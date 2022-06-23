import { AI } from "../index";

import { SUCCESS, Task } from 'behaviortree';
import { WeaponTag } from "enums";

/**
 * Releases the triggered weapon by tag.
 */
export const BTT_ReleaseWeapon = (tag: WeaponTag) => new Task({
    run: () => {
        AI.WeaponRelease(tag);
        return SUCCESS;
    }
});