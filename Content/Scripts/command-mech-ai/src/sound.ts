import { Vector } from "types";
import { ProvideVectorContext } from "@blackboards/blackboardkeycontext";

export class Sound implements ProvideVectorContext {
    time: number
    location: Vector

    constructor(location: Vector, time: number) {
        this.time = time
        this.location = location
    }

    getVectorValue(): Vector {
        return this.location
    }
}