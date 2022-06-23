import { SUCCESS, Task } from 'behaviortree';

import { WeaponTag } from "enums";
import { AI } from "../index";

/**
 * Triggers the specified weapon by tag.
 */
export const BTT_TriggerWeapon = (tag: WeaponTag) => new Task({
    run: () => {
        AI.WeaponTrigger(tag);
        return SUCCESS;
    },

    end: () => {
        console.log("end called")
    },

    abort: () => {
        console.log("abort called")
        AI.WeaponRelease(tag)
    }
});