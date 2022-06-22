import { ObserverAborts, Parallel, ParallelSelector, Selector, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_Shoot } from "../tasks/BTT_Shoot"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentString } from "../tasks/BTT_EQSSetArgument"
import { Predicate } from "../decorators/Predicate"
import { BT_GetCover } from "./BT_GetCover"
import { ForceSuccess } from "../decorators/ForceSuccess"
import { IsSet } from "../decorators/IsSet"
import { BT_Strafe } from "./BT_Strafe"
import { HasVeryLowTotalHealth } from "../predicates/Predicate_HasVeryLowTotalHealth"
import { TargetHasMoreTotalHealth } from "../predicates/Predicate_TargetHasMoreTotalHealth"
import { OutnumberingEnemies } from "../predicates/Predicate_OutnumberingEnemies"
import { BTT_TriggerWeapon } from "../tasks/BTT_TriggerWeapon"
import { BT_GetPickup } from "./BT_GetPickup"
import { BT_SetFocal } from "./BT_SetFocal"
import { BTT_Success } from "../tasks/BTT_Success"
import { IsOutnumbered } from "../predicates/Predicate_IsOuntnumbered"

/**
 *
 */
export const BT_RangeCombat = new ParallelBackground({
    nodes: [
        new Parallel({
            nodes: [BTT_Shoot(WeaponTag.PrimaryLeftArm), BTT_Shoot(WeaponTag.PrimaryRightArm)],
        }),
        BT_SetFocal,
        new Selector({
            nodes: [
                IsSet(BT_GetPickup, "desiredPickUpLocation", true, ObserverAborts.Both),
                Predicate(BT_GetCover, HasVeryLowTotalHealth, true, ObserverAborts.LowerPriority),
                Predicate(
                    // TODO: This should ideally be getting closer, not directly to target.
                    BTT_MoveTo("targetLastKnownLocation"),
                    (blackboard: AIBlackboard) => (!TargetHasMoreTotalHealth(blackboard) && !IsOutnumbered(blackboard)) || OutnumberingEnemies(blackboard),
                    true,
                    ObserverAborts.Both,
                ),
                BT_Strafe,
                BTT_Success,
            ],
        }),
    ],
})
