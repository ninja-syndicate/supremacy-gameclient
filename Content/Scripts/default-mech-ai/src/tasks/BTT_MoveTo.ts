import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { MovementResult } from "enums"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"
import { IsVector } from "../utils"

/**
 * Move to a location.
 *
 * It's recommended to use {@link BTT_RunEQSQuery} in combination with this.
 * @param blackboardKey IntVector
 * @param {number} [acceptanceRadius=800] Fixed distance added to threshold between AI and goal location in destination reach test.
 */

/**
 * Makes the AI move to a specified location.
 *
 *
 *
 * @see {@link AI.MoveToVector} for details.
 *
 * @param blackboardKey The location where the AI will move to.
 * @param observeBlackboardKey Whether the change in 
 * @param {number} [acceptanceRadius=800]
 * @param {number} [timeout=20] The timeout before giving up. This is not implemented yet. //TODO: do implementation for timeout.
 */
export const BTT_MoveTo = (blackboardKey: keyof AIBlackboard, observeBlackboardKey: boolean = false, acceptanceRadius: number = 800, timeout: number = 20) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const value = blackboard[blackboardKey]
            if (!value || !IsVector(value)) return FAILURE

            const success: boolean = AI.MoveToVector(value, acceptanceRadius)
            return success ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            if (observeBlackboardKey) {
                const location = blackboard[blackboardKey]
                if (!location || !IsVector(location)) return FAILURE

                const success: boolean = AI.MoveToVector(location, acceptanceRadius)
                if (!success) return FAILURE
            }
            // TODO: test timeout after getting setTimeout done.

            const status = AI.QueryMovementResult()
            switch (status) {
                case MovementResult.Moving:
                    return RUNNING
                case MovementResult.Success:
                    return SUCCESS
                case MovementResult.Aborted:
                    return FAILURE
                default:
                    return FAILURE
            }
        },
    })
