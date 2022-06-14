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

const BT_SearchTarget = new Sequence({
    nodes: [
        new ParallelBackground({
            nodes: [
                new Sequence({
                    nodes: [BTT_MoveTo("targetLastKnownLocation")],
                }),
                BTT_SetFocalPoint("targetPredictedLocation"),
            ],
        }),
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

export const BT_Combat = new Selector({
    nodes: [
        IsSet(new Parallel({
            nodes: [BTT_Shoot(WeaponTag.PrimaryLeftArm), BTT_Shoot(WeaponTag.PrimaryRightArm)],
        }), "canSeeTarget", true, ObserverAborts.Self)
        // IsSet(BT_RangeCombat, "canSeeTarget", true, ObserverAborts.Both)
        //IsSet(BT_CanSeeTarget, "canSeeTarget", true, ObserverAborts.Both),
        //IsSet(BT_ReceivedDamage, "damageStimulusFocalPoint", true, ObserverAborts.Both),
        //IsSet(BT_SearchTarget, "canSeeTarget", false, ObserverAborts.Self),
    ],
})
