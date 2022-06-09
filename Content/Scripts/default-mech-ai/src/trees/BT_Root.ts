import {Selector} from 'behaviortree'
import {BT_Combat} from "./BT_Combat"
import {BT_Patrol} from "./BT_Patrol"
import {IsSet,} from "../decorators/IsSet"

export const BT_Root = new Selector({
    nodes: [
        BT_Combat,
        // IsSet(BT_Combat, "target"),
        // IsSet(BT_Patrol, "target", false)
    ]
})