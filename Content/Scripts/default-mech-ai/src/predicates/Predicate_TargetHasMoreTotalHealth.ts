import { AIBlackboard } from "../blackboard"

export const TargetHasMoreTotalHealth = (blackboard: AIBlackboard) => {
    const self = blackboard.input.self
    const target = blackboard.target
    if (target === null) return false

    const selfTotalHealth = self.health + self.shield
    const targetTotalHealth = target.health + target.shield
    return targetTotalHealth > selfTotalHealth
}
