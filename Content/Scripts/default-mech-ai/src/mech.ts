import { BehaviorTree } from "behaviortree"
import { EnvironmentQueryStatus, InteractableTag, SoundType, WeaponTag } from "enums"
import { BrainInput, DamageDetails, InteractableDetails, SoundDetails, WarMachine } from "types"
import { AIBlackboard } from "./blackboard"
import { add, distanceTo, distanceToVec, multiply } from "./helper"
import { AI } from "./index"
import { BT_Root } from "./trees/BT_Root"
import { StringToEQSQueryType } from "./utils"

// TODO: some clean up
// TODO: handle signaling.

/**
 * Creates a new behavior tree based off {@link BT_Root}.
 *
 * @see {@link BT_Root} for the root behavior tree and {@link AIBlackboard} for blackboard details.
 */
export let tree = new BehaviorTree({
    tree: BT_Root,
    blackboard: {
        target: null,
        eqsResults: {},
    } as AIBlackboard,
})

/**
 * This function gets called when AI begins.
 *
 * You can set up things that only need to be done once here.
 *
 * @param input @see {@link BrainInput} for details.
 */
export const onBegin = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    // Check for secondary weapons and melee weapons and initialize blackboard
    for (let weapon of input.self.weapons) {
        if (weapon.tags.find((t) => t === WeaponTag.Secondary) !== undefined) {
            blackboard.secondaryWeapon = weapon
            blackboard.canUseSpecialAttack = true
            break
        }
    }
    for (let weapon of input.self.weapons) {
        if (weapon.tags.find((t) => t === WeaponTag.Melee) !== undefined) {
            blackboard.canMelee = true
            break
        }
    }
    console.log(`${input.self.name} AI Started`)
}

/**
 * This function gets called every tick rate that AI is capable of.
 *
 * @param input @see {@link BrainInput} for details.
 */
export const onTick = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    // Check for any errors and log it. This will be useful for debugging.
    if (input.errors.length !== 0) {
        input.errors.forEach((e) => console.log(`${e.severity}: ${e.command}: ${e.message}`))
    }

    // Update the blackboard based on the new input.
    updateBlackboard(input)

    // Run behavior tree.
    tree.step()

    // EQS - Run callbacks when they succeed.
    for (let [key, value] of Object.entries(input.eqs)) {
        blackboard.eqsResults[key] = value
        if (value.status === EnvironmentQueryStatus.Success) {
            AI.EQS_Complete(StringToEQSQueryType(key))
        }
    }
}

/**
 * Updates the blackboard based on the new input.
 *
 * @param input @see {@link BrainInput} for details.
 */
function updateBlackboard(input: BrainInput): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    // Copy over the new input for easy access.
    blackboard.input = input

    // Find a best target based on the current blackboard.
    const bestTarget: WarMachine = findBestTarget()
    if (bestTarget === null) {
        clearBlackboardTarget()
    } else {
        blackboard.target = bestTarget
    }
    // Update perception related information in the blackboard.
    updateBlackboardSight()
    updateBlackboardDamage()
    updateBlackboardSound()
    updateBlackboardInteractable()
}

/**
 * Updates the sight related information in the blackboard.
 */
function updateBlackboardSight(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const sight: WarMachine[] = blackboard.input.perception.sight

    // Clear damage related information if the one that caused damage is dead.
    if (blackboard.damageInstigatorHash !== undefined) {
        const idx = sight.findIndex((m) => m.hash === blackboard.damageInstigatorHash && m.health <= 0)
        if (idx !== -1) {
            clearDamageInfo()
        }
    }

    // Nothing to do if the target is not set.
    if (!blackboard.target) return

    if (sight.length === 0) {
        blackboard.canSeeTarget = false
    } else {
        // Get the index of the current target in the sight array.
        const targetVisIndex: number = sight.findIndex((m) => m.hash === blackboard.target.hash)

        // Update the target information if it's in sight.
        blackboard.canSeeTarget = targetVisIndex !== -1
        if (blackboard.canSeeTarget) {
            blackboard.targetLastKnownLocation = blackboard.target.location
            blackboard.targetPredictedLocation = blackboard.target.location
            blackboard.targetLastKnownVelocity = blackboard.target.velocity
        }
    }
    // Calculate a new target predicted location based on its last known velocity and the time elapsed since last tick.
    if (blackboard.targetLastKnownLocation !== undefined) {
        // TODO: Project to navigation and clear if not valid when navigating.
        blackboard.targetPredictedLocation = add(blackboard.targetPredictedLocation, multiply(blackboard.targetLastKnownVelocity, blackboard.input.deltaTime))
    }
}

