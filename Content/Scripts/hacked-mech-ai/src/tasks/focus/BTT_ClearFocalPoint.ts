import { SUCCESS, Task } from "behaviortree"
import { AI } from "../../index"

/**
 * Clears the focal point of AI set by {@link BTT_SetFocalPoint}.
 */
export const BTT_ClearFocalPoint = new Task({
    run: () => {
        AI.ClearFocus()
        return SUCCESS
    },
})