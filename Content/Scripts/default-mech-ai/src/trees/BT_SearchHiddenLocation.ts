import { Sequence } from "behaviortree"
import { Vector } from "types"
import { EQSArgument, EQSQueryType } from "../../../types/enums"
import { AIBlackboard } from "../blackboard"
import { BTT_EQSSetArgumentVector } from "../tasks/environment/BTT_EQSSetArgument"
import { BTT_MoveTo } from "../tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"

/**
 *
 *
 * @param searchLocation
 *
 * @returns
 */
export const BT_SearchHiddenLocation = (searchLocation: Vector) =>
    new Sequence({
        nodes: [
            BTT_EQSSetArgumentVector(EQSQueryType.Hidden, EQSArgument.TargetPredictedLocation, (blackboard: AIBlackboard) => searchLocation),
            BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
            BTT_SetFocalPoint("hiddenLocation"),
            BTT_MoveTo("hiddenLocation"),
            BTT_SetValue((blackboard: AIBlackboard) => (blackboard.hiddenLocation = undefined)),
        ],
    })
