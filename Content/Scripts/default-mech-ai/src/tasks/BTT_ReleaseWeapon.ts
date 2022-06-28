import { AI } from "../index"

import { SUCCESS, Task } from "behaviortree"
import { WeaponTag } from "enums"
import { AIBlackboard } from "../blackboard"

/**
 * Releases the specified weapon(s) by tag.
 *
 * If the specified weapon(s) is already released, this will do nothing.
 *
 * @see {@link AI.WeaponRelease} for details.
 *
 * @param tag The weapon tag to release
 */
export const BTT_ReleaseWeapon = (tag: WeaponTag) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            AI.WeaponRelease(tag)
            return SUCCESS
        },
    })
