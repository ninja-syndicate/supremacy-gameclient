import { EQSQueryType } from "enums"
import { BrainInput, EnvironmentQuery, InteractableDetails, Vector, WarMachine, Weapon } from "types"

/**
 * This is the memory of the AI.
 *
 * It stores all the information that the AI needs to make a decision. The blackboard will be provided as input to your behavior tree nodes to allow you to
 * make decision based on the state of the memory.
 *
 * You can add/remove properties as you deem necessary to customize your own AI.
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
    desiredPickupLocation?: Vector

    targetLastKnownLocation?: Vector
    targetLastKnownVelocity?: Vector
    targetPredictedLocation?: Vector

    damageInstigatorHash?: string
    damageStimulusDirection?: Vector
    damageStimulusFocalPoint?: Vector
    damageStimulusEstimateLocation?: Vector
    damageHiddenLocation?: Vector
    isLastDamageFromTarget: boolean

    leftArmWeapon: Weapon
    rightArmWeapon: Weapon
    secondaryWeapon?: Weapon

    canMelee: boolean
    canUseSpecialAttack: boolean
}
