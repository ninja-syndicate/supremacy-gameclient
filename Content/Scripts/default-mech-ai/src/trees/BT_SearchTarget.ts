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

export const BT_SearchTarget = new Sequence({
    nodes: [
        new ParallelBackground({
            nodes: [
                IsSet(
                    new Sequence({
                        nodes: [BTT_MoveTo("targetLastKnownLocation")],
                    }),
                    "targetLastKnownLocation",
                ),
                // TODO: smooth out the predication focal point
                IsSet(BTT_SetFocalPoint("targetPredictedLocation"), "targetPredictedLocation"),
            ],
        }),
        IsSet(
            new Sequence({
                nodes: [
                    BTT_EQSSetArgumentVector(
                        EQSQueryType.Hidden,
                        EQSArgument.TargetPredictedLocation,
                        (blackboard: AIBlackboard) => blackboard.targetPredictedLocation,
                    ),
                    BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
                    BTT_SetFocalPoint("hiddenLocation"),
                    BTT_MoveTo("hiddenLocation"),
                ],
            }),
            "targetPredictedLocation",
        ),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.targetLastKnownLocation = undefined)),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.targetPredictedLocation = undefined)),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.target = null)),
    ],
})
