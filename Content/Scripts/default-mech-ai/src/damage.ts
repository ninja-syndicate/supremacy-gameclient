import { DamageDetails } from "types"

export class Damage {
    time: number
    damageDetails: DamageDetails

    constructor(currentTime: number, damageDetails: DamageDetails) {
        this.time = currentTime
        this.damageDetails = damageDetails
    }
}