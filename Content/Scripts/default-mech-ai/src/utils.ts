import {EQSQueryType} from "enums";

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