import { FAILURE, RUNNING, Task } from "behaviortree"
import { WeaponTag } from "enums"
import { AIBlackboard } from "../blackboard"
import { AI } from "../index"

/**
 * Shoots the specified weapon.
 */
export const BTT_Shoot = (tag: WeaponTag) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            const idx: number = blackboard.input.self.weapons.findIndex((w) => w.tags.findIndex((t) => t === tag))
            if (idx === -1) return FAILURE

            const hasAmmo = AI.WeaponGetAmmoByTag(tag) > 0

            if (hasAmmo) {
                AI.WeaponTrigger(tag, blackboard.targetLastKnownLocation)
            } else {
                AI.WeaponRelease(tag)
            }
            return hasAmmo ? RUNNING : FAILURE
        },

        end: () => {
            AI.WeaponRelease(tag)
        },

        abort: () => {
            AI.WeaponRelease(tag)
        },
    })
