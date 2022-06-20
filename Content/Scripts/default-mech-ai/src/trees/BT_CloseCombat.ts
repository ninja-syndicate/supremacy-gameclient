import { ObserverAborts, Selector, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { WeaponTag } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_TriggerWeapon } from "../tasks/BTT_TriggerWeapon"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_MeleeAttack } from "../tasks/BTT_MeleeAttack"
import { AIBlackboard } from "../blackboard"
import { BT_GetCover } from "./BT_GetCover"
import { Predicate } from "../decorators/Predicate"
import { ForceSuccess } from "../decorators/ForceSuccess"
import { HasVeryLowTotalHealth } from "../predicates/Predicate_HasVeryLowTotalHealth"
import { TargetHasMoreTotalHealth } from "../predicates/Predicate_TargetHasMoreTotalHealth"

/**
 *
 */
export const BT_CloseCombat = new ParallelBackground({
    nodes: [
        new ParallelBackground({
            nodes: [
                BTT_MeleeAttack(WeaponTag.Melee),
                new Selector({
                    nodes: [
                        // TODO: do observer aborts
                        Predicate(BT_GetCover, HasVeryLowTotalHealth, true, ObserverAborts.Both),
                        Predicate(BTT_MoveTo("targetLastKnownLocation"), TargetHasMoreTotalHealth, false, ObserverAborts.Self),
                        BTT_MoveTo("targetLastKnownLocation"),
                    ],
                }),
            ],
        }),
        ForceSuccess(
            new Selector({
                nodes: [BTT_SetFocalPoint("target"), BTT_SetFocalPoint("targetLastKnownLocation")],
            }),
        ),
    ],
})
