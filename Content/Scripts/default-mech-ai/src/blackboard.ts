import { EnvironmentQuery, WarMachine, Vector, Weapon, Perception, BrainInput } from "types"
import { EQSQueryType } from "enums"

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

    desiredPickUpLocation?: Vector
    healCrateLocation?: Vector
    shieldCrateLocation?: Vector
    ammoCrateLocation?: Vector

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
