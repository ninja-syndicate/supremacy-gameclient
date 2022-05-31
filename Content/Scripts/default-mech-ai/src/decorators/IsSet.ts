import {Decorator, RunCallback} from "behaviortree";
import {AIBlackboard} from "../blackboard";

interface IsSetProps {
    blackboardKey: keyof AIBlackboard
}

export default class IsSet extends Decorator {
    constructor({config = {} as IsSetProps, ...props}) {
        super(props);
        this.nodeType = "IsSetDecorator";
        this.setConfig(config);
    }

    decorate(run: RunCallback, blackboard: AIBlackboard, config: IsSetProps) {
        console.log(`decorate: ${JSON.stringify(config)}`);
        return run();
    }
}