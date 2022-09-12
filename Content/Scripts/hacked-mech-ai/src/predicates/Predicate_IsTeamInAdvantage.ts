import { WarMachine } from "types"
import { AIBlackboard } from "@blackboards/blackboard"

export const Predicate_IsTeamInAdvantage = (blackboard: AIBlackboard) => {
    const factionID: string = blackboard.input.self.factionID

    // TODO: maintain a list of friendly mechs in some radius and factor that into account.
    const teammates: WarMachine[] = blackboard.input.perception.sight.filter((w) => w.factionID === factionID && w.health > 0)
    const enemies: WarMachine[] = blackboard.input.perception.sight.filter((w) => w.factionID !== factionID && w.health > 0)

    const teammatesScore = teammates.map((w) => (w.health + w.shield) / (w.healthMax + w.shieldMax))
    const enemiesScore = enemies.map((w) => (w.health + w.shield) / (w.healthMax + w.shieldMax))
    return teammatesScore > enemiesScore
}
