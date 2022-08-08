import { Vector } from "types";

export class Sound {
    time: number
    location: Vector

    constructor(location: Vector, time: number) {
        this.time = time
        this.location = location
    }
}