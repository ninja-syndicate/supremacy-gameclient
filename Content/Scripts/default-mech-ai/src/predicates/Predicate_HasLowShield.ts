import { AIBlackboard } from "../blackboard"

/**
 * 
 *  
 * @param blackboard 
 * @returns 
 */
export const HasLowShield = (blackboard: AIBlackboard) => {
    let self = blackboard.input.self
    return self.shield / self.shieldMax <= 0.3
}
