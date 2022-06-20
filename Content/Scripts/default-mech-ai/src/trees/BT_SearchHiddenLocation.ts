import { Sequence, SUCCESS, Task } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { Vector } from "types"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"

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
            BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.hiddenLocation = undefined)),
        ],
    })
