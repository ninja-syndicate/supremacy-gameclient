import {FAILURE, RUNNING, SUCCESS, Task} from 'behaviortree'
import {AI} from "../index"
import {Ability, AbilityStatus} from "enums";
import {IsIntVector} from "../utils"
import {AIBlackboard} from "../blackboard"

/**
 * Performs a special attack. 
 * 
 * @param blackboardKey IntVector
 */
export const BTT_SpecialAttack = (blackboardKey: keyof AIBlackboard) => new Task({
    run: (blackboard: AIBlackboard) => {
        const location = blackboard[blackboardKey];
        if (!location || !IsIntVector(location))
            return FAILURE;
        
        AI.TrySpecialAttack(location);
        const status = AI.QueryAbilityStatus(Ability.SpecialAttack);
        switch (status) {
            case AbilityStatus.Running:
                return RUNNING;
            case AbilityStatus.Failed:
                return FAILURE;
            case AbilityStatus.Finished:
                return SUCCESS;
            default:
                return FAILURE;
        }
    }
});