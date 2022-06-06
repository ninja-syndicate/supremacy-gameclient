import {AI} from "../index";
import {AIBlackboard} from "../blackboard";
import {FAILURE, RUNNING, SUCCESS, Task} from "behaviortree";
import {AbilityStatus, WeaponTag} from "enums";

/**
 * Shoots the specified weapon.
 */
export const BTT_Shoot = (tag: WeaponTag) => new Task({
    run: (blackboard: AIBlackboard) => {
        const weaponLeftArmAmmo: number = AI.WeaponGetAmmo(blackboard.leftArmWeapon.hash);
        const weaponRightArmAmmo: number = AI.WeaponGetAmmo(blackboard.rightArmWeapon.hash);


        switch (status) {
            case AbilityStatus.Ready:
                AI.WeaponTrigger(WeaponTag.Melee);
                return RUNNING;
            case AbilityStatus.Running:
                return RUNNING;
            case AbilityStatus.Success:
                return SUCCESS;
            default:
                return FAILURE;
        };
    }
});