import { ParallelBackground } from "@branches/ParallelBackground"
import { BT_SetFocal } from "@trees/BT_SetFocal"
import { BT_MoveToBattleZone } from "@trees/battlezone/BT_MoveToBattleZone"

/**
 * Parallel behavior for setting the focal point while moving to the main battle zone.
 */
export const BT_ParallelMoveToBattleZone = new ParallelBackground({
    nodes: [BT_MoveToBattleZone, BT_SetFocal],
})
