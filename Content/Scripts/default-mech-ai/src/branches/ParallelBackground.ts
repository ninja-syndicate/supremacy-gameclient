import { FAILURE, SUCCESS, RUNNING, Parallel } from 'behaviortree';
import BranchNode from 'behaviortree';
import Node from 'behaviortree/src/Node';
import { ParallelRunConfig, RunResult, StatusWithState, Blackboard, MinimalBlueprint, NodeOrRegistration } from 'behaviortree';

/**
 * The parallel background branch node is a variant of parallel node that keeps
 * running the background task repeatedly after it completes. But finishes when
 * the main task succeeds.
 */
export class ParallelBackground extends Parallel {
	nodeType = 'ParallelBackground';

	run(blackboard: Blackboard = {}, { lastRun, introspector, rerun, registryLookUp = (x) => x as Node }: ParallelRunConfig = {}) {
		if (!rerun) 
			this.blueprint.start(blackboard);

		const results: Array<RunResult> = [];
		for (let currentIndex = 0; currentIndex < this.numNodes; ++currentIndex) {
			const lastRunForIndex = lastRun && (lastRun as StatusWithState).state[currentIndex];
            if (lastRunForIndex && !isRunning(lastRunForIndex)) {
                results[currentIndex] = lastRunForIndex;
				if (currentIndex === 0)
					break;
				if (isFailure(lastRunForIndex))
					break;
            }
			const node = registryLookUp(this.nodes[currentIndex]);
			const result = node.run(blackboard, { lastRun: lastRunForIndex, introspector, rerun, registryLookUp });
			results[currentIndex] = result;

			if (currentIndex === 0 && isFailure(result))
				break;
		}
		const endResult = this.calcResult(results);
		if (isFailure(endResult) || isSuccess(results[0])) {
			this.blueprint.end(blackboard);
		}
		if (introspector) {
			const running = !!results.find((x) => isRunning(x));
			const debugResult = running ? RUNNING : (endResult as boolean);
			introspector.wrapLast(this.numNodes, this, debugResult, blackboard);
		}
		return endResult;
	}

	protected calcResult(results: Array<RunResult>): RunResult {
		if (results.includes(FAILURE)) {
		  return FAILURE;
		}
		return { total: RUNNING, state: results };
	  }
}

function isRunning(result: RunResult | undefined): boolean {
	return result === RUNNING || (typeof result === 'object' && result.total === RUNNING);
}

function isFailure(result: RunResult | undefined): boolean {
	return result === FAILURE || (typeof result === 'object' && result.total === FAILURE);
}

function isSuccess(result: RunResult | undefined): boolean {
	return result === SUCCESS || (typeof result === 'object' && result.total === SUCCESS);
}