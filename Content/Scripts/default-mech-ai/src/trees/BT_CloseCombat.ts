import { Parallel, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/BTT_SetFocalPoint"
import { WeaponTag } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_TriggerWeapon } from "../tasks/BTT_TriggerWeapon"

/**
 * 
 */
export const BT_CloseCombat = new Parallel({
    nodes: [
        new Sequence({
            nodes: [BTT_SetFocalPoint("target"), BTT_MoveTo("targetLastKnownLocation")],
        }),
        BTT_TriggerWeapon(WeaponTag.Melee),
    ],
})
