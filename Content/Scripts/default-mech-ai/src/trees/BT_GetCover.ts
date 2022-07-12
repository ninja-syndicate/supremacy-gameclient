import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "enums"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_QuerySetArgumentVector } from "@tasks/environment/BTT_QuerySetArgument"
import { BTT_MoveTo } from "@tasks/movement/BTT_MoveTo"
import { BTT_RunEQSQuery } from "@tasks/environment/BTT_RunEQSQuery"
import { BTT_SetValue } from "@tasks/BTT_SetValue"

/**
 * Getting a cover behavior.
 *
 * This behavior makes an environment query to get a cover location and moves to it.
 *
 * The cover environment query requires the arguments {@link EQSArgument.Origin} and {@link EQSArgument.LastHitLocation} to be set before it
 * gets called (@see {@link EQSQueryType.Cover}). In this behavior, if any of these are undefined, the current location of the AI will be used for the undefined
 * location.
 */
export const BT_GetCover = new Sequence({
    nodes: [
        BTT_QuerySetArgumentVector(EQSQueryType.Cover, EQSArgument.Origin, (blackboard: AIBlackboard) =>
<<<<<<< HEAD
            typeof blackboard.targetLastKnownLocation !== "undefined" ? blackboard.targetLastKnownLocation : blackboard.input.self.location,
=======
            blackboard.targetLastKnownLocation !== undefined ? blackboard.targetLastKnownLocation : blackboard.input.self.location,
>>>>>>> develop
        ),
        BTT_QuerySetArgumentVector(EQSQueryType.Cover, EQSArgument.LastHitLocation, (blackboard: AIBlackboard) =>
            typeof blackboard.lastHitLocation !== "undefined" ? blackboard.lastHitLocation : blackboard.input.self.location,
        ),
        BTT_RunEQSQuery(EQSQueryType.Cover, "coverLocation"),
        BTT_MoveTo("coverLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.coverLocation = undefined)),
    ],
})
