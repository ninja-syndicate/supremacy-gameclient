import { ObserverAborts, ParallelSelector, Selector, Sequence } from "behaviortree"
import { WeaponTag } from "enums"
import { ParallelBackground } from "@branches/ParallelBackground"
import { IsSet } from "@decorators/IsSet"
import { BTT_Shoot } from "@tasks/BTT_Shoot"
import { BTT_Success } from "@tasks/BTT_Success"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { BT_MoveToCommand } from "@trees/BT_MoveToCommand"
import { BT_PatrolNonParallel } from "@trees/BT_Patrol"
import { ForceSuccess } from "@trees/helper/BT_Helper"

export const BT_RangeCombat = new ParallelBackground({
    nodes: [
        // Main task
        new ParallelSelector({
            nodes: [ForceSuccess(BTT_Shoot(WeaponTag.PrimaryLeftArm)), ForceSuccess(BTT_Shoot(WeaponTag.PrimaryRightArm))],
        }),

        // Background tasks:
        BTT_SetFocalPoint("target"),
        new Selector({
            nodes: [IsSet(BT_MoveToCommand, "isCommanded", true, ObserverAborts.Both), IsSet(BT_PatrolNonParallel, "moveCommandLocation", true), BTT_Success],
        }),
    ],
})
