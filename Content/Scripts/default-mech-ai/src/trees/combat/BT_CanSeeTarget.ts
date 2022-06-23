import { ObserverAborts, Selector } from "behaviortree"
import { Action } from "enums"
import { AIBlackboard } from "../../blackboard"
import { CanActivateAction } from "../../decorators/CanActivateAction"
import { Predicate } from "../../decorators/Predicate"
import { distanceToVec } from "../../helper"
import { BTT_SpecialAttack } from "../../tasks/BTT_SpecialAttack"
import { BT_CloseCombat } from "./BT_CloseCombat"
import { BT_RangeCombat } from "./BT_RangeCombat"

export const BT_CanSeeTarget = new Selector({
    nodes: [
        CanActivateAction(BTT_SpecialAttack("targetLastKnownLocation"), Action.SpecialAttack, true, ObserverAborts.LowerPriority),
        /*
        Predicate(
            ,
            (blackboard: AIBlackboard) => blackboard.canUseSpecialAttack && blackboard.targetLastKnownLocation !== undefined,
            true,
            ObserverAborts.LowerPriority,
        ),
        */
        Predicate(
            BT_CloseCombat,
            (blackboard: AIBlackboard) =>
                blackboard.canMelee &&
                blackboard.targetLastKnownLocation !== undefined &&
                distanceToVec(blackboard.input.self.location, blackboard.targetLastKnownLocation) <= 4000,
            true,
            ObserverAborts.Both,
        ),
        BT_RangeCombat,
    ],
})
