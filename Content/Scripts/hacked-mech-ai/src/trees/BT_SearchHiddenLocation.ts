import { Sequence } from "behaviortree"
import { Vector } from "types"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_QuerySetArgumentVector } from "@tasks/environment/BTT_QuerySetArgument"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "@tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BTT_SetFocalPoint } from "@tasks/focus/BTT_SetFocalPoint"
import { BT_DefaultMoveTo } from "@trees/movement/BT_MovementMode"


/**
 * Behavior for searching possible hidden location based on the provided search location.
 *
 * Makes an environment query to get a possible hidden location using the provided search location and moves to it (@see {@link EQSQueryType.Hidden}). Note that
 * the hidden environment query requires the argument {@link EQSArgument.TargetPredictedLocation} to be set before it gets called.
 *
 * @param {Vector} searchLocation - The location that is used to generate a possible hidden location from.
 */
export const BT_SearchHiddenLocation = (searchLocation: keyof AIBlackboard) =>
    new Sequence({
        nodes: [
            BTT_QuerySetArgumentVector(
                EQSQueryType.Hidden,
                EQSArgument.TargetPredictedLocation,
                (blackboard: AIBlackboard) => blackboard[searchLocation] as Vector,
            ),
            BTT_RunEQSQuery(EQSQueryType.Hidden, "hiddenLocation"),
            BTT_SetFocalPoint("hiddenLocation"),
            BT_DefaultMoveTo("hiddenLocation"),
            BTT_SetValue((blackboard: AIBlackboard) => (blackboard.hiddenLocation = undefined)),
        ],
    })
