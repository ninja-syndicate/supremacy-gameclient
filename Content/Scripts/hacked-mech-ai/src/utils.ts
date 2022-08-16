import { EQSQueryType } from "enums";
import { Vector, WarMachine } from "types";

export const StringToEQSQueryType = (key: string) => {
    switch (key) {
        case "away":
            return EQSQueryType.Away;
        case "cover":
            return EQSQueryType.Cover;
        case "hidden":
            return EQSQueryType.Hidden;
        case "patrol":
            return EQSQueryType.Patrol;
        case "strafe":
            return EQSQueryType.Strafe;
    }
}

export const IsVector = (object: any): object is Vector => {
    return 'X' in object && 'Y' in object;
}

export const IsWarMachine = (object: any): object is WarMachine => {
    return 'hash' in object;
}