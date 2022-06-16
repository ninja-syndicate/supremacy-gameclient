import { Selector, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { WeaponTag } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_TriggerWeapon } from "../tasks/BTT_TriggerWeapon"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_MeleeAttack } from "../tasks/BTT_MeleeAttack"
import { AIBlackboard } from "../blackboard"
import { BT_GetCover } from "./BT_GetCover"
import { Predicate } from "../decorators/Predicate"
import { ForceSuccess } from "../decorators/ForceSuccess"

/**
 *
 */
export const BT_CloseCombat = new Sequence({
    nodes: [
        ForceSuccess(
            new Selector({
                nodes: [BTT_SetFocalPoint("target"), BTT_SetFocalPoint("targetLastKnownLocation")],
            }),
        ),
        new ParallelBackground({
            nodes: [
                BTT_MeleeAttack(WeaponTag.Melee),
                new Selector({
                    nodes: [
                        Predicate(BT_GetCover, (blackboard: AIBlackboard) => {
                            let self = blackboard.input.self
                            return (self.health + self.shield) / (self.healthMax + self.shieldMax) <= 0.3
                        }),
                        BTT_MoveTo("targetLastKnownLocation"),
                    ],
                }),
            ],
        }),
    ],
})
