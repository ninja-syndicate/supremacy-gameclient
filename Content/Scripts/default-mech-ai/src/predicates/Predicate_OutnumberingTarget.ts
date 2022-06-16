import { WarMachine } from "types"
import { AIBlackboard } from "../blackboard"

export const OutnumberingTarget = (blackboard: AIBlackboard) => {
    const factionID: string = blackboard.input.self.factionID

    const teammates: WarMachine[] = blackboard.input.perception.sight.filter((w) => w.factionID === factionID)
    const enemies: WarMachine[] = blackboard.input.perception.sight.filter((w) => w.factionID !== factionID)

    return teammates.length > enemies.length
}
