
import { FAILURE, ObserverAborts, Parallel, ParallelComplete, ParallelSelector, Selector, Sequence, SUCCESS, Task } from "behaviortree"
import { BTT_SetFocalPoint } from "../tasks/BTT_SetFocalPoint"
import { IsSet } from "../decorators/IsSet"
import { AIBlackboard } from "../blackboard"
import { Ability, EQSArgument, EQSQueryType, WeaponTag } from "../../../types/enums"
import { BTT_SpecialAttack } from "../tasks/BTT_SpecialAttack"
import { CanActivateAbility } from "../decorators/CanActivateAbility"
import { BTT_MoveTo } from "../tasks/BTT_MoveTo"
import { ParallelBackground } from "../branches/ParallelBackground"
import { BTT_RunEQSQuery } from "../tasks/BTT_RunEQSQuery"
import { BTT_EQSSetArgumentString, BTT_EQSSetArgumentVector } from "../tasks/BTT_EQSSetArgument"
import { BTT_SetValue } from "../tasks/BTT_SetValue"
import { BT_ReceivedDamage } from "./BT_ReceivedDamage"
import { BT_CanSeeTarget } from "./BT_CanSeeTarget"
import { BT_RangeCombat } from "./BT_RangeCombat"
import { BTT_Shoot } from "../tasks/BTT_Shoot"
import { BTT_TriggerWeapon } from "../tasks/BTT_TriggerWeapon"
import { BTT_MeleeAttack } from "../tasks/BTT_MeleeAttack"
import { BTT_LogString } from "../tasks/BTT_LogString"

export const BT_SearchTarget = new Sequence({
    nodes: [
        new ParallelBackground({
            nodes: [
                new Sequence({
                    nodes: [BTT_MoveTo("targetLastKnownLocation")],
                }),
                BTT_SetFocalPoint("targetPredictedLocation"),
            ],
        }),
        BTT_LogString("got to here"),
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
        BTT_SetValue((blackboard: AIBlackboard) => (blackboard.target = null)),
    ],
})