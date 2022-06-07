import {Decorator, FAILURE, Node, NodeOrRegistration, RunCallback} from "behaviortree"
import {AIBlackboard} from "../blackboard"
import {Ability} from "../../../types/enums";
import { AI } from "..";
import { BT_Combat } from "../trees/BT_Combat";

interface CanActivateAbilityProps {
    ability: Ability,
    isSet: boolean
}

class CanActivateAbilityDecorator extends Decorator {
    nodeType = "CanActivateAbilityDecorator"

    setConfig(config: CanActivateAbilityProps) {
        this.config = config;
    }

    decorate(run: RunCallback, blackboard: AIBlackboard, config: CanActivateAbilityProps) {
        if (AI.CanActivateAbility(config.ability) !== config.isSet) {
            return FAILURE;
        }
        return run();
    }
}

export const CanActivateAbility = (node: NodeOrRegistration, ability: Ability, isSet: boolean = true): Node => new CanActivateAbilityDecorator({
    node: node, config: {
        ability,
        isSet
    }
});