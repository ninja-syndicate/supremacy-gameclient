import { Vector } from "types"

export class Pickup {
    tag: string
    location: Vector
    factionID: string

    constructor(tag: string, location: Vector, factionID: string) {
        this.tag = tag
        this.location = location
        this.factionID = factionID
    }
}
