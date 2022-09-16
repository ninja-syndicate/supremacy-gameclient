import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_QuerySetArgumentFloat, BTT_QuerySetArgumentVector } from "@tasks/environment/BTT_QuerySetArgument"
import { BTT_RunEQSQuery } from "@tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { BT_SprintMoveTo } from "@trees/movement/BT_MovementMode"

/**
 * Getting a cover behavior.
 *
 * This behavior makes an environment query to get a cover location and moves to it.
 *
 * Note that this behavior will make your AI to sprint if capable.
 *
 * The cover environment query requires the arguments {@link EQSArgument.TargetLastKnownLocation} and {@link EQSArgument.LastHitLocation} to be set before it
 * gets called (@see {@link EQSQueryType.Cover}). In this behavior, if any of these are undefined, the current location of the AI will be used for the undefined
 * location.
 */
export const BT_GetCover = new Sequence({
    nodes: [
        BTT_QuerySetArgumentVector(EQSQueryType.Cover, EQSArgument.TargetLastKnownLocation, (blackboard: AIBlackboard) =>
            typeof blackboard.targetLastKnownLocation !== "undefined" ? blackboard.targetLastKnownLocation : blackboard.input.Self.Location,
        ),
        BTT_QuerySetArgumentVector(EQSQueryType.Cover, EQSArgument.LastHitLocation, (blackboard: AIBlackboard) =>
            typeof blackboard.lastHitLocation !== "undefined" ? blackboard.lastHitLocation : blackboard.input.Self.Location,
        ),
        BTT_QuerySetArgumentFloat(EQSQueryType.Cover, EQSArgument.GridSize, (blackboard: AIBlackboard) => 20000),
        BTT_RunEQSQuery(EQSQueryType.Cover, "coverLocation"),
        BT_SprintMoveTo("coverLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.coverLocation = undefined)),
    ],
})
