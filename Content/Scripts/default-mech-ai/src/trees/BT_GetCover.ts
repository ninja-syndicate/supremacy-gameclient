import { Sequence } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/focus/BTT_SetFocalPoint"
import { AIBlackboard } from "../blackboard"
import { EQSArgument, EQSQueryType } from "../../../types/enums"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { Predicate } from "../decorators/Predicate"
import { AI } from ".."
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BTT_ClearValue } from "../tasks/BTT_ClearValue"
import { BTT_LogString } from "../tasks/BTT_LogString"

/**
 * Getting a cover behavior.
 *
 * Requests a cover location and moves to it.
 *
 * By default, it will use the target's last known location and last hit
 * location to find a suitable cover location. If any of these are undefined,
 * the current location of the AI will be used for the undefined location.
 *
 * Note that this behavior changes the current focal point unless it is already
 * set.
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
        ForceSuccess(Predicate(BTT_SetFocalPoint("coverLocation"), (blackboard: AIBlackboard) => !AI.IsFocalPointSet())),
        BTT_MoveTo("coverLocation"),
        BTT_ClearValue((blackboard: AIBlackboard) => (blackboard.coverLocation = undefined)),
    ],
})
