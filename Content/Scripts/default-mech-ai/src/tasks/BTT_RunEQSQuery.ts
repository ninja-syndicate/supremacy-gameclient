import {FAILURE, RUNNING, SUCCESS, Task} from 'behaviortree'
import {AI} from "../index"
import {EnvironmentQueryStatus, EQSQueryType} from "enums"
import {EnvironmentQuery} from "types"
import {AIBlackboard} from "../blackboard"

/**
 * Runs an environment query and returns the resulting location.
 * @param query The query to run
 * @param blackboardKey IntVector
 */
export const BTT_RunEQSQuery = (query: EQSQueryType, blackboardKey: keyof AIBlackboard) => new Task({
    start: (blackboard: AIBlackboard) => {
        blackboard.eqsResults[query] = {status: EnvironmentQueryStatus.Processing};
        AI.EQS_Query(query)
        return SUCCESS;
    },

    run: (blackboard: AIBlackboard) => {
        const result: EnvironmentQuery = blackboard.eqsResults[query];

        if (!result)
            return FAILURE
        switch (result.status) {
            case EnvironmentQueryStatus.Processing:
                return RUNNING
            case EnvironmentQueryStatus.Failed:
                return FAILURE
            case EnvironmentQueryStatus.Success:
                blackboard[blackboardKey as string] = blackboard.eqsResults[query].location
                return SUCCESS
            default:
                console.log("can this case ever happen")
                return SUCCESS
        }
    },
})
