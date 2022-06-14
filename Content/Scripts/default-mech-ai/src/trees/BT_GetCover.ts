import { Parallel, Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_Shoot } from "../tasks/BTT_Shoot"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentString } from "../tasks/BTT_EQSSetArgument"

/**
 *
 */
export const BT_GetCover = new Sequence({
    nodes: [
        BTT_SetFocalPoint("target"),
        new ParallelBackground({
            nodes: [
                // TODO: should be parallel selector, but can't use it right now...
                new Parallel({
                    nodes: [BTT_Shoot(WeaponTag.PrimaryLeftArm), BTT_Shoot(WeaponTag.PrimaryRightArm)],
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
})
