import { SUCCESS, Task } from "behaviortree"

import { AI } from "../index"
import { WeaponTag } from "enums"
import { AIBlackboard } from "../blackboard"

/**
 * Triggers the specified weapon by tag.
 */
export const BTT_Wait = (seconds: number) =>
    new Task({
        run: (blackboard: AIBlackboard) => {
            return SUCCESS
        },

        end: () => {
            console.log("end called")
        },

        abort: () => {
            console.log("abort called")
        },
    })
