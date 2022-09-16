import { ObserverAborts, Selector } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { IsSet } from "@decorators/IsSet"
import { Predicate } from "@decorators/Predicate"
import { Predicate_HasLowShield } from "@predicates/Predicate_HasLowShield"
import { BT_Camp } from "@trees/BT_Camp"
import { BT_CurrentTargetVisible } from "@root/trees/combat/BT_CurrentTargetVisible"
import { BT_GetPickup } from "@trees/BT_GetPickup"
import { BT_SearchTarget } from "@trees/BT_SearchTarget"
import { BTT_Success } from "@tasks/BTT_Success"
import { BT_Patrol } from "@trees/BT_Patrol"
import { Action } from "enums"
import { BT_ParallelMoveToBattleZone } from "@trees/battlezone/BT_ParallelMoveToBattleZone"
import { Predicate_IsInsideBattleZone } from "@predicates/Predicate_IsInsideBattleZone"
import { Predicate_IsUsingAction } from "@predicates/Predicate_IsUsingAction"
import { BT_Repair } from "@trees/useraction/BT_UserAction"

/**
 * The main combat behavior tree.
 *
 * This behavior represents what AI can do when it is in combat state. It is composed of the following sub-behavior trees:
 *
 * {@link BT_CurrentTargetVisible} if AI can see the current target and isn't using any latent actions. This behavior is where the actual fighting logic is placed
 * {@link BT_GetPickup} otherwise get to the pickup location if AI has any
 * {@link BT_Camp} - otherwise get to the cover location and camp if its shield is low
 * {@link BT_SearchTarget} - otherwise searches for the current target based on the target's last known location
 * {@link BT_Patrol} otherwise fallback to patrol if {@link BT_SearchTarget} fails.
 *
 * You can change this behavior to prioritize certain behaviors or anything you deem appropriate.
 */
export const BT_HasTarget = new Selector({
    nodes: [
        Predicate(
            BT_CurrentTargetVisible,
            (blackboard: AIBlackboard) => blackboard.canSeeTarget || Predicate_IsUsingAction(Action.SpecialAttack)(blackboard),
            true,
            ObserverAborts.Both,
        ),
        BT_Repair(ObserverAborts.LowerPriority),
        Predicate(BT_ParallelMoveToBattleZone, Predicate_IsInsideBattleZone, false, ObserverAborts.LowerPriority),
        IsSet(BT_GetPickup, "desiredPickupLocation", true, ObserverAborts.Both),
        Predicate(BT_Camp, Predicate_HasLowShield, true, ObserverAborts.LowerPriority),
        // TODO: Need to decide priority between investigating noise and searching target.
        // Predicate(BT_InvestigateNoise, (blackboard: AIBlackboard) => !blackboard.canSeeTarget && blackboard.heardNoise, true, ObserverAborts.LowerPriority),
        // CanActivateAction(Predicate(BTT_Taunt, (blackboard: AIBlackboard) => !blackboard.canSeeTarget && !HasLowShield(blackboard)), Action.Taunt),
        Predicate(BT_SearchTarget, (blackboard: AIBlackboard) => !blackboard.canSeeTarget),
        BTT_Success,
    ],
})