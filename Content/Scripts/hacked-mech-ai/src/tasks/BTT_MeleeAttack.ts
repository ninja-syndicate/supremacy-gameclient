import { AI } from "@root/index"
import { RUNNING, Task } from "behaviortree"
import { Action, WeaponTag } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"

// TODO: add melee tag check at the start and return false if is not.
/**
 * Makes AI perform a melee attack using the specified melee weapon(s) by tag.
 *
 * Similar to {@link BTT_Shoot}, the difference between {@link BTT_TriggerWeapon} and this task is that this task will return RUNNING status instead of SUCCESS
 * after triggering the melee weapon(s) by tag.
 *
 * Releases triggered melee weapon(s) when aborted.
 *
 * @param tag A melee weapon tag
 */
export const BTT_MeleeAttack = (tag: WeaponTag) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            AI.WeaponTrigger(tag)
            blackboard.actionStatus.set(Action.MeleeAttack, true)

            return RUNNING
        },
        end: (blackboard: AIBlackboard) => {
            AI.WeaponRelease(tag)
            blackboard.actionStatus.set(Action.MeleeAttack, false)
        },
        abort: (blackboard: AIBlackboard) => {
            AI.WeaponRelease(tag)
            blackboard.actionStatus.set(Action.MeleeAttack, false)
        },
    })
