import {EnvironmentQuery, WarMachine, IntVector, Weapon} from "types"
import {EQSQueryType} from "enums"

/**
 * 
 * 
 */
export interface AIBlackboard {
    self: WarMachine;
    eqsResults: Map<EQSQueryType, EnvironmentQuery>;

    target: WarMachine | null;
    canSeeTarget: boolean;
    patrolLocation?: IntVector;
    targetLastKnownLocation?: IntVector;
    leftArmWeapon: Weapon;
    rightArmWeapon: Weapon;
}