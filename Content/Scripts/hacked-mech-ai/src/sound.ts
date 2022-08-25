import { SoundDetails, Vector } from "types"
import { ProvideVectorContext } from "@blackboards/blackboardkeycontext"

export class Sound implements ProvideVectorContext {
    time: number
    soundDetail: SoundDetails

    constructor(soundDetails: SoundDetails, time: number) {
        this.time = time
        this.soundDetail = soundDetails
    }

    getVectorValue(): Vector {
        return this.soundDetail.location
    }
}
