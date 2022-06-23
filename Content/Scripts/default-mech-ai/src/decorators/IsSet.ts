import { Decorator, Node, NodeOrRegistration, ObserverAborts } from "behaviortree"
import { AIBlackboard } from "../blackboard"

interface IsSetProps {
    blackboardKey: keyof AIBlackboard
    isSet: boolean
    observerAborts: ObserverAborts
}

class IsSetDecorator extends Decorator {
    nodeType = "IsSetDecorator"

    setConfig(config: IsSetProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    condition(blackboard: AIBlackboard) {
        return !!blackboard[this.config.blackboardKey] === this.config.isSet
    }
}

export const IsSet = (
    node: NodeOrRegistration,
    blackboardKey: keyof AIBlackboard,
    isSet: boolean = true,
    observerAborts: ObserverAborts = ObserverAborts.None,
): Node =>
    new IsSetDecorator({
        node: node,
        start: (node as Node).blueprint.start,
        config: {
            blackboardKey,
            isSet,
            observerAborts,
        },
    })
