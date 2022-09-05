import { ObserverAborts, Selector } from "behaviortree"
import { IsSet } from "@decorators/IsSet"
import { BT_CanSeeTarget } from "@trees/combat/BT_CanSeeTarget"
import { BTT_Success } from "@tasks/BTT_Success"
import { BT_Patrol } from "@trees/BT_Patrol"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BT_MoveToCommand } from "@trees/BT_MoveToCommand"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { Predicate } from "@decorators/Predicate"
import { Predicate_IsUsingAction } from "@predicates/Predicate_IsUsingAction"
import { Action } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"

export const Parallel_MoveToCommand = new ParallelBackground({ nodes: [BT_MoveToCommand, BT_SetFocal] })

export const BT_Combat = new Selector({
    nodes: [
        Predicate(
            BT_CanSeeTarget,
            (blackboard: AIBlackboard) => blackboard.canSeeTarget || Predicate_IsUsingAction(Action.SpecialAttack)(blackboard),
            true,
            ObserverAborts.Both,
        ),
        IsSet(Parallel_MoveToCommand, "isCommanded", true, ObserverAborts.Both),
        IsSet(BT_Patrol, "moveCommandLocation", true),
        BTT_Success,
    ],
})
