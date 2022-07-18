// NOTE: ForceSuccess decorator is buggy. Don't use it yet.

import { Decorator, Node, NodeOrRegistration, ObserverAborts, RunCallback, RUNNING, RunResult, SUCCESS } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"

interface ForceSuccessProps {
    observerAborts: ObserverAborts
}

class ForceSuccessDecorator extends Decorator {
    nodeType = "ForceSuccessDecorator"

    setConfig(config: ForceSuccessProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    decorate(run: RunCallback, blackboard: AIBlackboard, config: ForceSuccessProps) {
        const result = super.decorate(run, blackboard, config)
        return isRunning(result) ? RUNNING : SUCCESS
    }
}

export const ForceSuccess = (node: NodeOrRegistration, observerAborts: ObserverAborts = ObserverAborts.None): Node =>
    new ForceSuccessDecorator({
        node: node,
        config: {
            start: (node as Node).blueprint.start,
            observerAborts,
        },
    })

function isRunning(result: RunResult | undefined): boolean {
    return result === RUNNING || (typeof result === "object" && result.total === RUNNING)
}