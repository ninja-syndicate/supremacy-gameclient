import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { EnvironmentQueryStatus, EQSQueryType } from "enums"
import { EnvironmentQuery } from "types"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

/**
 * Runs the specified environment query.
 *
 * Depending on the environment query type, you may need to execute
 * {@link BTT_EQSSetArgument} to set the arguments for the query before
 * executing this task.
 *
 * @see {@link AI.EQS_Query} for additional details.
 *
 * @param query The type of EQS query to run.
 * @param blackboardKey The key of blackboard where the resulting location will
 * be stored.
 */
export const BTT_RunEQSQuery = (query: EQSQueryType, blackboardKey: keyof AIBlackboard) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            blackboard.eqsResults[query] = { status: EnvironmentQueryStatus.Processing }
            AI.EQS_Query(query)
            return SUCCESS
        },

        run: (blackboard: AIBlackboard) => {
            const result: EnvironmentQuery = blackboard.eqsResults[query]
            if (!result) return FAILURE

            switch (result.status) {
                case EnvironmentQueryStatus.Processing:
                    return RUNNING
                case EnvironmentQueryStatus.Failed:
                    return FAILURE
                case EnvironmentQueryStatus.Success:
                    blackboard[blackboardKey as string] = blackboard.eqsResults[query].location
                    return SUCCESS
                default:
                    return FAILURE
            }
        },
    })
