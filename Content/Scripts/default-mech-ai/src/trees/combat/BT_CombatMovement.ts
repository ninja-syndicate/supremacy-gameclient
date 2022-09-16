import { Predicate } from "@decorators/Predicate"
import { ObserverAborts, Selector } from "behaviortree"
import { BT_MoveToBattleZone } from "@trees/battlezone/BT_MoveToBattleZone"
import { Predicate_IsInsideBattleZone, Predicate_IsTargetInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { Predicate_IsSet } from "@predicates/Predicate_IsSet"
import { BT_GetPickup } from "@trees/BT_GetPickup"
import { BT_GetCover } from "@trees/BT_GetCover"
import { conjunct, disjunct, negate } from "@predicates/Functional"
import { Predicate_HasLowShield } from "@predicates/Predicate_HasLowShield"
import { Predicate_HasVeryLowTotalHealth, Predicate_TargetHasVeryLowTotalHealth } from "@predicates/Predicate_HasVeryLowTotalHealth"
import { Predicate_HasAmmoByTag } from "@predicates/combat/Predicate_HasAmmo"
import { WeaponTag } from "enums"
import { BT_CloseStrafe } from "@trees/BT_CloseStrafe"
import { BT_MoveByDistanceToTarget } from "@trees/movement/BT_MovementMode"
import { BT_Strafe } from "@trees/BT_Strafe"
import { IsOutnumbered } from "@predicates/Predicate_IsOutnumbered"
import { TargetHasMoreTotalHealth } from "@predicates/Predicate_TargetHasMoreTotalHealth"
import { AIBlackboard } from "@root/blackboards/blackboard"
import { Predicate_TargetInRange } from "@predicates/Predicate_InRange"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"
import { Predicate_IsTeamInAdvantage } from "@root/predicates/Predicate_IsTeamInAdvantage"

const closeCombatMovementCondition: (blackboard: AIBlackboard) => boolean = conjunct(
    Predicate_IsSet("canMelee"),
    negate(IsOutnumbered),
    negate(TargetHasMoreTotalHealth),
    negate(Predicate_HasVeryLowTotalHealth),
    negate(Predicate_HasLowShield),
    Predicate_TargetHasVeryLowTotalHealth,
    Predicate_IsTeamInAdvantage,
)

export const BT_MeleeMovement = new Selector({
    nodes: [
        Predicate(
            Predicate(BT_MoveByDistanceToTarget("targetLastKnownLocation", true), Predicate_IsTargetInsideBattleZone, true, ObserverAborts.Self),
            Predicate_TargetInRange(CURRENT_AI_CONFIG.closeCombatKeepRange),
            false,
            ObserverAborts.LowerPriority,
        ),
        BT_CloseStrafe,
    ],
})

const BT_CombatNormalMovement = new Selector({
    nodes: [Predicate(BT_MeleeMovement, closeCombatMovementCondition, true, ObserverAborts.Self), BT_Strafe],
})

export const BT_CombatMovement = new Selector({
    nodes: [
        Predicate(BT_MoveToBattleZone, Predicate_IsInsideBattleZone, false, ObserverAborts.LowerPriority),
        Predicate(BT_GetPickup, Predicate_IsSet("desiredPickupLocation"), true, ObserverAborts.Both),
        Predicate(BT_GetCover, disjunct(Predicate_HasLowShield, Predicate_HasVeryLowTotalHealth), true, ObserverAborts.LowerPriority),
        // TODO: Use weapon state?
        new Selector({
            nodes: [Predicate(BT_CombatNormalMovement, Predicate_IsSet("hasPrimaryAmmo"), true, ObserverAborts.Both), BT_MeleeMovement],
        }),
    ],
})
