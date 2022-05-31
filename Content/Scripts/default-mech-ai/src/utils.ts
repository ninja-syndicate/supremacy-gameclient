import {EQSQueryType} from "enums";
import {IntVector} from "types";

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

export const IsIntVector = (object: any): object is IntVector => {
    return 'X' in object && 'Y' in object;
}