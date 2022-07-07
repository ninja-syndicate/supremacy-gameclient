import { Decorator, Node, NodeOrRegistration, ObserverAborts } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"

interface IsCommandedProps {
    blackboardKey: keyof AIBlackboard
    isCommanded: boolean
    observerAborts: ObserverAborts
}

class IsCommandedDecorator extends Decorator {
    nodeType = "IsSetDecorator"

    setConfig(config: IsCommandedProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    condition(blackboard: AIBlackboard) {
        return AI.
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
