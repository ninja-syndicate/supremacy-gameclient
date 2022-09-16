import { DamageTracker } from "@root/damagetracker"
import { Sound } from "@root/Sound"
import { Action, EQSQueryType, MovementMode } from "enums"
import { BrainInput, EnvironmentQuery, Vector, WarMachine, Weapon } from "types"

/**
 * This is the memory of the AI.
 *
 * It stores all the information that the AI needs to make a decision. The blackboard will be provided as input to your behavior tree nodes to allow you to
 * make decision based on the state of the memory.
 *
 * You can add/remove properties as you deem necessary to customize your own AI.
 */
export interface AIBlackboard {
    /** The input provided to the AI on onBegin and onTick. */
    input: BrainInput

    /**
     * Accumulation of the elapsed time since the script has been running in seconds.
     * Note that this may not actually correspond to the real elapsed time since the script can be disabled as a result of user action.
     */
    currentTime: number

    eqsResults: Map<EQSQueryType, EnvironmentQuery>
    actionStatus: Map<Action, boolean>
    currentMovementMode: MovementMode
    weapons: Weapon[]
    patrolLocation?: Vector

    target: WarMachine | null
    /** Can AI currently see the {@link target}? */
    canSeeTarget: boolean
    isTargetInWeaponLOS: boolean
    /** Only valid when AI cannot see the target. That is, {@link canSeeTarget} is false. */
    targetLostSightTime?: number

    heardNoise: boolean
    noiseLocation?: Vector
    lastHitLocation?: Vector
    lastWeaponNoise: Sound

    lookAtLocation?: Vector

    strafeLocation?: Vector
    closeStrafeLocation?: Vector
    hiddenLocation?: Vector
    coverLocation?: Vector
    /** A location inside the battle zone generated by {@link EQSArgument.BattleZone}. */
    battleZoneLocation?: Vector
    /** Does battle zone exist in the current map? */
    isBattleZonePresent: boolean

    desiredPickupLocation?: Vector

    targetLastKnownLocation?: Vector
    targetLastKnownVelocity?: Vector
    targetPredictedLocation?: Vector
    lastTargetUpdateTime: number

    /** Tracks the received damage from other AIs. */
    damageTracker: DamageTracker

    damageStimulusTime?: number
    damageInstigatorHash?: string
    damageStimulusDirection?: Vector
    damageStimulusFocalPoint?: Vector
    damageStimulusEstimateLocation?: Vector
    damageHiddenLocation?: Vector
    isLastDamageFromTarget: boolean

    leftArmWeapon: Weapon
    rightArmWeapon: Weapon
    secondaryWeapon?: Weapon

    arcLaunchLocation?: Vector
    hasPrimaryAmmo: boolean

    /** Tolerable ideal range at which shootable weapons are still effective. This value is based on the {@link optimalEngagmentRange}. */
    idealEngagementRange: number
    /** Optimal range at which shootable weapons do full damage. */
    optimalEngagementRange: number
    /** Whether AI has any melee weapons. */
    canMelee: boolean
}
