import {EnvironmentQuery, WarMachine, Vector, Weapon, Perception, BrainInput} from "types";
import {EQSQueryType} from "enums";

/**
 * 
 * 
 */
export interface AIBlackboard {
    input: BrainInput;
    
    eqsResults: Map<EQSQueryType, EnvironmentQuery>;
    weapons: Weapon[];
    patrolLocation?: Vector;

    target: WarMachine | null;
    canSeeTarget: boolean;

    strafeLocation?: Vector;
    hiddenLocation?: Vector;

    targetLastKnownLocation?: Vector;
    targetLastKnownVelocity?: Vector;
    targetPredictedLocation?: Vector;

    damageStimulusDirection?: Vector;
    damageStimulusFocalPoint?: Vector;
    damageStimulusEstimateLocation?: Vector;

    leftArmWeapon: Weapon;
    rightArmWeapon: Weapon;
    secondaryWeapon?: Weapon;

    canUseSpecialAttack: boolean;
}

export type BlackboardKey = keyof AIBlackboard | keyof WarMachine;