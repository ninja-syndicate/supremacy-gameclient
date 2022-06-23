import { Sequence } from "behaviortree"
import { EQSArgument, EQSQueryType } from "../../../types/enums"
import { AIBlackboard } from "../blackboard"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_SetValue } from "../tasks/BTT_SetValue"

/**
 * Getting a cover behavior.
 *
 * Requests a cover location and moves to it.
 *
 * By default, it will use the target's last known location and last hit
 * location to find a suitable cover location. If any of these are undefined,
 * the current location of the AI will be used for the undefined location.
 */
export const BT_GetCover = new Sequence({
    nodes: [
        BTT_EQSSetArgumentVector(EQSQueryType.Cover, EQSArgument.TargetLastKnownLocation, (blackboard: AIBlackboard) =>
            blackboard.targetLastKnownLocation !== undefined ? blackboard.targetLastKnownLocation : blackboard.input.self.location,
        ),
        BTT_EQSSetArgumentVector(EQSQueryType.Cover, EQSArgument.LastHitLocation, (blackboard: AIBlackboard) =>
            blackboard.lastHitLocation !== undefined ? blackboard.lastHitLocation : blackboard.input.self.location,
        ),
        BTT_RunEQSQuery(EQSQueryType.Cover, "coverLocation"),
        BTT_MoveTo("coverLocation"),
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.coverLocation = undefined)),
    ],
})
