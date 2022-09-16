import { Selector, Sequence } from "behaviortree"
import { IsSet } from "@decorators/IsSet"
import { Predicate } from "@decorators/Predicate"
import { BTT_Success } from "@tasks/BTT_Success"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "@blackboards/blackboard"
import { Predicate_FocusToDamage } from "@predicates/Predicate_FocusToDamage"
import { Predicate_FocusToPredictedLocation } from "@predicates/Predicate_FocusToPredictedLocation"
import { Predicate_FocusToWeaponNoise } from "@predicates/Predicate_FocusToWeaponNoise"
import { BTT_SetValue } from "@tasks/BTT_SetValue"

/**
 * Behavior for setting the focal point of AI (@see {@link BTT_SetFocalPoint}).
 *
 * Sets the focal point of AI to the most desirable target/location.
 * Currently, the priority for setting the focal point is defined as follows:
 *
 *  - {@link AIBlackboard.target} if AI can see the current target
 *  - {@link AIBlackboard.damageStimulusFocalPoint} if the predicate {@link Predicate_FocusToDamage} is satisfied
 *  - {@link AIBlackboard.targetPredictedLocation} if the predicate {@link Predicate_FocusToPredictedLocation} is satisfied
 *  - {@link AIBlackboard.targetLastKnownLocation} if AI has the target's last known location
 *  - {@link AIBlackboard.lastWeaponNoise.location} if the predicate {@link Predicate_FocusToWeaponNoise} is satisfied
 *
 * You may want to wrap around this behavior with a {@link ForceSuccess} decorator if used with a {@link ParallelBackground} branch node.
 */
export const BT_SetFocal = new Selector({
    nodes: [
        IsSet(BTT_SetFocalPoint("target"), "canSeeTarget"),
        Predicate(BTT_SetFocalPoint("damageStimulusFocalPoint"), Predicate_FocusToDamage),
        Predicate(BTT_SetFocalPoint("targetPredictedLocation"), Predicate_FocusToPredictedLocation),
        IsSet(BTT_SetFocalPoint("targetLastKnownLocation"), "targetLastKnownLocation"),
        // TODO: Implement score function for targetPrediction/Sound focal points
        // TODO: Probably clear focus after investing that location later.
        Predicate(
            new Sequence({
                nodes: [BTT_SetFocalPoint("lastWeaponNoise"), BTT_SetValue((blackboard: AIBlackboard) => (blackboard.lastWeaponNoise = undefined))],
            }),
            Predicate_FocusToWeaponNoise,
        ),
        // TODO: This success can be removed if ForceSuccess decorator worked.
        BTT_Success,
    ],
})