/**
 * Update the damage related information in the blackboard.
 *
 * Currently, it only considers last damage from enemy AIs. You may modify this implementation to also consider friendly damage, maintain the amount of damage
 * AI has received over time from different enemies.
 *
 * @see {@link DamageDetails} for damage details.
 */
function updateBlackboardDamage(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const damageDetails: DamageDetails[] = blackboard.input.perception.damage

    // Fail-fast if nothing to update.
    if (damageDetails.length === 0) return

    // Get the enemy damage details. Feel free to modify this logic to do something about friendly damage
    const enemyDamageDetails: DamageDetails[] = damageDetails.filter((d) => !d.friendly)
    if (enemyDamageDetails.length === 0) return

    // Update damage info using the last enemy damage details.
    const lastIdx: number = enemyDamageDetails.length - 1
    blackboard.damageInstigatorHash = enemyDamageDetails[lastIdx].instigatorHash
    blackboard.damageStimulusDirection = enemyDamageDetails[lastIdx].damageDirection
    blackboard.damageStimulusFocalPoint = add(blackboard.input.self.location, multiply(blackboard.damageStimulusDirection, 10000))
    blackboard.lastHitLocation = blackboard.input.self.location
    blackboard.isLastDamageFromTarget = blackboard.target && blackboard.target.hash === enemyDamageDetails[lastIdx].instigatorHash
}

/**
 * Updates the sound related information in the blackboard.
 *
 * Currently, it only considers last taunt sound generated by the enemy AI. You may modify this implementation to also consider noise generated by the friendly
 * AIs, gun sound, and evaluate the score of new sounds based on the distance and type.
 *
 * @see {@link SoundDetails} for sound details.
 */
function updateBlackboardSound(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const soundDetails: SoundDetails[] = blackboard.input.perception.sound

    if (soundDetails.length === 0) return

    // Ignore sound generated by friendly AIs.
    const enemySounds = soundDetails.filter((s) => !s.friendly)
    const enemyTauntSounds = enemySounds.filter((s) => s.tag === SoundType.Taunt)

    const lastIdx: number = enemyTauntSounds.length - 1
    if (lastIdx < 0) return

    // Update the last noise location to the last enemy taunt noise location.
    blackboard.heardNoise = true
    blackboard.noiseLocation = enemyTauntSounds[lastIdx].location
}

/**
 * Updates the interactable related information in the blackboard.
 *
 * @see {@link InteractableDetails} for interactable details.
 */
function updateBlackboardInteractable(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const interactables: InteractableDetails[] = blackboard.input.perception.interactable

    // Clear the desired pickup location if there are no interactables.
    if (interactables.length === 0) {
        blackboard.desiredPickupLocation = undefined
        return
    }

    // Otherwise find the best pickup and update desired pickup location.
    const bestPickup = findBestPickup()
    if (bestPickup !== undefined) {
        blackboard.desiredPickupLocation = bestPickup.location
    }
}

/**
 * Finds the best pickup based on the current blackboard state.
 *
 * @returns best pickup if there is one and undefined otherwise
 */
function findBestPickup(): InteractableDetails {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const scores = evaluateInteractable()
    const idx: number = scores.indexOf(Math.max(...scores))
    return scores[idx] > 0 ? blackboard.input.perception.interactable[idx] : undefined
}

/**
 * Evaluation function for interactables.
 *
 * Gives a score for each interactable using the predefined scoring functions based on its type.
 *
 * @returns An array of sum of scores evaluated by the scoring functions. These scores maintain the same ordering as interactables array. That is, scores[i] is
 * for interactable[i] for all i
 */
