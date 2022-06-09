import {EnvironmentQueryStatus, WeaponTag} from "enums"
import {BrainInput, IntVector, WarMachine} from "types"
import {StringToEQSQueryType} from "./utils"
import {AI} from "./index"
import {BT_Root} from "./trees/BT_Root"
import {BehaviorTree} from "behaviortree"
import {AIBlackboard} from "./blackboard"
import {MovementResult} from "enums";
import {Task, SUCCESS, FAILURE, RUNNING} from 'behaviortree';
import {Perception} from "types";
import {distanceTo, isDead} from "./helper";

export let tree = new BehaviorTree({
    tree: BT_Root,
    blackboard: {
        target: null,
        eqsResults: {},
    } as AIBlackboard,
});

export const onBegin = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;

    // Store hash for the weapons to blackboard for easy access.
    /*
    for (let weapon of input.self.weapons) {
        const leftIndex: number = weapon.tags.findIndex(tag => tag === WeaponTag.PrimaryLeftArm);
        const rightIndex: number = weapon.tags.findIndex(tag => tag === WeaponTag.PrimaryRightArm);

        if (leftIndex !== -1) {
            blackboard.leftArmWeapon = input.self.weapons[leftIndex];
        }
        if (rightIndex !== -1) {
            blackboard.rightArmWeapon = input.self.weapons[rightIndex];
        }
    }
    */
    console.log(`${input.self.name} AI Started`);
}

export const onTick = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;

    blackboard.self = input.self;

    // Check errors
    if (input.errors.length !== 0) {
        input.errors.forEach(e => console.log(`${e.severity}: ${e.command}: ${e.message}`))
    }

    // Perception
    handleSightPerception(input.perception);

    if (input.perception.damage.length != 0) {
        const lastIndex: number = input.perception.damage.length - 1;

        // Use the last damage stimulus direction.
        blackboard.damageStimulusRotator = input.perception.damage[lastIndex].damageRotator;
        console.log(blackboard.damageStimulusRotator.Roll, blackboard.damageStimulusRotator.Pitch,blackboard.damageStimulusRotator.Yaw);
    }





    /*
    if (bb.canSeeTarget || !bb.canSeeTarget) {
        bb.targetLastKnownLocation = bb.target.location;
    }
    */
        /*
        if (movementResult == MovementResult.Success) {
            const result = AI.MoveToVector(bb.targetLastKnownLocation);
            movementResult = result;
            
            switch (result) {
                case MovementResult.Moving:
                    return RUNNING
                case MovementResult.Success:
                    return SUCCESS
                case MovementResult.Aborted:
                    return SUCCESS
                default:
                    return FAILURE
            }
        }
        */
    //}

    /*
    console.log(bb.canSeeTarget);
    const {X, Y, Z} = bb.targetLastKnownLocation;
    console.log(X, Y, Z);
    */

    // Update Target

    // if (input.perception.damage.length > 0) {
    //     console.log(JSON.stringify(input.perception.damage[0]));
    // }

    // Run Behaviour Tree
    tree.step()

    // EQS - Run callbacks when they succeed
    for (let [key, value] of Object.entries(input.eqs)) {
        if (value.status === EnvironmentQueryStatus.Success) {
            blackboard.eqsResults[key] = value
            AI.EQS_Complete(StringToEQSQueryType(key))
        }
    }

    // TODO: Weapon LOS check
    // if (targetVisible) {
    //     AI.FocusHash(target.hash);
    //     AI.WeaponTrigger(WeaponTag.Primary, target.location)
    // } else {
    //     AI.ClearFocus();
    //     AI.WeaponRelease(WeaponTag.Primary);
    // }
}

function handleSightPerception(perception: Perception): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;
    
    // If the mech has no target, update the target to best target given by .
    if (blackboard.target === null) {

    }
    const targetVisIndex = !blackboard.target ? -1 : perception.sight.findIndex(m => m.hash === blackboard.target.hash);
    blackboard.canSeeTarget = blackboard.target !== null && targetVisIndex !== -1;


    if (blackboard.target !== null && isDead(blackboard.target)) {

    }

    if (blackboard.canSeeTarget) {
        blackboard.targetLastKnownLocation = blackboard.target.location;
    }

    if (!blackboard.canSeeTarget) {
        // Find Target
        if (perception.sight.length > 0) {
            blackboard.target = perception.sight[0]
            blackboard.canSeeTarget = true
            blackboard.targetLastKnownLocation = blackboard.target.location;
        }
    }

    if (targetVisIndex !== -1) {
        blackboard.target = perception.sight[targetVisIndex];
        score(blackboard.target);
    }

}

// TODO: damage perception
/*
function handleDamagePerception(preception: Perception): void {
    preception.damage;
}
*/

/**
 * 
 */
function findBestTarget(mechs: WarMachine[]): WarMachine {
    if (mechs.length === 0)
        return null;
    
    
    // Get the index of the first target with largest score.
    const scores: number[] = mechs.map(score);
    const idx: number = scores.indexOf(Math.max(...scores));
    if (idx === -1)
        return null;
    
    return mechs[idx];
}

/**
 * 
 * 
 * @param mech 
 * 
 * @returns 
 */
function filter(mech: WarMachine): boolean {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;
    const MaxDistanceToConsider: number = 50000;

    const filterByDistance = () => distanceTo(blackboard.self, mech) <= MaxDistanceToConsider;
    const filterFuncs = [filterByDistance];

    return filterFuncs.map((func) => func()).reduce((a, b) => a && b);
}

/**
 * 
 * 
 * @param mech 
 * 
 * @returns 
 */
function score(mech: WarMachine): number {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;
    const MaxDistanceToConsider: number = 50000;

    // Normalized score functions.
    const scoreByHealth = (m: WarMachine) => 1 - ((m.health + m.shield) / (m.healthMax + m.shieldMax));
    const scoreByDistance = (m: WarMachine) => 1 - Math.min(1, distanceTo(blackboard.self, m) / MaxDistanceToConsider);
    const scoreFuncs = [scoreByHealth, scoreByDistance];

    const totalScore = scoreFuncs.map((func) => func(mech)).reduce((a, b) => a + b);

    // Normalize total score.
    return totalScore / scoreFuncs.length;
}