import { FAILURE, RUNNING, Task } from "behaviortree"
import { WeaponTag } from "enums"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

/**
 * Makes the AI shoot the specified weapon(s) by tag.
 *
 *
 * The main difference between {@link BTT_TriggerWeapon} and this task is that
 *
 *
 * @param tag
 */
export const BTT_Shoot = (tag: WeaponTag) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            const idx: number = blackboard.input.self.weapons.findIndex((w) => w.tags.findIndex((t) => t === tag))
            if (idx === -1) return FAILURE

            // TODO: add check for shootable tag and fail if it isn't.

            const hasAmmo = AI.WeaponGetAmmoByTag(tag) > 0

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
