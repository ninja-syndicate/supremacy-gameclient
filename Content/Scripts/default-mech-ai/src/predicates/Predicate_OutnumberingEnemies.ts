import { WarMachine } from "types"
import { AIBlackboard } from "../blackboard"

export const OutnumberingEnemies = (blackboard: AIBlackboard) => {
    const factionID: string = blackboard.input.self.factionID

    // TODO: maintain a list of friendly mechs in some radius and factor that into account.
    const teammates: WarMachine[] = blackboard.input.perception.sight.filter((w) => w.factionID === factionID)
    const enemies: WarMachine[] = blackboard.input.perception.sight.filter((w) => w.factionID !== factionID)

    return teammates.length + 1 > enemies.length
}
