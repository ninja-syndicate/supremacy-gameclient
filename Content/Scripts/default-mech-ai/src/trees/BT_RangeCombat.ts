import { Parallel, ParallelSelector, Selector, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_Shoot } from "../tasks/BTT_Shoot"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentString } from "../tasks/BTT_EQSSetArgument"
import { Predicate } from "../decorators/Predicate"
import { BT_GetCover } from "./BT_GetCover"

/**
 *
 */
export const BT_RangeCombat = new Sequence({
    nodes: [
        BTT_SetFocalPoint("target"),
        new ParallelBackground({
            nodes: [
                new Parallel({
                    nodes: [BTT_Shoot(WeaponTag.PrimaryLeftArm), BTT_Shoot(WeaponTag.PrimaryRightArm)],
                }),
                new Selector({
                    nodes: [
                        Predicate(BT_GetCover, (blackboard: AIBlackboard) => {
                            let self = blackboard.input.self
                            return (self.health + self.shield) / (self.healthMax + self.shieldMax) <= 0.3
                        }),
                        new Sequence({
                            nodes: [
                                BTT_EQSSetArgumentString(EQSQueryType.Strafe, EQSArgument.TargetHash, (blackboard: AIBlackboard) => blackboard.target.hash),
                                BTT_RunEQSQuery(EQSQueryType.Strafe, "strafeLocation"),
                                BTT_MoveTo("strafeLocation"),
                            ],
                        }),
                    ],
                }),
            ],
        }),
    ],
})
