import { EQSQueryType } from "enums"
import { Vector, WarMachine } from "types"
import { ProvideVectorContext } from "@blackboards/blackboardkeycontext"

export const StringToEQSQueryType = (key: string) => {
    switch (key) {
        case "away":
            return EQSQueryType.Away
        case "cover":
            return EQSQueryType.Cover
        case "hidden":
            return EQSQueryType.Hidden
        case "patrol":
            return EQSQueryType.Patrol
        case "strafe":
            return EQSQueryType.Strafe
        case "closeStrafe":
            return EQSQueryType.CloseStrafe
        case "battleZone":
            return EQSQueryType.BattleZone
    }
}

export const IsVector = (object: any): object is Vector => {
    return "X" in object && "Y" in object
}

export const IsWarMachine = (object: any): object is WarMachine => {
    return "hash" in object
}

export const DoesProvideVectorContext = (object: any): object is ProvideVectorContext => {
    return "getVectorValue" in object
}