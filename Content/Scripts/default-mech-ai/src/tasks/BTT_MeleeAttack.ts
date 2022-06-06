import {AI} from "../index"

import {FAILURE, RUNNING, SUCCESS, Task} from 'behaviortree'
import {AbilityStatus} from "enums"
import {IsIntVector} from "../utils"
import {AIBlackboard} from "../blackboard"

/**
 * Performs a melee attack in the direction AI is facing. 
 */
export const BTT_MeleeAttack = () => new Task({
    run: () => {
        const status = AI.QueryAbilityStatus(Ability.MeleeAttack);
        if (status != AbilityStatus.Ready)
            return FAILURE;

        return SUCCESS;
    }

    /*
    run: (blackboard: AIBlackboard) => {
        if (!location || !IsIntVector(location))
            return FAILURE;
        
        const result = AI.SpecialAttack(location);
        switch (result) {
            case AbilityStatus.Running:
                return RUNNING;
            case AbilityStatus.Failed:
                return FAILURE;
            case AbilityStatus.Success:
                return SUCCESS;
        };
    },
    */
});