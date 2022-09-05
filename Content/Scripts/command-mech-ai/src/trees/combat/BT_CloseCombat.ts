import { ObserverAborts, Selector, Sequence } from "behaviortree"
import { WeaponTag } from "enums"
import { ParallelBackground } from "@branches/ParallelBackground"
import { IsSet } from "@decorators/IsSet"
import { BTT_MeleeAttack } from "@tasks/BTT_MeleeAttack"
import { BTT_Success } from "@tasks/BTT_Success"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { BT_MoveToCommand } from "@trees/BT_MoveToCommand"
import { BT_PatrolNonParallel } from "@trees/BT_Patrol"

export const BT_CloseCombat = new ParallelBackground({
    nodes: [
        // Main task
        BTT_MeleeAttack(WeaponTag.Melee),

        // Background tasks
        BTT_SetFocalPoint("target"),
        new Selector({
            nodes: [IsSet(BT_MoveToCommand, "isCommanded", true, ObserverAborts.Both), IsSet(BT_PatrolNonParallel, "moveCommandLocation", true), BTT_Success],
        }),
    ],
})
