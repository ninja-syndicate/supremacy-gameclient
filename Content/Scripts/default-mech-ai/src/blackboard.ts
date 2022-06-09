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
    targetLastKnownLocation?: Vector;
    targetPredictedLocation?: Vector;

    damageStimulusDirection?: Vector;
    damageStimulusFocalPoint?: Vector;
    damageStimulusEstimateLocation?: Vector;

    leftArmWeapon: Weapon;
    rightArmWeapon: Weapon;
}