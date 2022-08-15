import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { MovementResult } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"
import { IsVector } from "../../utils"
import { ENABLE_DEBUGGING } from "@root/aiconfig"

// TODO: test timeout after getting setTimeout done and refactor a bit.
// TODO: do implementation for timeout and change comments.
/**
 * Makes AI move to a specified location.
 *
 * You may want to use {@link observeBlackboardKey} if you want to track the location AI is moving to (e.g. {@link AIBlackboard.TargetLastKnownLocation}). Also,
 * using a large value of {@link acceptanceRadius} is recommended to prevent AI potentially getting stuck for a while if the destination is occupied by
 * something else.
 *
 * It's recommended to use {@link BTT_RunEQSQuery} in combination with this.
 *
 * @see {@link AI.MoveToVector} for additional details.
 *
 * @param {Vector} blackboardKey The location where the AI will move to
 * @param {boolean} observeBlackboardKey Whether the change in the location that AI is moving to will make a new move to request
 * @param {number} [acceptanceRadius=600] Fixed distance added to threshold between AI and goal location in destination reach test
 * @param {number} [timeout=20] The timeout before giving up. This is not implemented yet
 */
export const BTT_MoveTo = (blackboardKey: keyof AIBlackboard, observeBlackboardKey: boolean = false, acceptanceRadius: number = 600, timeout: number = 20) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            if (ENABLE_DEBUGGING) {
                console.log("BTT_MoveTo: Move To called.")
            }

            // Check if the blackboard key is a Vector.
            const value = blackboard[blackboardKey]
            if (!value || !IsVector(value)) return FAILURE

            if (ENABLE_DEBUGGING) {
                console.log("BTT_MoveTo: Move To Location: " + JSON.stringify(value))
            }

            const success: boolean = AI.MoveToVector(value, acceptanceRadius)
            return success ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            // Make a new MoveTo request if observing blackboard key.
            if (observeBlackboardKey) {
                const location = blackboard[blackboardKey]
                if (!location || !IsVector(location)) return FAILURE

                const success: boolean = AI.MoveToVector(location, acceptanceRadius)
                if (!success) return FAILURE
            }

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
