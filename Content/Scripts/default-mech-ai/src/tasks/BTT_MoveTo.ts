import { Task, SUCCESS, FAILURE, RUNNING } from "behaviortree"
import { AI } from "../index"
import { AIBlackboard } from "../blackboard"
import { IsVector } from "../utils"
import { MovementResult } from "enums"

/**
 * Move to a location.
 *
 * It's recommended to use {@link BTT_RunEQSQuery} in combination with this.
 * @param blackboardKey IntVector
 * @param {number} [acceptanceRadius=800] Fixed distance added to threshold between AI and goal location in destination reach test.
 */
export const BTT_MoveTo = (blackboardKey: keyof AIBlackboard, acceptanceRadius: number = 800) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const value = blackboard[blackboardKey]
            if (!value || !IsVector(value)) return FAILURE

            const success: boolean = AI.MoveToVector(value, acceptanceRadius)
            return success ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            const status = AI.QueryMovementResult()
            switch (status) {
                case MovementResult.Moving:
                    return RUNNING
                case MovementResult.Success:
                    return SUCCESS
                case MovementResult.Aborted:
                    return FAILURE
                case MovementResult.Invalid:
                    return FAILURE
                default:
                    return FAILURE
            }
        },
    })
