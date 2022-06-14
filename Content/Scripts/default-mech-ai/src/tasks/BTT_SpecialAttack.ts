import { FAILURE, RUNNING, RunResult, SUCCESS, Task } from "behaviortree"
import { AI } from "../index"
import { Ability, Status } from "enums"
import { IsVector } from "../utils"
import { AIBlackboard } from "../blackboard"

/**
 * Performs a special attack.
 *
 * @param blackboardKey IntVector
 */
export const BTT_SpecialAttack = (blackboardKey: keyof AIBlackboard) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            const location = blackboard[blackboardKey]
            if (!location || !IsVector(location)) return FAILURE

            // TODO: move this to decorator?
            const hasSecondaryWeapon = blackboard.secondaryWeapon !== undefined && blackboard.secondaryWeapon !== null
            if (!hasSecondaryWeapon) return FAILURE

            const success: boolean = AI.TrySpecialAttack(location)
            return success ? SUCCESS : FAILURE
        },

        run: (blackboard: AIBlackboard) => {
            const status = AI.QueryStatus(Ability.SpecialAttack)

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
    })
