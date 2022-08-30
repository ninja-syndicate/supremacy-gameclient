import { Decorator, Node, NodeOrRegistration, ObserverAborts } from "behaviortree"
import { AIBlackboard } from "@blackboards/blackboard"

interface PredicateProps {
    predicate: (blackboard: AIBlackboard) => boolean
    isMatch: boolean
    observerAborts: ObserverAborts
}

/**
 * A decorator that checks if the result of running predicate function matches {@link PredicateProps.isMatch}.
 */
export class PredicateDecorator extends Decorator {
    nodeType = "PredicateDecorator"

    setConfig(config: PredicateProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    // NOTE: Assumes that this condition function and its predicate function does not modify the blackboard state, i.e. pure.
    condition(blackboard: AIBlackboard) {
        return !!this.config.predicate(blackboard) === this.config.isMatch
    }
}

/**
 * Helper function for creating a new PredicateDecorator.
 *
 * @see {@link PredicateDecorator} for details about the Predicate decorator.
 *
 * @param node The node to run if the result of running {@link predicate} function matches {@link isMatch}
 * @param predicate A function that returns boolean to act as a condition for this decorator
 * @param isMatch Whether to test for is match or not
 * @param observerAborts Observer abort value to use (@see {@link ObserverAborts}). By default, this is {@link ObserverAborts.None}
 * @returns a new PredicateDecorator
 */
export const Predicate = (
    node: NodeOrRegistration,
    predicate: (blackboard: AIBlackboard) => boolean,
    isMatch: boolean = true,
    observerAborts: ObserverAborts = ObserverAborts.None,
): Node =>
    new PredicateDecorator({
        node: node,
        // start: (node as Node).blueprint.start,
        config: {
            predicate,
            isMatch,
            observerAborts,
        },
    })
