import { ObserverAborts, Parallel, Selector } from "behaviortree"
import { WeaponTag } from "../../../../types/enums"
import { AIBlackboard } from "../../blackboard"
import { ParallelBackground } from "../../branches/ParallelBackground"
import { IsSet } from "../../decorators/IsSet"
import { Predicate } from "../../decorators/Predicate"
import { HasVeryLowTotalHealth } from "../../predicates/Predicate_HasVeryLowTotalHealth"
import { IsOutnumbered } from "../../predicates/Predicate_IsOutnumbered"
import { IsOutnumberingEnemies } from "../../predicates/Predicate_IsOutnumberingEnemies"
import { TargetHasMoreTotalHealth } from "../../predicates/Predicate_TargetHasMoreTotalHealth"
import { BTT_MoveTo } from "../../tasks/BTT_MoveTo"
import { BTT_Shoot } from "../../tasks/BTT_Shoot"
import { BTT_Success } from "../../tasks/BTT_Success"
import { BT_GetCover } from "../BT_GetCover"
import { BT_GetPickup } from "../BT_GetPickup"
import { BT_SetFocal } from "../BT_SetFocal"
import { BT_Strafe } from "../BT_Strafe"

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
                    (blackboard: AIBlackboard) => (!TargetHasMoreTotalHealth(blackboard) && !IsOutnumbered(blackboard)) || IsOutnumberingEnemies(blackboard),
                    true,
                    ObserverAborts.Both,
                ),
                BT_Strafe,
                BTT_Success,
            ],
        }),
    ],
})
