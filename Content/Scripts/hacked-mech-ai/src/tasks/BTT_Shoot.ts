import { FAILURE, RUNNING, SUCCESS, Task } from "behaviortree"
import { WeaponTag } from "enums"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

// TODO: Also checks whether the given weapon(s) by tag is actually shootable and return FAILURE otherwise.
/**
 * Makes AI shoot the specified weapon(s) by tag.
 *
 * The main difference between {@link BTT_TriggerWeapon} and this task is that this task will return RUNNING status instead of SUCCESS after triggering the
 * shootable weapon(s) by tag. If the given weapon(s) by tag does not have any ammo, the triggered weapon(s) will be released. And if there are multiple weapons
 * with the given tag, the total ammo of all those weapons will be used (@see {@link AI.WeaponGetAmmoByTag}).
 *
 * Releases triggered shootable weapon(s) when aborted.
 *
 * This task can be used with a {@link Parallel} or its variant branch node to perform shooting and moving at the same time (@see {@link BT_RangeCombat}).
 *
 * @param tag the shootable weapon tag to trigger
 */
export const BTT_Shoot = (tag: WeaponTag) =>
    new Task({
        start: (blackboard: AIBlackboard) => {
            // Check if AI has any weapons with the given tag.
            const idx: number = blackboard.input.self.weapons.findIndex((w) => w.tags.findIndex((t) => t === tag))
            return idx !== -1 ? SUCCESS : FAILURE
        },
        run: (blackboard: AIBlackboard) => {
            const hasAmmo: boolean = AI.WeaponGetAmmoByTag(tag) > 0

            if (hasAmmo) {
                AI.WeaponTrigger(tag, blackboard.targetLastKnownLocation)
            } else {
                AI.WeaponRelease(tag)
            }
            return hasAmmo ? RUNNING : FAILURE
        },

        abort: (blackboard: AIBlackboard) => {
            AI.WeaponRelease(tag)
        },
    })
