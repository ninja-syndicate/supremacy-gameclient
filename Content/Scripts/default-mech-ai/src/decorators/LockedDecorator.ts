/*
import {Decorator, FAILURE, Node, NodeOrRegistration, RunCallback} from "behaviortree"
import {AIBlackboard} from "../blackboard"

interface LockedProps {
    isSet: boolean
}

class IsSetDecorator extends Decorator {
    nodeType = "IsSetDecorator"

    setConfig(config: LockedProps) {
        this.config = config
    }

    decorate(run: RunCallback, blackboard: AIBlackboard, config: LockedProps) {
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
*/