import {AI} from "../index";
import {AIBlackboard} from "../blackboard";
import {FAILURE, RUNNING, SUCCESS, Task} from "behaviortree";
import {AbilityStatus, WeaponTag} from "enums";

/**
 * Shoots the specified weapon.
 */
export const BTT_Shoot = (tag: WeaponTag) => new Task({
    run: () => {
        const hasAmmo = AI.WeaponGetAmmoByTag(tag) > 0;

        if (hasAmmo) {
            AI.WeaponTrigger(tag);
        } else {
            AI.WeaponRelease(tag);
        }
        return hasAmmo ? RUNNING : FAILURE;
    }
});