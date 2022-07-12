// TODO: implementation
/*
import { Decorator, Node, NodeOrRegistration, ObserverAborts, RunCallback } from "behaviortree"
import { AIBlackboard } from "../blackboard"

interface LoopProps {
    count: number
    observerAborts: ObserverAborts
}

class LoopDecorator extends Decorator {
    nodeType = "LoopDecorator"
    successCount = 0

    setConfig(config: LoopProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    decorate(run: RunCallback, blackboard: AIBlackboard, config: LoopProps) {
        const result = super.decorate(run, blackboard, config)
        if (isSuccess(result)) {
            
        }
        return isRunning(result) ? RUNNING : SUCCESS
    }
}

export const Loop = (node: NodeOrRegistration, count: number = 1, observerAborts: ObserverAborts = ObserverAborts.None): Node =>
    new LoopDecorator({
        node: node,
        config: {
            count: count,
            start: (node as Node).blueprint.start,
            observerAborts,
        },
    })

*/