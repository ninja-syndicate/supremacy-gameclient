import { EQSQueryType } from "enums"
import { BrainInput, EnvironmentQuery, InteractableDetails, Vector, WarMachine, Weapon } from "types"

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
    isLastDamageFromTarget: boolean

    leftArmWeapon: Weapon
    rightArmWeapon: Weapon
    secondaryWeapon?: Weapon

    canMelee: boolean
    canUseSpecialAttack: boolean
}
