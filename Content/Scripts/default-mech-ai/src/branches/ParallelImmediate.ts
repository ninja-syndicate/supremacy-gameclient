import { FAILURE, SUCCESS, RUNNING } from 'behaviortree/src/constants';
import BranchNode from 'behaviortree/src/BranchNode';
import Node from 'behaviortree/src/Node';
import { isRunning } from 'behaviortree/src/helper';
import { ParallelRunConfig, RunResult, StatusWithState, Blackboard, MinimalBlueprint, NodeOrRegistration } from 'behaviortree/src/types';

/**
 * The Parallel node runs all of its children in parallel and stops running if all of the children are
 * successful or the first one returns failure.
 */
export default class Parallel extends BranchNode {
  numNodes: number;
  nodes: NodeOrRegistration[];

  nodeType = 'Parallel';

  constructor(blueprint: MinimalBlueprint) {
    super(blueprint);

    this.nodes = blueprint.nodes || [];
    this.numNodes = this.nodes.length;
  }

  run(blackboard: Blackboard = {}, { lastRun, introspector, rerun, registryLookUp = (x) => x as Node }: ParallelRunConfig = {}) {
    if (!rerun) this.blueprint.start(blackboard);
    const results: Array<RunResult> = [];
    for (let currentIndex = 0; currentIndex < this.numNodes; ++currentIndex) {
      const lastRunForIndex = lastRun && (lastRun as StatusWithState).state[currentIndex];
      if (lastRunForIndex && !isRunning(lastRunForIndex)) {
        results[currentIndex] = lastRunForIndex;
        continue;
      }
      const node = registryLookUp(this.nodes[currentIndex]);
      const result = node.run(blackboard, { lastRun: lastRunForIndex, introspector, rerun, registryLookUp });
      results[currentIndex] = result;
    }
    const endResult = this.calcResult(results);
    if (!isRunning(endResult)) {
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
    const running = !!results.find((x) => isRunning(x));
    return running ? { total: RUNNING, state: results } : SUCCESS;
  }
}
