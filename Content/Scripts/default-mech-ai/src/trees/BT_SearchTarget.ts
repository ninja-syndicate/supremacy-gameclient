import { Sequence, SUCCESS, Task } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { IsSet } from "../decorators/IsSet"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { BT_SetFocal } from "./BT_SetFocal"
import { BTT_ClearTarget } from "../tasks/BTT_ClearTarget"

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
