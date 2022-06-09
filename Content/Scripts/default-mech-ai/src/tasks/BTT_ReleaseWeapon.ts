import {AI} from "../index"

import {FAILURE, RUNNING, SUCCESS, Task} from 'behaviortree'
import {Ability, AbilityStatus} from "enums"
import {IsVector} from "../utils"
import {AIBlackboard} from "../blackboard"
import {WeaponTag} from "enums"

/**
 * Releases the triggered weapon by tag.
 */
export const BTT_ReleaseWeapon = (tag: WeaponTag) => new Task({
    run: () => {
        AI.WeaponRelease(tag);
        return SUCCESS;
    }
});