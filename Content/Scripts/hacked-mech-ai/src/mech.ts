import { BehaviorTree } from "behaviortree"
import { Action, EnvironmentQueryStatus, InteractableTag, MovementMode, SoundType, UserAction, WeaponTag } from "enums"
import { BrainInput, DamageDetails, InteractableDetails, SoundDetails, Vector, WarMachine, Weapon } from "types"
import { AIBlackboard } from "@blackboards/blackboard"
import { add, distanceTo, distanceToVec, multiply } from "./helper"
import { AI } from "@root/index"
import { BT_Root } from "@trees/BT_Root"
import { StringToEQSQueryType } from "./utils"
import { Sound } from "@root/Sound"
import { Evaluator } from "@utility/evaluator"
import { Test } from "@utility/test"
import { scoreByDistance } from "@utility/helper"
import { CURRENT_AI_CONFIG } from "@root/aiconfig"
import { Damage } from "@root/damage"
import { DamageTracker } from "@root/damagetracker"

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
        damageTracker: new DamageTracker(),
        actionStatus: new Map<Action, boolean>(),
    } as AIBlackboard,
})

const init_engagement_range = (input: BrainInput, blackboard: AIBlackboard) => {
    const primaryWeapons = input.Self.Weapons.filter((w) => w.Tags.find((t) => t === WeaponTag.Primary))

    if (primaryWeapons.length === 0) {
        console.log(`Hash: ${input.Self.Hash}, Name: ${input.Self.Name} AI has no primary weapons. AI will not work properly.`)
    } else {
        const primaryGuns = primaryWeapons.filter((w) => !w.Tags.find((t) => t === WeaponTag.Melee))
        const validOptimalRanges = primaryGuns.filter((w) => w.DamageFalloff > 0)
        if (validOptimalRanges.length === 0) {
            console.log(`Hash: ${input.Self.Hash}, Name: ${input.Self.Name} AI has no valid optimal range setup. Defaulting optimal range to melee range.`)
            blackboard.idealEngagementRange = CURRENT_AI_CONFIG.closeCombatEnterRange * CURRENT_AI_CONFIG.optimalRangeMultiplier
            blackboard.optimalEngagementRange = CURRENT_AI_CONFIG.closeCombatEnterRange
        } else {
            // Calculate optimal engagement range and ideal range based on that.
            const minOptimalRange = Math.min(...validOptimalRanges.map((w) => w.DamageFalloff))
            blackboard.idealEngagementRange = minOptimalRange * CURRENT_AI_CONFIG.optimalRangeMultiplier
            blackboard.optimalEngagementRange = minOptimalRange
        }
    }
}

const init_weapon = (input: BrainInput, blackboard: AIBlackboard) => {
    init_engagement_range(input, blackboard)

    const secondaryWeapons: Weapon[] = input.Self.Weapons.filter((w) => w.Tags.find((t) => t === WeaponTag.Secondary))

    // For now, only one secondary weapon can be equipped.
    blackboard.secondaryWeapon = secondaryWeapons.length !== 0 ? secondaryWeapons[0] : null

    const meleeWeapons: Weapon[] = input.Self.Weapons.filter((w) => w.Tags.find((t) => t === WeaponTag.Melee))
    blackboard.canMelee = meleeWeapons.length !== 0

    blackboard.weapons = input.Self.Weapons
}

/**
 * This function gets called when AI begins.
 *
 * You can set up things that only need to be done once here.
 *
 * @param input @see {@link BrainInput} for details.
 */
export const onBegin = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    init_weapon(input, blackboard)

    blackboard.currentTime = 0
    blackboard.currentMovementMode = MovementMode.Walk
    blackboard.isBattleZonePresent = AI.IsBattleZonePresent()
    console.log(`${input.Self.Hash}: ${input.Self.Name} AI Started`)
}

/**
 * This function gets called every tick rate that AI is capable of.
 *
 * @param input @see {@link BrainInput} for details.
 */
