import {FAILURE, RUNNING, RunResult, SUCCESS, Task} from 'behaviortree'
import {AI} from "../index"
import {Ability, Status} from "enums";
import {IsVector} from "../utils"
import {AIBlackboard} from "../blackboard"

/**
 * Performs a special attack. 
 * 
 * @param blackboardKey IntVector
 */
export const BTT_SpecialAttack = (blackboardKey: keyof AIBlackboard) => new Task({
    start: (blackboard: AIBlackboard) => {
    },

    run: (blackboard: AIBlackboard) => {
        const location = blackboard[blackboardKey];
        if (!location || !IsVector(location))
            return FAILURE;

        const hasSecondaryWeapon = blackboard.secondaryWeapon !== undefined && blackboard.secondaryWeapon !== null;
        if (!hasSecondaryWeapon)
            return FAILURE;

        if (!blackboard.canUseSpecialAttack)
            return FAILURE;

        const success: boolean = AI.TrySpecialAttack(location);
        if (success) {
            blackboard.canUseSpecialAttack = false;
            console.log("special attack location" + JSON.stringify(location));
        }

        const status = AI.QueryStatus(Ability.SpecialAttack);

        // TODO: clean up
        switch (status) {
            case Status.Running:
                return RUNNING;
            case Status.Failed:
                return FAILURE;
            case Status.Finished:
                /*
                setTimeout(() => {
                    blackboard.canUseSpecialAttack = true;
                }, (60 / blackboard.secondaryWeapon.rateOfFire) * 1000);
                */
                return SUCCESS;
            default:
                return FAILURE;
        }
    }
});