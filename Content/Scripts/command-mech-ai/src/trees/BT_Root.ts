import { ObserverAborts, Selector } from "behaviortree"
import { IsSet } from "@decorators/IsSet"
import { BTT_Wait } from "@tasks/BTT_Wait"
import { BT_Combat } from "@trees/combat/BT_Combat"
import { BT_Patrol } from "@trees/BT_Patrol"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { BT_MoveToCommand } from "@trees/BT_MoveToCommand"

export const Parallel_MoveToCommand = new ParallelBackground({ nodes: [BT_MoveToCommand, BT_SetFocal] })

// TODO: Support user actions for composable mechs?
export const BT_Root = new Selector({
    nodes: [
        // Check BT_COmbat
        IsSet(BT_Combat, "target", true, ObserverAborts.Both),
        IsSet(Parallel_MoveToCommand, "isCommanded", true, ObserverAborts.Both),
        IsSet(BT_Patrol, "moveCommandLocation", true),
        BTT_Wait(1),
    ],
})
