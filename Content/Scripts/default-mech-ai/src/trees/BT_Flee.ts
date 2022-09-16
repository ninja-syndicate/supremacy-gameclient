import { Predicate } from "@decorators/Predicate"
import { ObserverAborts, Selector } from "behaviortree"
import { BT_GetPickup } from "@trees/BT_GetPickup"
import { BT_MoveToBattleZone } from "@trees/battlezone/BT_MoveToBattleZone"
import { BT_GetCover } from "@trees/BT_GetCover"
import { Predicate_IsInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { Predicate_IsSet } from "@predicates/Predicate_IsSet"

export const BT_Flee = new Selector({
    nodes: [
        Predicate(BT_MoveToBattleZone, Predicate_IsInsideBattleZone, false, ObserverAborts.LowerPriority),
        Predicate(BT_GetPickup, Predicate_IsSet("desiredPickupLocation"), true, ObserverAborts.Both),
        BT_GetCover,
    ],
})