function evaluateInteractable(): number[] {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const MaxDistanceToConsider: number = 50000

    const self = blackboard.input.self
    // const totalAmmo = self.weapons.map((w) => (w.tags.findIndex((t) => t === WeaponTag.Primary) !== -1 ? w.maxAmmo : 0)).reduce((a, b) => a + b)
    // console.log(JSON.stringify("total ammo is") + totalAmmo)
    const scoreByHealth = (x: InteractableDetails) => 1 - self.health / self.healthMax
    const scoreByShield = (x: InteractableDetails) => 1 - self.shield / self.shieldMax
    const scoreByDistance = (x: InteractableDetails) => 1 - Math.min(1, distanceToVec(self.location, x.location) / MaxDistanceToConsider)
    // const scoreByAmmo = () => AI.WeaponGetAmmoByTag(WeaponTag.Primary) / totalAmmo

    // const ammoCrateFuncs = [() => 1 - scoreByHealth(), () => 1 - scoreByShield(), scoreByDistance(blackboard.ammoCrateLocation), scoreByAmmo]

    const healCrateFuncs = [scoreByHealth, (x) => scoreByShield(x) - 1, scoreByDistance]
    const shieldCrateFuncs = [(x) => scoreByHealth(x) - 1, scoreByShield, scoreByDistance]

    // TODO: normalization of score?
    let scores = []
    for (const interactable of blackboard.input.perception.interactable) {
        let score = 0
        if (interactable.tag === InteractableTag.HealCrate) {
            score = healCrateFuncs.map((func) => func(interactable)).reduce((a, b) => a + b)
        } else if (interactable.tag === InteractableTag.ShieldCrate) {
            score = shieldCrateFuncs.map((func) => func(interactable)).reduce((a, b) => a + b)
        } else {
            console.log("TODO for ammo crate")
        }
        scores.push(score)
    }
    return scores
}

/**
 * Finds the best target based on the current blackboard.
 *
 * @returns A best target or null if none
 */
function findBestTarget(): WarMachine {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const mechsBySight: WarMachine[] = blackboard.input.perception.sight
    const damageDetails: DamageDetails[] = blackboard.input.perception.damage

    // TODO: Also consider damage

    // Filter the mechs and maintain the same target if there are no suitable mechs.
    const filteredMechs = mechsBySight.filter((m) => filter(m))
    if (filteredMechs.length === 0) return blackboard.target

    // Get the index of the first target with a largest score.
    const scores: number[] = filteredMechs.map(score)
    const idx: number = scores.indexOf(Math.max(...scores))
    return filteredMechs[idx]
}

/**
 * Tests filter functions on the {@link mech} to check if it's suitable as a target.
 *
 * @param mech A mech to test
 *
 * @returns true if the mech passed all the filter functions and false otherwise
 */
// TODO: Support inverse option maybe
function filter(mech: WarMachine, inverse: boolean = false): boolean {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const MaxDistanceToConsider: number = 50000

    // Filter functions. Add more filter functions as you deem appropriate.
    const filterByAlive = () => mech.health > 0
    const filterByFaction = () => blackboard.input.self.factionID !== mech.factionID
    const filterByDistance = () => distanceTo(blackboard.input.self, mech) <= MaxDistanceToConsider
    const filterFuncs = [filterByAlive, filterByFaction, filterByDistance]

    return filterFuncs.map((func) => func()).reduce((a, b) => a && b)
}

/**
 * Gives a score from [0, 1] of suitability as a target for the given {@link mech}.
 *
 * Score 1 means the best target and 0 means the worst target.
 *
 * @param mech A mech to score
 *
 * @returns score of the mech between [0, 1]
 */
function score(mech: WarMachine): number {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const MaxDistanceToConsider: number = 50000

    // Normalized score functions. Add more scoring functions as you desire.
    const scoreByHealth = (m: WarMachine) => 1 - (m.health + m.shield) / (m.healthMax + m.shieldMax)
    const scoreByDistance = (m: WarMachine) => 1 - Math.min(1, distanceTo(blackboard.input.self, m) / MaxDistanceToConsider)
    const scoreFuncs = [scoreByHealth, scoreByDistance]

    const totalScore = scoreFuncs.map((func) => func(mech)).reduce((a, b) => a + b)

    // Normalize total score.
    return totalScore / scoreFuncs.length
}

/**
 * Clears target related information in the blackboard.
 */
export function clearBlackboardTarget(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    blackboard.target = null
    blackboard.canSeeTarget = false
    if (blackboard.targetLastKnownLocation !== undefined) {
        delete blackboard.targetLastKnownLocation
        delete blackboard.targetPredictedLocation
    }
}

/**
 * Clears damage related information in the blackboard.
 */
function clearDamageInfo(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    blackboard.damageInstigatorHash = undefined
    blackboard.damageStimulusDirection = undefined
    blackboard.damageStimulusFocalPoint = undefined
}
