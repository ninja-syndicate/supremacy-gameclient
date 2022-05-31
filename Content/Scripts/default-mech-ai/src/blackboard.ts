import {EnvironmentQuery} from "types";
import {EQSQueryType} from "enums";
import {IntVector} from "types"

export interface AIBlackboard {
    eqsResults: Map<EQSQueryType, EnvironmentQuery>;

    targetHash?: string;
    targetLastKnownLocation?: IntVector;
    canSeeTarget: boolean;
    patrolLocation?: IntVector;
}