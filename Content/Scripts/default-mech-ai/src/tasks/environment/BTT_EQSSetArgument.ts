import { SUCCESS, Task } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { Vector } from "types"
import { AIBlackboard } from "../../blackboard"
import { AI } from "../../index"

/**
 *
 * @param queryType
 * @param key
 * @param func
 * @returns
 */
export const BTT_EQSSetArgumentString = (queryType: EQSQueryType, key: EQSArgument, func: (blackboard: AIBlackboard) => string) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            const value: string = func(blackboard)

            AI.EQS_SetArgumentString(queryType, key, value)
            return SUCCESS
        },
    })

/**
 *
 * @param queryType
 * @param key
 * @param func
 * @returns
 */
export const BTT_EQSSetArgumentVector = (queryType: EQSQueryType, key: EQSArgument, func: (blackboard: AIBlackboard) => Vector) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            const value = func(blackboard)

            AI.EQS_SetArgumentVector(queryType, key, value)
            return SUCCESS
        },
    })
