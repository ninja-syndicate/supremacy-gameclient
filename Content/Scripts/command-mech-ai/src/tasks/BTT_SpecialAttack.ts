import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { Action, Status } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { AI } from "@root/index"
import { IsVector } from "../utils"

/**
 * Makes AI perform a special attack.
 *
 * @param {Vector} blackboardKey The target location for the special attack
 *
 * @see {@link AI.TrySpecialAttack} for details.
 */
export const BTT_SpecialAttack = (blackboardKey: keyof AIBlackboard) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            // Check if the `blackboardKey` is a Vector.
            const location = blackboard[blackboardKey]
            if (!location || !IsVector(location)) return FAILURE

            // TODO: move this to decorator?
            const hasSecondaryWeapon = typeof blackboard.secondaryWeapon !== "undefined" && blackboard.secondaryWeapon !== null
            if (!hasSecondaryWeapon) return FAILURE

            const success: boolean = AI.TrySpecialAttack(location)
            if (success) blackboard.actionStatus.set(Action.SpecialAttack, true)

            return success ? SUCCESS : FAILURE
        },

        run: (blackboard: AIBlackboard) => {
            const status = AI.QueryStatus(Action.SpecialAttack)
            switch (status) {
                case Status.Running:
                    return RUNNING
                case Status.Failed:
                    return FAILURE
                case Status.Finished:
                    return SUCCESS
                default:
                    return FAILURE
            }
        },
        end: (blackboard: AIBlackboard) => {
            blackboard.actionStatus.set(Action.SpecialAttack, false)
        },
        abort: (blackboard: AIBlackboard) => {
            blackboard.actionStatus.set(Action.SpecialAttack, false)
        },
    })
