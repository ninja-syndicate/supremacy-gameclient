import { Vector } from "types"
import { distanceToVec } from "@root/helper"

const MaxDistanceToConsider: number = 200000

// export const evaluate = <T>(items: T[], funcs: { (item: T): number }[]) => items.map((i) => funcs.map((func) => func(i)).reduce((a, b) => a + b))
/** Scores by the ratio of the health. The lower the health, higher the score. */
export const scoreByHealth = (health: number, maxHealth: number) => 1 - (health / maxHealth)
/** Scores by the distance. */
export const scoreByDistance = (from: Vector, to: Vector) => 1 - Math.min(1, distanceToVec(from, to) / MaxDistanceToConsider)
// export const scoreByDamage = (damage: number) =>

export const filterByTime = (time: number, currentTime: number, timeout: number) => (currentTime - time) >= timeout
