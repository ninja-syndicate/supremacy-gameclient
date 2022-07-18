import { Decorator, Node, NodeOrRegistration, ObserverAborts } from "behaviortree"
import { AI } from "@root/index"
import { Action } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"

interface CanActivateActionProps {
    action: Action
    isMatch: boolean
    observerAborts: ObserverAborts
}

/**
 * A decorator that checks if the truth of whether the action can be activated matches {@link CanActivateActionProps.isMatch}.
 */
class CanActivateActionDecorator extends Decorator {
    nodeType = "CanActivateActionDecorator"

    setConfig(config: CanActivateActionProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    condition(blackboard: AIBlackboard) {
        return !!AI.CanActivateAction(this.config.action) === this.config.isMatch
    }
}

/**
 * Helper function to create a new CanActivateActionDecorator.
 *
 * @see {@link CanActivateActionDecorator} for details about the CanActivateAction decorator.
 *
 * @param node The node to run if the truth of whether the specified {@link action} can be activated matches {@link isMatch}
 * @param action The action to test for activation
 * @param isMatch Whether to test for match or not
 * @param observerAborts Observer abort value to use (@see {@link ObserverAborts}). By default, this is {@link ObserverAborts.None}
 * @returns a new CanActivateActionDecorator
 */
export const CanActivateAction = (
    node: NodeOrRegistration,
    action: Action,
    isMatch: boolean = true,
    observerAborts: ObserverAborts = ObserverAborts.None,
): Node =>
    new CanActivateActionDecorator({
        node: node,
        // start: (node as Node).blueprint.start,
        config: {
            action,
            isMatch,
            observerAborts,
        },
    })
