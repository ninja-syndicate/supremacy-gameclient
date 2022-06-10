import {Decorator, FAILURE, Node, NodeOrRegistration, RunCallback, RUNNING, RunResult} from "behaviortree"
import {AIBlackboard} from "../blackboard"
import {BT_Combat} from "../trees/BT_Combat"

class AlwaysFailDecorator extends Decorator {
    nodeType = "AlwaysFailDecorator"

    decorate(run: RunCallback) {
        const result = run();
        if (isRunning(result)) return result;
        return FAILURE;
    }
}

export const AlwaysFail = (node: NodeOrRegistration): Node => new AlwaysFailDecorator({
    node: node, 
    config: {}
})

function isRunning(result: RunResult | undefined): boolean {
	return result === RUNNING || (typeof result === 'object' && result.total === RUNNING);
}
