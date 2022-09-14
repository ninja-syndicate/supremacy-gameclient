import { WarMachine } from "types"
import { AIBlackboard } from "@blackboards/blackboard"

export const Predicate_IsTeamInAdvantage = (blackboard: AIBlackboard) => {
    const factionID: string = blackboard.input.Self.FactionId

    // TODO: maintain a list of friendly mechs in some radius and factor that into account.
    const teammates: WarMachine[] = blackboard.input.Perception.Sight.filter((w) => w.FactionId === factionID && w.Health > 0)
    const enemies: WarMachine[] = blackboard.input.Perception.Sight.filter((w) => w.FactionId !== factionID && w.Health > 0)

    const teammatesScore = teammates.map((w) => (w.Health + w.Shield) / (w.HealthMax + w.ShieldMax))
    const enemiesScore = enemies.map((w) => (w.Health + w.Shield) / (w.HealthMax + w.ShieldMax))
    return teammatesScore > enemiesScore
}
