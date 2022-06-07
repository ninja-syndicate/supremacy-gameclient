import {Decorator, FAILURE, Node, NodeOrRegistration, RunCallback} from "behaviortree"
import {AIBlackboard} from "../blackboard"
import {BT_Combat} from "../trees/BT_Combat"

interface IsSetProps {
    blackboardKey: keyof AIBlackboard
    isSet: boolean
}

class IsSetDecorator extends Decorator {
    nodeType = "IsSetDecorator"

    setConfig(config: IsSetProps) {
        this.config = config
    }

    decorate(run: RunCallback, blackboard: AIBlackboard, config: IsSetProps) {
        if (!!blackboard[config.blackboardKey] !== config.isSet) {
            return FAILURE;
        }
        return run();
    }
}

export const IsSet = (node: NodeOrRegistration, blackboardKey: keyof AIBlackboard, isSet: boolean = true): Node => new IsSetDecorator({
    node: node, config: {
        blackboardKey,
        isSet,
    }
})