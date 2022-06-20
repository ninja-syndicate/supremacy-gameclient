import { EnvironmentQuery, WarMachine, Vector, Weapon, Perception, BrainInput, InteractableDetails } from "types"
import { EQSQueryType } from "enums"
import { Pickup } from "./pickup"

/**
 *
 *
 */
export interface AIBlackboard {
    input: BrainInput

    eqsResults: Map<EQSQueryType, EnvironmentQuery>
    weapons: Weapon[]
    patrolLocation?: Vector

    target: WarMachine | null
    canSeeTarget: boolean

    // TODO: clean up
    heardNoise: boolean
    noiseLocation?: Vector
    lastHitLocation?: Vector

    lookAtLocation?: Vector

    strafeLocation?: Vector
    hiddenLocation?: Vector
    coverLocation?: Vector

    interactables: InteractableDetails[]
    desiredPickUpLocation?: Vector
    
    targetLastKnownLocation?: Vector
    targetLastKnownVelocity?: Vector
    targetPredictedLocation?: Vector

    damageInstigatorHash?: string
    damageStimulusDirection?: Vector
    damageStimulusFocalPoint?: Vector
    damageStimulusEstimateLocation?: Vector

    leftArmWeapon: Weapon
    rightArmWeapon: Weapon
    secondaryWeapon?: Weapon

    canMelee: boolean
    canUseSpecialAttack: boolean
}
