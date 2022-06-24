import { BehaviorTree } from "behaviortree"
import { EnvironmentQueryStatus, InteractableTag, SoundType, WeaponTag } from "enums"
import { BrainInput, DamageDetails, InteractableDetails, SoundDetails, WarMachine } from "types"
import { AIBlackboard } from "./blackboard"
import { add, distanceTo, distanceToVec, multiply } from "./helper"
import { AI } from "./index"
import { BT_Root } from "./trees/BT_Root"
import { StringToEQSQueryType } from "./utils"

export let tree = new BehaviorTree({
    tree: BT_Root,
    blackboard: {
        target: null,
        eqsResults: {},
    } as AIBlackboard,
})

/**
 * This funciton gets called when the AI begins.
 *
 * You can set up things that only need to be done once here.
 *
 * @param input
 */
export const onBegin = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

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
 * This function gets called every tick rate.
 *
 *
 * @param input
 */
export const onTick = (input: BrainInput) => {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    // Check errors
    if (input.errors.length !== 0) {
        input.errors.forEach((e) => console.log(`${e.severity}: ${e.command}: ${e.message}`))
    }

    updateBlackboard(input)

    // Run Behaviour Tree
    tree.step()

    // EQS - Run callbacks when they succeed
    for (let [key, value] of Object.entries(input.eqs)) {
        blackboard.eqsResults[key] = value
        if (value.status === EnvironmentQueryStatus.Success) {
            AI.EQS_Complete(StringToEQSQueryType(key))
        }
    }
}

/**
 * Updates the blackboard.
 * 
 * @param input
 */
function updateBlackboard(input: BrainInput): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    blackboard.input = input

    const bestTarget: WarMachine = findBestTarget(blackboard)
    if (bestTarget === null) {
        clearBlackboardTarget()
    } else {
        blackboard.target = bestTarget
    }
    updateBlackboardSight(input.perception.sight)
    updateBlackboardDamage(input.perception.damage)
    updateBlackboardSound(input.perception.sound)
    updateBlackboardInteractable(input.perception.interactable)
}

/**
 * 
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

function clearDamageInfo(): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    blackboard.damageInstigatorHash = undefined
    blackboard.damageStimulusDirection = undefined
    blackboard.damageStimulusFocalPoint = undefined
}

/**
 * Only update the sight info.
 *
 * @param perception
 */
function updateBlackboardSight(sight: WarMachine[]): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    if (blackboard.damageInstigatorHash !== undefined) {
        const idx = sight.findIndex((m) => m.hash === blackboard.damageInstigatorHash && m.health <= 0)
        if (idx !== -1) {
            clearDamageInfo()
        }
    }

    // TODO: figure out why it doesn't update target sometimes...
    if (!blackboard.target) return

    if (sight.length === 0) {
        blackboard.canSeeTarget = false
    } else {
        const targetVisIndex: number = sight.findIndex((m) => m.hash === blackboard.target.hash)

        blackboard.canSeeTarget = targetVisIndex !== -1
        if (blackboard.canSeeTarget) {
            blackboard.targetLastKnownLocation = blackboard.target.location
            blackboard.targetPredictedLocation = blackboard.target.location
            blackboard.targetLastKnownVelocity = blackboard.target.velocity
        }
    }
    if (blackboard.targetLastKnownLocation !== undefined) {
        // TODO: Project to navigation and clear if not valid.
        // Also expose a new EQS to allow searching for target in the direction.
        blackboard.targetPredictedLocation = add(blackboard.targetPredictedLocation, multiply(blackboard.targetLastKnownVelocity, blackboard.input.deltaTime))
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
    if (damageDetails.length === 0) return

    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const lastIdx: number = damageDetails.length - 1

    if (damageDetails[lastIdx].friendly) return

    blackboard.damageInstigatorHash = damageDetails[lastIdx].instigatorHash
    blackboard.damageStimulusDirection = damageDetails[lastIdx].damageDirection
    blackboard.damageStimulusFocalPoint = add(blackboard.input.self.location, multiply(blackboard.damageStimulusDirection, 10000))
    blackboard.lastHitLocation = blackboard.input.self.location
    blackboard.isLastDamageFromTarget = blackboard.target && blackboard.target.hash === damageDetails[lastIdx].instigatorHash
}

