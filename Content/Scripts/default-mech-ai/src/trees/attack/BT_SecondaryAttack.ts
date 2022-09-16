import { Sequence } from "behaviortree"
import { Vector } from "types"
import { add, distanceToVec, multiply } from "@root/helper"
import { AIBlackboard } from "@blackboards/blackboard"
import { BTT_SetValue } from "@tasks/BTT_SetValue"
import { ROCKET_POD_ACTIVATION_TIME } from "@root/aiconfig"
import { BTT_SpecialAttack } from "@tasks/BTT_SpecialAttack"

export const BT_FireRocketPod = new Sequence({
    nodes: [
        BTT_SetValue((blackboard: AIBlackboard) => {
            const distToTarget: number = distanceToVec(blackboard.input.Self.Location, blackboard.target.Location)
            const trajectoryTime: number = distToTarget / Math.max(1, blackboard.secondaryWeapon.ProjectileSpeed)
            const targetPredictedLocation: Vector = add(
                blackboard.targetLastKnownLocation,
                multiply(blackboard.targetLastKnownVelocity, ROCKET_POD_ACTIVATION_TIME + trajectoryTime),
            )
            blackboard.arcLaunchLocation = targetPredictedLocation
        }),
        BTT_SpecialAttack("arcLaunchLocation"),
    ],
})
