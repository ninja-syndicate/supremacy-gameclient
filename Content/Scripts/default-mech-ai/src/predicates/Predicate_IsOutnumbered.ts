import { WarMachine } from "types"
import { AIBlackboard } from "@blackboards/blackboard"

/**
 * Checks if the number of detected teammates (including itself) is less than the number of detected enemies.
 *
 * @param blackboard
 * @returns true if outnumbered and false otherwise.
 */
export const IsOutnumbered = (blackboard: AIBlackboard) => {
    const factionID: string = blackboard.input.Self.FactionID

    // TODO: maintain a list of friendly mechs in some radius and factor that into account.
    const teammates: WarMachine[] = blackboard.input.Perception.Sight.filter((w) => w.FactionID === factionID && w.Health > 0)
    const enemies: WarMachine[] = blackboard.input.Perception.Sight.filter((w) => w.FactionID !== factionID && w.Health > 0)

    return teammates.length + 1 < enemies.length
}
