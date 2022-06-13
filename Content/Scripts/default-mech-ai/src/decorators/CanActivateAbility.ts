import {Decorator, FAILURE, Node, NodeOrRegistration, ObserverAborts, RunCallback} from "behaviortree"
import {AIBlackboard} from "../blackboard"
import {Ability} from "../../../types/enums";
import { AI } from "..";
import { BT_Combat } from "../trees/BT_Combat";

interface CanActivateAbilityProps {
    ability: Ability,
    isSet: boolean,
    observerAborts: ObserverAborts
}

class CanActivateAbilityDecorator extends Decorator {
    nodeType = "CanActivateAbilityDecorator"

    setConfig(config: CanActivateAbilityProps) {
        this.config = config;
        this.observerAborts = config.observerAborts
    }

    condition(blackboard: AIBlackboard) {
        return !!AI.CanActivateAbility(this.config.ability) !== this.config.isSet
    }
}

export const CanActivateAbility = (
    node: NodeOrRegistration,
    ability: Ability,
    isSet: boolean = true,
    observerAborts: ObserverAborts = ObserverAborts.None,
): Node =>
    new CanActivateAbilityDecorator({
        node: node,
        config: {
            ability,
            isSet,
            observerAborts,
    },
})