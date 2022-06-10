import {EnvironmentQueryStatus, WeaponTag} from "enums"
import {BrainInput, DamageDetails, Vector, WarMachine} from "types"
import {StringToEQSQueryType} from "./utils"
import {AI} from "./index"
import {BT_Root} from "./trees/BT_Root"
import {BehaviorTree} from "behaviortree"
import {AIBlackboard} from "./blackboard"
import {MovementResult} from "enums";
import {Task, SUCCESS, FAILURE, RUNNING} from 'behaviortree';
import {Perception} from "types";
import {distanceTo, isDead, add, multiply} from "./helper";

export let tree = new BehaviorTree({
    tree: BT_Root,
    blackboard: {
        target: null,
        eqsResults: {},
    } as AIBlackboard,
});

export const onBegin = (input: BrainInput) => {
    console.log(`${input.self.name} AI Started`);
}

export const onTick = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;

    // Check errors
    if (input.errors.length !== 0) {
        input.errors.forEach(e => console.log(`${e.severity}: ${e.command}: ${e.message}`))
    }

    updateBlackboard(input);

    // Run Behaviour Tree
    tree.step()

    // EQS - Run callbacks when they succeed
    for (let [key, value] of Object.entries(input.eqs)) {
        if (value.status === EnvironmentQueryStatus.Success) {
            blackboard.eqsResults[key] = value
            AI.EQS_Complete(StringToEQSQueryType(key))
        }
    }
}

function updateBlackboard(input: BrainInput): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;

    blackboard.input = input;
    
    const bestTarget: WarMachine = findBestTarget(blackboard);
    // console.log(JSON.stringify(bestTarget));
    if (bestTarget === null) {
        clearBlackboardTarget();
    } else {
        blackboard.target = bestTarget;
    }
    updateBlackboardSight(input.perception.sight);
    updateBlackboardDamage(input.perception.damage);
}

function clearBlackboardTarget(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;

    blackboard.target = null;
    blackboard.canSeeTarget = false;
    if (blackboard.targetLastKnownLocation !== undefined) {
        delete blackboard.targetLastKnownLocation;
    }
}

/**
 * Only update the sight info.
 * 
 * @param perception 
 */
function updateBlackboardSight(sight: WarMachine[]): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;
    if (!blackboard.target)
        return;

    if (sight.length === 0) {
        blackboard.canSeeTarget = false;
    } else {
        const targetVisIndex: number = sight.findIndex(m => m.hash === blackboard.target.hash);

        blackboard.canSeeTarget = targetVisIndex !== -1;
        if (blackboard.canSeeTarget) {
            blackboard.targetLastKnownLocation = blackboard.target.location;
            blackboard.targetPredictedLocation = blackboard.target.location;
            blackboard.targetLastKnownVelocity = blackboard.target.velocity;
        }
    }
    if (blackboard.targetLastKnownLocation !== undefined) {
        // TODO: Project to navigation and clear if not valid.
        // Also expose a new EQS to allow searching for target in the direction.
        blackboard.targetPredictedLocation = add(blackboard.targetPredictedLocation, 
                                                 multiply(blackboard.targetLastKnownVelocity, blackboard.input.deltaTime));
    }
}

/**
 * Only update the damage info.
 * 
 * @param perception 
 * 
 * @returns 
 */
function updateBlackboardDamage(damageDetails: DamageDetails[]): void {
    if (damageDetails.length === 0)
        return;
    
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard;
    const lastIndex: number = damageDetails.length - 1;

    blackboard.damageStimulusDirection = damageDetails[lastIndex].damageDirection;
    blackboard.damageStimulusFocalPoint = add(blackboard.input.self.location, multiply(blackboard.damageStimulusDirection, 1000));
}

/**
 * 
 */
function findBestTarget(blackboard: AIBlackboard): WarMachine {
    const mechsBySight: WarMachine[] = blackboard.input.perception.sight;
    const damageDetails: DamageDetails[] = blackboard.input.perception.damage;

    // For now, only consider mechs by sight.
    // TODO: Maintain list of mechs in memory and 
    // use damage details to figure out which mech it is associated with.
    if (mechsBySight.length === 0) {
        // maybe return null after some time if lost.
        return blackboard.target;
    }
    
    // TODO: apply filter function

    // Get the index of the first target with largest score.
    const scores: number[] = mechsBySight.map(score);
    const idx: number = scores.indexOf(Math.max(...scores));
    if (idx === -1)
        return null;
    
    return mechsBySight[idx];
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

    const filterByDistance = () => distanceTo(blackboard.input.self, mech) <= MaxDistanceToConsider;
    const filterFuncs = [filterByDistance];

    return filterFuncs.map((func) => func()).reduce((a, b) => a && b);
}

function scoreBySight(mechs: WarMachine[]): number[] {
    return mechs.map(score);
}

/*
// TODO
function scoreByDamage(damageDetails: DamageDetails[]): number[] {

}

function scoreByD(mech: WarMachine): number {

}
*/

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
    const scoreByDistance = (m: WarMachine) => 1 - Math.min(1, distanceTo(blackboard.input.self, m) / MaxDistanceToConsider);
    const scoreFuncs = [scoreByHealth, scoreByDistance];

    const totalScore = scoreFuncs.map((func) => func(mech)).reduce((a, b) => a + b);

    // Normalize total score.
    return totalScore / scoreFuncs.length;
}