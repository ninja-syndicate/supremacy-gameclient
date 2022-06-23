import { Decorator, Node, NodeOrRegistration, ObserverAborts } from "behaviortree"
import { AI } from ".."
import { Action } from "../../../types/enums"
import { AIBlackboard } from "../blackboard"

interface CanActivateActionProps {
    action: Action
    isSet: boolean
    observerAborts: ObserverAborts
}

class CanActivateActionDecorator extends Decorator {
    nodeType = "CanActivateActionDecorator"

    setConfig(config: CanActivateActionProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    condition(blackboard: AIBlackboard) {
        return !!AI.CanActivateAction(this.config.action) === this.config.isSet
    }
}

export const CanActivateAction = (
    node: NodeOrRegistration,
    action: Action,
    isSet: boolean = true,
    observerAborts: ObserverAborts = ObserverAborts.None,
): Node =>
    new CanActivateActionDecorator({
        node: node,
        // start: (node as Node).blueprint.start,
        config: {
            action,
            isSet,
            observerAborts,
        },
    })
