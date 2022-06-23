import { AIBlackboard } from "../blackboard"

export const HasVeryLowTotalHealth = (blackboard: AIBlackboard) => {
    let self = blackboard.input.self
    return (self.health + self.shield) / (self.healthMax + self.shieldMax) <= 0.3
}
