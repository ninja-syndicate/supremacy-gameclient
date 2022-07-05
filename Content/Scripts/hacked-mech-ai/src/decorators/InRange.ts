// NOTE: This decorator may be removed in the future.

import { Decorator, Node, NodeOrRegistration, ObserverAborts } from "behaviortree"
import { AIBlackboard } from "../blackboard"
import { distanceToVec } from "../helper"

interface InRangeProps {
    blackboardKey: keyof AIBlackboard
    range: number
    observerAborts: ObserverAborts
}

class InRangeDecorator extends Decorator {
    nodeType = "InRangeDecorator"

    setConfig(config: InRangeProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    condition(blackboard: AIBlackboard) {
        const location = blackboard[this.config.blackboardKey]
        const distTo = distanceToVec(blackboard.input.self.location, location)
        return distTo <= this.config.range
    }
}

export const InRange = (
    node: NodeOrRegistration,
    blackboardKey: keyof AIBlackboard,
    range: number = 0,
    observerAborts: ObserverAborts = ObserverAborts.None,
): Node =>
    new InRangeDecorator({
        node: node,
        config: {
            blackboardKey,
            range,
            observerAborts,
        },
    })
