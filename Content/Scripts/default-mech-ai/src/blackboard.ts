import {EnvironmentQuery, WarMachine, IntVector, Weapon, Perception} from "types";
import {EQSQueryType} from "enums";
import {Rotator} from "types";

/**
 * 
 * 
 */
export interface AIBlackboard {
    self: WarMachine;
    eqsResults: Map<EQSQueryType, EnvironmentQuery>;
    perception: Perception;
    target: WarMachine | null;
    canSeeTarget: boolean;
    patrolLocation?: IntVector;
    targetLastKnownLocation?: IntVector;
    damageStimulusRotator?: Rotator;
    leftArmWeapon: Weapon;
    rightArmWeapon: Weapon;
}