export const onTick = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    // Check for any errors and log it. This will be useful for debugging.
    if (input.Errors.length !== 0) {
        input.Errors.forEach((e) => console.log(`${e.Severity}: ${e.Command}: ${e.Message}`))
    }

    // Update the blackboard based on the new input.
    updateBlackboard(input)

    // Run behavior tree.
    tree.step()

    // EQS - Run callbacks when they succeed.
    for (let [key, value] of Object.entries(input.EnvQueryStatus)) {
        blackboard.eqsResults[key] = value
        if (value.Status === EnvironmentQueryStatus.Success) {
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
    const currentWeapons: Weapon[] = blackboard.weapons

    // Re-init weapons if equipped a new weapon. TODO: Handle weapon change.
    if (currentWeapons.length !== input.Self.Weapons.length) {
        init_weapon(input, blackboard)
    }

    // Copy over the new input for easy access.
    blackboard.input = input
    blackboard.currentTime += input.DeltaTime

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
    // updateTargetLOS()
}

/*
function updateTargetLOS() {
    // TODO: Add LOS to target selection.
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    if (blackboard.target) {
        blackboard.isTargetInWeaponLOS = AI.IsTargetInLOS(blackboard.target.hash)
    } else {
        blackboard.isTargetInWeaponLOS = false
    }
}
*/

/**
 * Updates the sight related information in the blackboard.
 */
function updateBlackboardSight(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const sight: WarMachine[] = blackboard.input.Perception.Sight

    // Clear damage related information if the one that caused damage is dead.
    if (typeof blackboard.damageInstigatorHash !== "undefined") {
        const idx = sight.findIndex((m) => m.Hash === blackboard.damageInstigatorHash && m.Health <= 0)
        if (idx !== -1) {
            clearDamageInfo()
        }
    }

    // Nothing to do if the target is not set.
    if (!blackboard.target) return

    if (sight.length === 0) {
        // Initial loss, set the target lost time.
        if (blackboard.canSeeTarget) {
            blackboard.targetLostSightTime = blackboard.currentTime
        }
        blackboard.canSeeTarget = false
    } else {
        // Get the index of the current target in the sight array.
        const targetVisIndex: number = sight.findIndex((m) => m.Hash === blackboard.target.Hash)
        const isTargetInSight: boolean = targetVisIndex !== -1

        if (blackboard.canSeeTarget && !isTargetInSight) {
            // Initial loss, set the target lost time.
            blackboard.targetLostSightTime = blackboard.currentTime
        }

        // Update the target information if it's in sight.
        blackboard.canSeeTarget = isTargetInSight
        if (blackboard.canSeeTarget) {
            blackboard.targetLastKnownLocation = blackboard.target.Location
            blackboard.targetPredictedLocation = blackboard.target.Location
            blackboard.targetLastKnownVelocity = blackboard.target.Velocity
            blackboard.lastTargetUpdateTime = blackboard.currentTime
        }
    }
    if (typeof blackboard.targetLostSightTime === "undefined") return
    if (typeof blackboard.targetLastKnownLocation === "undefined") return
    if (typeof blackboard.targetLastKnownVelocity === "undefined") return

    // Calculate a new target predicted location based on its last known velocity and the time elapsed since prediction update.
    const elapsedTime: number = blackboard.currentTime - blackboard.lastTargetUpdateTime
    if (elapsedTime >= CURRENT_AI_CONFIG.predictionUpdateInterval) {
        // TODO: Project to navigation and clear if not valid when navigating.
        blackboard.targetPredictedLocation = add(blackboard.targetPredictedLocation, multiply(blackboard.targetLastKnownVelocity, elapsedTime))
        blackboard.lastTargetUpdateTime = blackboard.currentTime
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
    const damageDetails: DamageDetails[] = blackboard.input.Perception.Damage

    // Return if nothing to update.
    if (damageDetails.length === 0) return

    // Get the enemy damage details. Feel free to modify this logic to do something about friendly damage
    const enemyDamageDetails: DamageDetails[] = damageDetails.filter((d) => !d.IsFriendly)
    if (enemyDamageDetails.length === 0) return

    // Update damage info using the last enemy damage details.
    const lastIdx: number = enemyDamageDetails.length - 1
    blackboard.damageStimulusTime = blackboard.currentTime
    blackboard.damageInstigatorHash = enemyDamageDetails[lastIdx].InstigatorHash
    blackboard.damageStimulusDirection = enemyDamageDetails[lastIdx].Direction
    blackboard.damageStimulusFocalPoint = add(blackboard.input.Self.Location, multiply(blackboard.damageStimulusDirection, 10000))
    blackboard.lastHitLocation = blackboard.input.Self.Location
    blackboard.isLastDamageFromTarget = blackboard.target && blackboard.target.Hash === enemyDamageDetails[lastIdx].InstigatorHash

    blackboard.damageTracker.addDamage(...enemyDamageDetails.map((d) => new Damage(blackboard.currentTime, d)))
}

/**
 * Updates the sound related information in the blackboard.
 *
 * You may modify this implementation to also consider noise generated by the friendly AIs.
 *
 * @see {@link SoundDetails} for sound details.
 */
function updateBlackboardSound(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const soundDetails: SoundDetails[] = blackboard.input.Perception.Sound
    const selfLocation: Vector = blackboard.input.Self.Location

    if (soundDetails.length === 0) return

    const enemySounds = soundDetails
    const enemyTauntSounds = enemySounds.filter((s) => s.Type === SoundType.Taunt && AI.IsNavigable(s.Location))
    const enemyWeaponSounds = enemySounds.filter((s) => s.Type === SoundType.Weapon && AI.IsNavigable(s.Location))

    /*
    if (blackboard.noiseLocation !== undefined) {
        // enemyTauntSounds.push(blackboard.noiseLocation))
    }
    if (blackboard.lastWeaponNoise !== undefined) {
        enemyWeaponSounds.push(blackboard.lastWeaponNoise.soundDetail)
    }
    */
    const bestWeaponSound: SoundDetails = new Evaluator(enemyWeaponSounds).addTest(new Test((s) => scoreByDistance(selfLocation, s.Location))).getBestItem()
    const bestTauntSound: SoundDetails = new Evaluator(enemyTauntSounds).addTest(new Test((s) => scoreByDistance(selfLocation, s.Location))).getBestItem()

    if (bestWeaponSound !== undefined) {
        blackboard.lastWeaponNoise = new Sound(bestWeaponSound, blackboard.currentTime)
    }
    if (bestTauntSound !== undefined) {
        // Update the last noise location to the last enemy taunt noise location.
        blackboard.heardNoise = true
        blackboard.noiseLocation = bestTauntSound.Location
    }
}

/**
 * Updates the interactable related information in the blackboard.
 *
 * @see {@link InteractableDetails} for interactable details.
 */
function updateBlackboardInteractable(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const interactables: InteractableDetails[] = blackboard.input.Perception.Interactable

    // Clear the desired pickup location if there are no interactables.
    if (interactables.length === 0) {
        if (typeof blackboard.desiredPickupLocation !== "undefined") delete blackboard.desiredPickupLocation

        return
    }

    // Otherwise find the best pickup and update desired pickup location.
    const bestPickup = findBestPickup()
    if (bestPickup !== undefined) {
        const isNavigable: boolean = AI.IsNavigable(bestPickup.Location)
        if (isNavigable) {
            blackboard.desiredPickupLocation = bestPickup.Location
        }
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
    return scores[idx] > 0 ? blackboard.input.Perception.Interactable[idx] : undefined
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

    const self = blackboard.input.Self
    // const totalAmmo = self.weapons.map((w) => (w.tags.findIndex((t) => t === WeaponTag.Primary) !== -1 ? w.maxAmmo : 0)).reduce((a, b) => a + b)
    // console.log(JSON.stringify("total ammo is") + totalAmmo)
    const scoreByHealth = (x: InteractableDetails) => 1 - self.Health / self.HealthMax
    const scoreByShield = (x: InteractableDetails) => 1 - self.Shield / self.ShieldMax
    const scoreByDistance = (x: InteractableDetails) => 1 - Math.min(1, distanceToVec(self.Location, x.Location) / MaxDistanceToConsider)
    // const scoreByAmmo = () => AI.WeaponGetAmmoByTag(WeaponTag.Primary) / totalAmmo

    // const ammoCrateFuncs = [() => 1 - scoreByHealth(), () => 1 - scoreByShield(), scoreByDistance(blackboard.ammoCrateLocation), scoreByAmmo]

    const healCrateFuncs = [scoreByHealth, (x) => scoreByShield(x) - 1, scoreByDistance]
    const shieldCrateFuncs = [(x) => scoreByHealth(x) - 1, scoreByShield, scoreByDistance]

    // TODO: normalization of score?
    let scores = []
    for (const interactable of blackboard.input.Perception.Interactable) {
        let score = 0
        if (interactable.Tag === InteractableTag.HealCrate) {
            score = healCrateFuncs.map((func) => func(interactable)).reduce((a, b) => a + b)
        } else if (interactable.Tag === InteractableTag.ShieldCrate) {
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
    const mechsBySight: WarMachine[] = blackboard.input.Perception.Sight
    const damageDetails: DamageDetails[] = blackboard.input.Perception.Damage

    // Filter the mechs and maintain the same target if there are no suitable mechs.
    const targetVisIndex: number = blackboard.target ? mechsBySight.findIndex((m) => m.Hash === blackboard.target.Hash) : -1
    const filteredMechs = mechsBySight.filter((m) => filter(m))
    if (filteredMechs.length === 0) {
        return targetVisIndex === -1 ? blackboard.target : null
    }

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

    // Filter functions. Add more filter functions as you deem appropriate.
    const filterByAlive = () => mech.Health > 0
    // const filterByFaction = () => blackboard.input.self.factionID !== mech.factionID
    const filterByDistance = () => distanceTo(blackboard.input.Self, mech) <= CURRENT_AI_CONFIG.sightMaxDistance
    const filterFuncs = [filterByAlive, filterByDistance]

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
    const MaxDamage: number = 2000

    // Score functions.
    const scoreByHealth = (m: WarMachine) => 1 - (m.Health + m.Shield) / (m.HealthMax + m.ShieldMax)
    const scoreByDistance = (m: WarMachine) => 1 - Math.min(1, distanceTo(blackboard.input.Self, m) / CURRENT_AI_CONFIG.sightMaxDistance)
    const scoreByDamageWindow = (m: WarMachine) => Math.min(1, blackboard.damageTracker.getTotalDamageByTime(blackboard.currentTime, 10, m.Hash) / MaxDamage)
    const scoreByCurrentTarget = (m: WarMachine) => 0.2 * (blackboard.target && blackboard.target.Hash === m.Hash ? 1 : 0)
    const scoreByFaction = (m: WarMachine) => (m.FactionID === blackboard.input.Self.FactionID ? 5 : 0)
    const scoreFuncs = [scoreByHealth, scoreByDistance, scoreByFaction, scoreByDamageWindow, scoreByCurrentTarget]

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
    blackboard.isTargetInWeaponLOS = false
    if (typeof blackboard.targetLostSightTime !== "undefined") {
        delete blackboard.targetLostSightTime
    }
    if (typeof blackboard.targetLastKnownLocation !== "undefined") {
        delete blackboard.targetLastKnownLocation
    }
    if (typeof blackboard.targetPredictedLocation !== "undefined") {
        delete blackboard.targetPredictedLocation
    }
}

/**
 * Clears damage related information in the blackboard.
 */
function clearDamageInfo(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    if (typeof blackboard.damageStimulusTime !== "undefined") {
        delete blackboard.damageStimulusTime
    }
    if (typeof blackboard.damageInstigatorHash !== "undefined") {
        delete blackboard.damageInstigatorHash
    }
    if (typeof blackboard.damageStimulusDirection !== "undefined") {
        delete blackboard.damageStimulusDirection
    }
    if (typeof blackboard.damageStimulusFocalPoint !== "undefined") {
        delete blackboard.damageStimulusFocalPoint
    }
}
