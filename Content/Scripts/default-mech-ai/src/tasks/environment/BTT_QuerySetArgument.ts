import { SUCCESS, Task } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { Vector } from "types"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"

/**
 * Sets the string {@link argument} for the environment query {@link queryType}.
 *
 * @param queryType The type of environment query to set the argument for
 * @param argument The argument type to set. This must be compatible with with specified {@link queryType}.
 * @param func A function that provides the string argument value.
 */
export const BTT_QuerySetArgumentString = (queryType: EQSQueryType, argument: EQSArgument, func: (blackboard: AIBlackboard) => string) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            const value: string = func(blackboard)
            AI.EQS_SetArgumentString(queryType, argument, value)
            return SUCCESS
        },
    })

/**
 * Sets the vector {@link argument} for the environment query {@link queryType}.
 *
 * @param queryType The type of environment query to set the argument for
 * @param argument The argument type to set. This must be compatible with with specified {@link queryType}.
 * @param func A function that provides the Vector argument value.
 */
export const BTT_QuerySetArgumentVector = (queryType: EQSQueryType, argument: EQSArgument, func: (blackboard: AIBlackboard) => Vector) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            const value: Vector = func(blackboard)
            AI.EQS_SetArgumentVector(queryType, argument, value)
            return SUCCESS
        },
    })
