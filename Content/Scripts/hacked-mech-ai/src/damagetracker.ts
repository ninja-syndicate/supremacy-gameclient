import { Queue } from "queue-typescript"
import { Damage } from "@root/damage"

class TrackedDamageDetails {
    maxHistoryCount: number
    damageDetailHistory: Queue<Damage>

    constructor(...damages: Damage[]) {
        this.maxHistoryCount = Math.max(damages.length, 30)
        this.damageDetailHistory = new Queue<Damage>(...damages)
    }

    add(damage: Damage) {
        this.damageDetailHistory.enqueue(damage)

        if (this.damageDetailHistory.length > this.maxHistoryCount) {
            this.damageDetailHistory.dequeue()
        }
    }
}

export class DamageTracker {
    damageTracker: Map<string, TrackedDamageDetails>

    constructor() {
        this.damageTracker = new Map<string, TrackedDamageDetails>()
    }

    addDamage(...damages: Damage[]) {
        for (const damage of damages) {
            const trackedDamage = this.damageTracker.get(damage.damageDetails.instigatorHash)

            if (trackedDamage === undefined) {
                this.damageTracker.set(damage.damageDetails.instigatorHash, new TrackedDamageDetails(damage))
            } else {
                trackedDamage.add(damage)
            }
        }
    }

    getTotalDamageByTime(currentTime: number, queryDuration: number, hash: string): number {
        const trackedDamage: TrackedDamageDetails = this.damageTracker.get(hash)
        if (trackedDamage === undefined) return 0

        return [...trackedDamage.damageDetailHistory]
            .filter((d) => d.time >= currentTime - queryDuration)
            .map((d) => d.damageDetails.amount)
            .reduce((a, b) => a + b, 0)
    }
}
