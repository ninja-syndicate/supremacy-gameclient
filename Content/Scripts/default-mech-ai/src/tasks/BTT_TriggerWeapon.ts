import { SUCCESS, Task } from "behaviortree"

import { WeaponTag } from "enums"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

/**
 * Triggers the specified weapon(s) by tag.
 *
 * If the specified weapon(s) is already triggered, this will not do anything.
 *
 * Note that this task will return SUCCESS immediately and if this task is
 * aborted by {@link ObserverAborts} the triggered weapon(s) by tag will be
 * released.
 *
 * @see {@link AI.WeaponTrigger} for details.
 *
 * @param tag The weapon tag to trigger
 */
export const BTT_TriggerWeapon = (tag: WeaponTag) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            AI.WeaponTrigger(tag)
            return SUCCESS
        },

        abort: (blackboard: AIBlackboard) => {
            AI.WeaponRelease(tag)
        },
    })
