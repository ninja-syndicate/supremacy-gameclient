import {AI} from "../index";
import {AIBlackboard} from "../blackboard";
import {FAILURE, RUNNING, SUCCESS, Task} from "behaviortree";
import {Status, WeaponTag} from "enums";

/**
 * Shoots the specified weapon.
 */
export const BTT_Shoot = (tag: WeaponTag) => new Task({
    run: (blackboard: AIBlackboard) => {
        const idx: number = blackboard.input.self.weapons.findIndex(w => w.tags.findIndex(t => t === tag));
        if (idx === -1)
            return FAILURE;

        // TODO: Remove this and maintain ammo from blackboard.
        const hasAmmo = AI.WeaponGetAmmoByTag(tag) > 0;

        if (hasAmmo) {
            AI.WeaponTrigger(tag, blackboard.targetLastKnownLocation);
        } else {
            AI.WeaponRelease(tag);
        }
        return hasAmmo ? RUNNING : FAILURE;
    },

    end: () => {
        AI.WeaponRelease(tag);
    }
});