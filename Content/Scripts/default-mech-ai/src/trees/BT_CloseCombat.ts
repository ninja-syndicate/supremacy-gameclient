import { Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/BTT_SetFocalPoint"
import { WeaponTag } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_TriggerWeapon } from "../tasks/BTT_TriggerWeapon"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_MeleeAttack } from "../tasks/BTT_MeleeAttack"

/**
 *
 */
export const BT_CloseCombat = new ParallelBackground({
    nodes: [
        BTT_MeleeAttack(WeaponTag.Melee),
        new Sequence({
            nodes: [BTT_SetFocalPoint("target"), BTT_MoveTo("targetLastKnownLocation")],
        })
    ],
})
