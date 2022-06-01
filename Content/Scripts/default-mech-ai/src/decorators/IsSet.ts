import {Decorator, RunCallback} from "behaviortree";
import {AIBlackboard} from "../blackboard";

interface IsSetProps {
    blackboardKey: keyof AIBlackboard
}

export class IsSet extends Decorator {
    constructor(props) {
        super(props);
        this.nodeType = "IsSetDecorator ";
        this.setConfig(props);
    }

    setConfig({blackboardKey}: IsSetProps) {
        this.config = {
            blackboardKey
        }
    }

    decorate(run: RunCallback, blackboard: AIBlackboard, config: IsSetProps) {
        console.log(`decorate: ${JSON.stringify(config)}`);
        return run();
    }
}