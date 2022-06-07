import {AI} from "../index"

import {FAILURE, RUNNING, SUCCESS, Task} from 'behaviortree'
import {AIBlackboard} from "../blackboard"
import {WeaponTag} from "enums"

/**
 * Shoots the specified weapon.
 */
 export const BTT_MeleeAttack = (tag: WeaponTag) => new Task({
    run: () => {
        AI.WeaponTrigger(tag);
        return RUNNING;
    },
    
    end: () => {
        AI.WeaponRelease(tag);
    }
});