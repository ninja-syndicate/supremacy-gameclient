import { AIBlackboard } from "@blackboards/blackboard"
import { Action } from "enums"
import { Predicate_CanActivateAction } from "@predicates/Predicate_CanActivateAction"
import { distanceTo, size } from "@root/helper"

export const Predicate_UseSpecialAttack = (blackboard: AIBlackboard): boolean => {
    if (!blackboard.secondaryWeapon) return false
    if (!blackboard.target) return false
    if (!blackboard.canSeeTarget) return false
    if (!Predicate_CanActivateAction(Action.SpecialAttack)(blackboard)) return false

    const distToTarget: number = distanceTo(blackboard.input.Self, blackboard.target)
    const currentSpeed: number = size(blackboard.target.Velocity)
    const maxSpeed: number = blackboard.target.MaxSpeed
    const speedRatio: number = currentSpeed / maxSpeed

    if (speedRatio < 0.5) return true

    return distToTarget <= blackboard.secondaryWeapon.DamageFalloff
}
