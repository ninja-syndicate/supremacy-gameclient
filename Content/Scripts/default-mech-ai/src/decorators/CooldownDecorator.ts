import { FAILURE, SUCCESS, RUNNING, Parallel, RunConfig, Decorator, RunCallback } from 'behaviortree';
import BranchNode from 'behaviortree';
import Node from 'behaviortree/src/Node';
import { ParallelRunConfig, RunResult, StatusWithState, Blackboard, MinimalBlueprint, NodeOrRegistration } from 'behaviortree';


export class CooldownDecorator extends Decorator {
  lock = false;
  nodeType = 'CooldownDecorator';

  setConfig({ cooldown = 5 }) {
    this.config = {
      cooldown
    };
  }

  decorate(run: RunCallback) {
    if (this.lock) {
      return FAILURE;
    }
    const result = run();
    if (!isRunning(result)) {
      this.lock = true;
      setTimeout(() => {
        this.lock = false;
      }, this.config.cooldown * 1000);
    }
    return result;
  }
}

function isRunning(result: RunResult | undefined): boolean {
	return result === RUNNING || (typeof result === 'object' && result.total === RUNNING);
}