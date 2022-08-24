import { ObserverAborts, Selector } from "behaviortree"
import { Predicate } from "@decorators/Predicate"
import { AIBlackboard } from "@blackboards/blackboard"
import { Predicate_TargetInRange } from "@predicates/Predicate_InRange"
import { UserAction } from "enums"
import { Predicate_CanActivateUserAction } from "@predicates/Predicate_CanActivateAction"
import { BTT_TriggerUserAction } from "@tasks/useraction/BTT_TriggerUserAction"
import { Predicate_HasVeryLowTotalHealth } from "@predicates/Predicate_HasVeryLowTotalHealth"

export const WrappedTask_Overcharge = (isMatch: boolean, observerAborts: ObserverAborts) =>
    Predicate(
        BTT_TriggerUserAction(UserAction.Overcharge),
        (blackboard: AIBlackboard) => Predicate_TargetInRange(5000)(blackboard) && Predicate_CanActivateUserAction(UserAction.Overcharge)(blackboard),
        isMatch,
        observerAborts,
    )

export const WrappedTask_Repair = (isMatch: boolean, observerAborts: ObserverAborts) =>
    Predicate(
        BTT_TriggerUserAction(UserAction.Repair),
        (blackboard: AIBlackboard) => Predicate_HasVeryLowTotalHealth(blackboard) && Predicate_CanActivateUserAction(UserAction.Repair)(blackboard),
        isMatch,
        observerAborts,
    )

export const BT_UserAction = new Selector({
    nodes: [WrappedTask_Overcharge(true, ObserverAborts.None), WrappedTask_Repair(true, ObserverAborts.None)],
})
