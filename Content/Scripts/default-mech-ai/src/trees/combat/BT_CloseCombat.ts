import { ObserverAborts, Selector } from "behaviortree"
import { WeaponTag } from "../../../../types/enums"
import { ParallelBackground } from "../../branches/ParallelBackground"
import { IsSet } from "../../decorators/IsSet"
import { Predicate } from "../../decorators/Predicate"
import { HasVeryLowTotalHealth } from "../../predicates/Predicate_HasVeryLowTotalHealth"
import { BTT_MeleeAttack } from "../../tasks/BTT_MeleeAttack"
import { BTT_MoveTo } from "../../tasks/BTT_MoveTo"
import { BTT_Success } from "../../tasks/BTT_Success"
import { BT_GetCover } from "../BT_GetCover"
import { BT_GetPickup } from "../BT_GetPickup"
import { BT_SetFocal } from "../BT_SetFocal"

/**
 *
 */
export const BT_CloseCombat = new ParallelBackground({
    nodes: [
        // TODO: provide main and background properties
        // Main task
        BTT_MeleeAttack(WeaponTag.Melee),

        // Backgorund tasks
        BT_SetFocal,
        new Selector({
            nodes: [
                IsSet(BT_GetPickup, "desiredPickUpLocation", true, ObserverAborts.Both),
                Predicate(BT_GetCover, HasVeryLowTotalHealth, true, ObserverAborts.LowerPriority),
                // Predicate(BTT_MoveTo("targetLastKnownLocation", true), TargetHasMoreTotalHealth, false, ObserverAborts.Self),
                BTT_MoveTo("targetLastKnownLocation", true),
                BTT_Success,
            ],
        }),
    ],
})
