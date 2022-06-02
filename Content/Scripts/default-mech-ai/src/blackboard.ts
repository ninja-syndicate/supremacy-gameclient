import {EnvironmentQuery, WarMachine, IntVector} from "types"
import {EQSQueryType} from "enums"

export interface AIBlackboard {
    eqsResults: Map<EQSQueryType, EnvironmentQuery>

    target: WarMachine | null
    canSeeTarget: boolean
    patrolLocation?: IntVector
    targetLastKnownLocation?: IntVector
}