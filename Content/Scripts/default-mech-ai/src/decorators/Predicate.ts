import { Decorator, Node, NodeOrRegistration, ObserverAborts } from "behaviortree"
import { AIBlackboard } from "../blackboard"

interface PredicateProps {
    predicate: (blackboard: AIBlackboard) => boolean
    isSet: boolean
    observerAborts: ObserverAborts
}

class PredicateDecorator extends Decorator {
    nodeType = "PredicateDecorator"

    setConfig(config: PredicateProps) {
        this.config = config
        this.observerAborts = config.observerAborts
    }

    condition(blackboard: AIBlackboard) {
        return this.config.predicate(blackboard) === this.config.isSet
    }
}

export const Predicate = (
    node: NodeOrRegistration,
    predicate: (blackboard: AIBlackboard) => boolean,
    isSet: boolean = true,
    observerAborts: ObserverAborts = ObserverAborts.None,
): Node =>
    new PredicateDecorator({
        node: node,
        start: (node as Node).blueprint.start,
        config: {
            predicate,
            isSet,
            observerAborts,
        },
    })
