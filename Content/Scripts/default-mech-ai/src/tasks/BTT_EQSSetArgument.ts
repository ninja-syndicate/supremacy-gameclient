import {Task, SUCCESS, FAILURE} from 'behaviortree'
import {AI} from "../index"
import {AIBlackboard, BlackboardKey} from "../blackboard"
import {IsVector, IsWarMachine} from "../utils"
import {add, multiply} from "../helper"
import { EQSArgument, EQSQueryType } from 'enums'
import { Vector } from 'types'

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
export const BTT_EQSSetArgumentString = (queryType: EQSQueryType, key: EQSArgument, func: (blackboard: AIBlackboard) => string) => new Task({
    run: (blackboard: AIBlackboard) => {
        const value: string = func(blackboard);

        AI.EQS_SetArgumentString(queryType, key, value);
        return SUCCESS;
    }
});

/**
 * Makes the AI look at a War Machine or location.
 *
 * Call {@link BTT_StopFocus} to stop looking at anything
 * @param blackboardKey WarMachine or IntVector
 * @constructor
 */
 export const BTT_EQSSetArgumentVector = (queryType: EQSQueryType, key: EQSArgument, func: (blackboard: AIBlackboard) => Vector) => new Task({
    run: (blackboard: AIBlackboard) => {
        const value = func(blackboard);

        AI.EQS_SetArgumentVector(queryType, key, value);
        return SUCCESS;
    }
});