import { AI } from "../index"

import { RUNNING, Task } from "behaviortree"
import { WeaponTag } from "enums"

/**
 * Performs a melee attack using the specified melee weapon.
 */
export const BTT_MeleeAttack = (tag: WeaponTag) =>
    new Task({
        run: () => {
            AI.WeaponTrigger(tag)
            return RUNNING
        },
        end: () => {
            AI.WeaponRelease(tag)
        },
        abort: () => {
            AI.WeaponRelease(tag)
        },
    })
