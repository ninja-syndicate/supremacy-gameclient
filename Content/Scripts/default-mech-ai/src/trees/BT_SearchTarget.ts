import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "../../../types/enums"
import { AIBlackboard } from "../blackboard"
import { ParallelBackground } from "../branches/ParallelBackground"
import { IsSet } from "../decorators/IsSet"
import { BTT_ClearTarget } from "../tasks/BTT_ClearTarget"
import { BTT_EQSSetArgumentVector } from "../tasks/environment/BTT_EQSSetArgument"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/environment/BTT_RunEQSQuery"
import { BT_SetFocal } from "./BT_SetFocal"

/**
 * Behavior for searching the target.
 * 
 * 
 */
export const BT_SearchTarget = new Sequence({
    nodes: [
        new ParallelBackground({
            nodes: [
                new Sequence({
                    nodes: [
                        IsSet(BTT_MoveTo("targetLastKnownLocation"), "targetLastKnownLocation"),
                        IsSet(
                            new Sequence({
                                nodes: [
                                    BTT_EQSSetArgumentVector(
                                        EQSQueryType.Hidden,
                                        EQSArgument.TargetPredictedLocation,
                                        (blackboard: AIBlackboard) => blackboard.targetPredictedLocation,
                                    ),
                                    BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
                                    BTT_MoveTo("hiddenLocation"),
                                ],
                            }),
                            "targetPredictedLocation",
                        ),
                    ],
                }),
                BT_SetFocal,
            ],
        }),
        BTT_ClearTarget
    ],
})
