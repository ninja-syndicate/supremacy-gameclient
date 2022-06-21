import { ObserverAborts, Selector, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { Predicate } from "../decorators/Predicate"
import { AI } from ".."
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { BTT_LogString } from "../tasks/BTT_LogString"
import { IsSet } from "../decorators/IsSet"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { ParallelBackground } from "../branches/ParallelBackground"

/**
 * Picking up behavior.
 */
export const BT_GetPickup = new ParallelBackground({
    nodes: [
        new Sequence({
            nodes: [
                // Force success to clear the desired pickup location if not navigable.
                ForceSuccess(BTT_MoveTo("desiredPickUpLocation")),
                BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.desiredPickUpLocation = undefined)),
            ],
        }),
        ForceSuccess(
            new Selector({
                nodes: [
                    IsSet(BTT_SetFocalPoint("target"), "canSeeTarget", true, ObserverAborts.Both),
                    BTT_SetFocalPoint("targetLastKnownLocation"),
                    Predicate(
                        BTT_SetFocalPoint("damageStimulusFocalPoint"),
                        (blackboard: AIBlackboard) => blackboard.damageStimulusFocalPoint !== undefined && blackboard.isLastDamageFromTarget,
                    ),
                    BTT_SetFocalPoint("desiredPickUpLocation"),
                ],
            }),
        ),
    ],
})
