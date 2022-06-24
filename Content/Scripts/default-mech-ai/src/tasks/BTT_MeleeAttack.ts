import { AI } from "../index"

import { RUNNING, Task } from "behaviortree"
import { WeaponTag } from "enums"
import { AIBlackboard } from "../blackboard"

/**
 * Makes the AI perform a melee attack using the specified melee weapon tag.
 *
 * @param tag A melee weapon tag.
 */
export const BTT_MeleeAttack = (tag: WeaponTag) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            // TODO: add melee tag check at the start and return false if is not.

            AI.WeaponTrigger(tag)
            return RUNNING
        },
        end: (blackboard: AIBlackboard) => {
            AI.WeaponRelease(tag)
        },
        abort: (blackboard: AIBlackboard) => {
            AI.WeaponRelease(tag)
        },
    })
