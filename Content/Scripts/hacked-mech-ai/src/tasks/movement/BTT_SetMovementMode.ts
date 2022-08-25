import { FAILURE, SUCCESS, Task } from "behaviortree"
import { MovementMode } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"

/**
 * Sets the current AI movement mode to the specified {@link movementMode}.
 *
 * @param movementMode The movement mode to set to. @see {@link MovementMode}
 */
export const BTT_SetMovementMode = (movementMode: MovementMode) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const success: boolean = AI.SetMovementMode(movementMode)
            return success ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            return SUCCESS
        },
    })
