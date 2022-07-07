import { Decorator, Node, NodeOrRegistration, ObserverAborts } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"

interface IsSetProps {
    blackboardKey: keyof AIBlackboard
    isSet: boolean
    observerAborts: ObserverAborts
}

/**
 * A decorator that checks if the truth of blackboard key is set matches {@link IsSetProps.isSet}.
 */
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

/**
 * Helper function for creating a new IsSetDecorator.
 *
 * @see {@link IsSetDecorator} for details about the IsSet decorator.
 *
 * @param node The node to run if the truth of {@link blackboardKey} is set matches {@link isSet}
 * @param blackboardKey The blackboard key to test
 * @param isSet Whether to test for is set or not
 * @param observerAborts Observer abort value to use (@see {@link ObserverAborts}). By default, this is {@link ObserverAborts.None}
 * @returns a new IsSetDecorator
 */
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
