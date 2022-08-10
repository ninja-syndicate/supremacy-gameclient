import { Blackboard, FAILURE, Parallel, ParallelRunConfig, RUNNING, RunResult, StatusWithState, SUCCESS, Node } from "behaviortree"

/**
 * The {@link ParallelBackground} branch node is a variant of {@link Parallel} node that keeps running the background task repeatedly after it returns SUCCESS.
 * The nodes are split into a main and background tasks and until the main task finishes (i.e. returns SUCCESS), background tasks run in parallel and restarts
 * when it finishes. If the main or any background tasks return FAILURE, this node will fail immediately.
 */
export class ParallelBackground extends Parallel {
    nodeType = "ParallelBackground"

    run(blackboard: Blackboard = {}, { lastRun, introspector, rerun, registryLookUp = (x) => x as Node }: ParallelRunConfig = {}) {
        const results: Array<RunResult> = []

        let failed = false
        if (this.ranStart) {
            for (let currentIndex = 1; currentIndex < this.numNodes; ++currentIndex) {
                let lastRunForIndex = lastRun && (lastRun as StatusWithState).state[currentIndex]

                if (lastRunForIndex && isSuccess(lastRunForIndex)) {
                    const node = registryLookUp(this.nodes[currentIndex])
                    const startResult = node.blueprint.start(blackboard)
                    if (startResult === FAILURE) {
                        results[currentIndex] = startResult
                        failed = true
                        break
                    }
                }
            }
        }

        if (!rerun || !this.ranStart) {
            this.ranStart = true
            const startResult = this.blueprint.start(blackboard)
            if (startResult === FAILURE) return startResult
        }

        if (!failed) {
            for (let currentIndex = 0; currentIndex < this.numNodes; ++currentIndex) {
                let lastRunForIndex = lastRun && (lastRun as StatusWithState).state[currentIndex]

                if (lastRunForIndex && !isRunning(lastRunForIndex)) {
                    results[currentIndex] = lastRunForIndex
                    if (currentIndex === 0) break
                    if (isFailure(lastRunForIndex)) break
                }
                const node = registryLookUp(this.nodes[currentIndex])
                const isRunningState = isSuccess(lastRunForIndex) ? false : rerun
                const newLastRunForIndex = isSuccess(lastRunForIndex) ? false : lastRunForIndex
                const result = node.run(blackboard, { lastRun: newLastRunForIndex, introspector, rerun: isRunningState, registryLookUp })
                results[currentIndex] = result

                if (currentIndex === 0 && isFailure(result)) break
            }
        }

        const endResult = this.calcResult(results)
        if (isFailure(endResult) || isSuccess(results[0])) {
            this.blueprint.end(blackboard)

            /*
			for (const n of this.nodes) {
				(n as Node).blueprint.end(blackboard);
			}
			*/
        }
        // TODO: instropector result might need to change...
        if (introspector) {
            const running = !!results.find((x) => isRunning(x))
            const debugResult = running ? RUNNING : (endResult as boolean)
            introspector.wrapLast(this.numNodes, this, debugResult, blackboard)
        }

        return isSuccess(results[0]) ? SUCCESS : endResult
    }

    abort(blackboard: Blackboard, { registryLookUp = (x) => x as Node, lastRun }: ParallelRunConfig = {}) {
        this.blueprint.abort(blackboard, { registryLookUp, lastRun })

        // call abort() on parallel nodes
        for (const n of this.nodes) {
            ;(n as Node).abort(blackboard, { registryLookUp, lastRun })
        }
    }

    protected calcResult(results: Array<RunResult>): RunResult {
        if (results.includes(FAILURE)) {
            return FAILURE
        }
        //const running = !!results.find((x) => isRunning(x));
        //return running ? { total: RUNNING, state: results } : SUCCESS;
        return { total: RUNNING, state: results }
    }
}

function isRunning(result: RunResult | undefined): boolean {
    return result === RUNNING || (typeof result === "object" && result.total === RUNNING)
}

function isFailure(result: RunResult | undefined): boolean {
    return result === FAILURE || (typeof result === "object" && result.total === FAILURE)
}

function isSuccess(result: RunResult | undefined): boolean {
    return result === SUCCESS || (typeof result === "object" && result.total === SUCCESS)
}