// TODO: handle signaling.
/**
 * Updates the sound related blackboard information (@see {@link SoundDetails}).
 *
 * Currently, it only considers last taunt sound generated by the enemy AI. You may modify this implementation to also consider noise generated by the friendly
 * AIs, gun sound, and evaluate the score of new sounds based on the distance and type.
 *
 * @param soundDetails
 */
function updateBlackboardSound(soundDetails: SoundDetails[]): void {
    if (soundDetails.length === 0) return

    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

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
 * Updates the interactable related blackboard information (@see {@link InteractableDetails}).
 *
 * @param interactables
 */
function updateBlackboardInteractable(interactables: InteractableDetails[]): void {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard

    blackboard.interactables = interactables
    if (blackboard.interactables.length === 0) {
        blackboard.desiredPickUpLocation = undefined
        return
    }

    const bestPickup = findBestPickup(blackboard)
    if (bestPickup !== undefined) {
        blackboard.desiredPickUpLocation = bestPickup.location
    }
}

/**
 * Finds the best pick up based on the current blackboard state.
 *
 * @param blackboard
 * @returns
 */
function findBestPickup(blackboard: AIBlackboard): InteractableDetails {
    const scores = evaluateInteractable(blackboard)
    const idx: number = scores.indexOf(Math.max(...scores))
    return scores[idx] > 0 ? blackboard.interactables[idx] : undefined
}

/**
 * Scoring function for interactables.
 *
 * @param blackboard
 * @returns
 */
function evaluateInteractable(blackboard: AIBlackboard): number[] {
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

    let scores = []
    for (const interactable of blackboard.interactables) {
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
 *
 */
function findBestTarget(blackboard: AIBlackboard): WarMachine {
    const mechsBySight: WarMachine[] = blackboard.input.perception.sight
    const damageDetails: DamageDetails[] = blackboard.input.perception.damage

    // For now, only consider mechs by sight.
    // TODO: Maintain list of mechs in memory and
    // use damage details to figure out which mech it is associated with.
    if (mechsBySight.length === 0) {
        // maybe return null after some time if lost.
        return blackboard.target
    }

    const filtered = mechsBySight.filter((m) => filter(m))

    // Get the index of the first target with largest score.
    const scores: number[] = filtered.map(score)
    const idx: number = scores.indexOf(Math.max(...scores))
    if (idx === -1) {
        if (blackboard.target) {
            const targetVisIndex: number = mechsBySight.findIndex((m) => m.hash === blackboard.target.hash)
            return targetVisIndex !== -1 && mechsBySight[targetVisIndex].health <= 0 ? null : blackboard.target
        } else {
            return null
        }
    }

    return filtered[idx]
}

/**
 *
 *
 * @param mech
 *
 * @returns
 */
// TODO: do inverse
function filter(mech: WarMachine, inverse: boolean = false): boolean {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const MaxDistanceToConsider: number = 50000

    const filterByAlive = () => mech.health > 0
    const filterByFaction = () => blackboard.input.self.factionID !== mech.factionID
    const filterByDistance = () => distanceTo(blackboard.input.self, mech) <= MaxDistanceToConsider
    const filterFuncs = [filterByAlive, filterByFaction, filterByDistance]

    return filterFuncs.map((func) => func()).reduce((a, b) => a && b)
}

/**
 *
 *
 * @param mech
 *
 * @returns
 */
function score(mech: WarMachine): number {
    const blackboard: AIBlackboard = tree.blackboard as AIBlackboard
    const MaxDistanceToConsider: number = 50000

    // Normalized score functions.
    const scoreByHealth = (m: WarMachine) => 1 - (m.health + m.shield) / (m.healthMax + m.shieldMax)
    const scoreByDistance = (m: WarMachine) => 1 - Math.min(1, distanceTo(blackboard.input.self, m) / MaxDistanceToConsider)
    const scoreFuncs = [scoreByHealth, scoreByDistance]

    const totalScore = scoreFuncs.map((func) => func(mech)).reduce((a, b) => a + b)

    // Normalize total score.
    return totalScore / scoreFuncs.length
}
