import {EnvironmentQuery, WarMachine, Vector, Weapon, Perception} from "types";
import {EQSQueryType} from "enums";

/**
 * 
 * 
 */
export interface AIBlackboard {
    self: WarMachine;
    eqsResults: Map<EQSQueryType, EnvironmentQuery>;
    weapons: Weapon[];
    perception: Perception;
    target: WarMachine | null;
    canSeeTarget: boolean;
    patrolLocation?: Vector;
    targetLastKnownLocation?: Vector;
    damageStimulusDirection?: Vector;
    leftArmWeapon: Weapon;
    rightArmWeapon: Weapon;
}