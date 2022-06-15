import { Action, DamageType, EnvironmentQueryStatus, EQSArgument, EQSQueryType, MovementResult, WeaponTag } from "./enums"
import { Ability, Status } from "./enums"
//import { Vec3 } from "vec3"

// The AI Controller, containing all the available commands a Mech can be given
declare class AIController {
    /**
     * Move to the following location. Will automatically path find.
     * @param {number} [acceptanceRadius=800] Fixed distance added to threshold between AI and goal location in destination reach test.
     */
    MoveTo(x: number, y: number, acceptanceRadius?: number): boolean

    /**
     * Move to the following location. Will automatically path find.
     * *For cases when you know the z axis (ie: from an EQS result)*
     * @param location The location to move to.
     * @param {number} [acceptanceRadius=800] Fixed distance added to threshold between AI and goal location in destination reach test.
     */
    MoveToVector(location: Vector, acceptanceRadius?: number): boolean

    /**
     *
     */
    StopMoveTo(): void

    /**
     * Note that this will change the current focal point.
     *
     * @param location
     *
     */
    LookAt(location: Vector): boolean

    /**
     * Aim at a target. The war machine will continously aim towards this target until it loses sight or focus is cleared with {@link ClearFocus}.
     * @param hash The hash of the target (Mech or damageable AI like Robot Dogs). Get hashes and other details from perception in {@link BrainInput}.
     */
    SetFocalPointByHash(hash: string): void

    /** Aim at location.  The war machine will continously aim towards this location until focus is cleared with {@link ClearFocus}. */
    SetFocalPointByLocation(location: Vector): void

    IsFocalPointSet(): boolean

    // Stop aiming at the current target.
    ClearFocus(): void

    /**
     * Starts firing all weapons that match the supplied tag, defaults to All Weapons
     *
     * *Will not trigger weapons that are currently out of ammo*
     * @param tag
     * @param location If set, will not trigger limited-range weapons if location is not within the weapon's range (eg: melee weapons and flamethrowers)
     * @constructor
     */
    WeaponTrigger(tag?: WeaponTag, location?: Vector): void

    // Stops firing all weapons that match the supplied tag, defaults to All Weapons
    WeaponRelease(tag?: WeaponTag): void

    /**
     * Get the current ammo count of a weapon.
     *
     * Always returns 1 if weapon has infinite ammo.
     * *Note: Can only get the ammo count of your own weapons*
     */
    WeaponGetAmmo(hash: string): number

    /**
     * Get the current ammo count of a weapon by tag. Note that if the AI has
     * more than one weapon of the specified tag, the sum of ammos for all
     * those weapons will be returned.
     *
     * @param tag
     */
    WeaponGetAmmoByTag(tag: WeaponTag): number

    /** Returns true if location is within {@link range} of the war machine */
    InRange(location: Vector, range: number): boolean

    /**
     * Shoot up a flare and trigger a loud horn, attracting enemies towards you.
     * Useful if the AI is having trouble finding any enemies to fight.
     */
    Taunt(): void

    TryMeleeAttack(): boolean
    TrySpecialAttack(location: Vector): boolean

    CanActivateAbility(ability: Ability): boolean

    /**
     * Queries status for the given ability.
     *
     * @param ability
     */
    QueryStatus(ability: Action | Ability): Status

    QueryMovementResult(): MovementResult

    /**
     * Run an Environment Query System query to get the optimal position to move the war machine to
     * Get results from eqs in {@link BrainInput}.
     */
    EQS_Query(query: EQSQueryType): void
    /** Removes EQS query status from {@link BrainInput.eqs}, essentially marking it as complete so you know you can run it again */
    EQS_Complete(query: EQSQueryType): void

    /** Set string argument for an EQS query, generally a {@link WarMachine} hash. Call before {@link EQS_Query} */
    EQS_SetArgumentString(query: EQSQueryType, argument: EQSArgument, value: string): void
    /** Set vector argument for an EQS query. Call before {@link EQS_Query} */
    EQS_SetArgumentVector(query: EQSQueryType, argument: EQSArgument, value: Vector): void
}

declare class JavascriptContext {
    GetOwner(): AIController

    OnMessage(name: string, message: string)
}

export interface Vector {
    X: number
    Y: number
    Z: number
}

export interface ScriptError {
    // Which function from {@link AIController} the error/warning is from
    command: string
    severity: "error" | "warning"
    message: string
}

export interface Weapon {
    // Unique hash of the weapon
    hash: string
    // The weapon model
    model: string
    // The weapon skin
    skin: string
    // The weapon name
    name: string
    // The amount of damage the weapon deals per shot/projectile
    damage: number
    // Distance at which damage starts decreasing
    damageFalloff: number
    // How much the damage decreases by per km
    damageFalloffRate: number
    // Enemies within this radius when the projectile hits something is damaged
    damageRadius: number
    // Distance at which damage starts decreasing (must be greater than 0 and less than damageRadius to have any affect)
    damageRadiusFalloff: number
    // The damage type of the weapon
    damageType: DamageType
    //  Projectiles are randomly offset inside a cone. Spread is the half-angle of the cone, in degrees.
    spread: number
    //  Rounds per minute
    rateOfFire: number
    // Speed of the weapon's projectiles in cm/s
    projectileSpeed: number
    // The max amount of ammo this weapon can hold
    maxAmmo: number
    /** The weapon's tags. For use with {@link WeaponTrigger} and {@link WeaponRelease} */
    tags: WeaponTag[]
}

/**
 * War Machine details.
 * -----
 * A War Machine may be a Mech or pure AI controlled machine (eg: Robot Dog).
 *
 * *Note: If war machine is not currently visible; not all details will be up to date.*
 */
export interface WarMachine {
    // Unique hash of the war machine
    hash: string
    // Last known location of the war machine
    location: Vector
    // Last known yaw of the war machine (direction the war machine is facing)
    rotation: number
    // Last known velocity of the war machine
    velocity: Vector
    // The ID of faction the mech belongs to
    factionID: string
    // The name of the war machine
    name: string
    // The model name of the war machine
    model: string
    // Last known health of the war machine
    health: number
    // Max amount of health of the war machine
    healthMax: number
    // Last known shield health of the war machine
    shield: number
    // Max amount of shield health of the war machine
    shieldMax: number
    // Rate at which the shield is recharged when out of combat (health per second)
    shieldRechargeRate: number
    // Movement speed (cm/s)
    speed: number
    // All the weapons this war machine has
    weapons: Weapon[]
}

/**
 * Details of a detected sound.
 *
 * Could be a taunt, gunshot, sword swing, explosion, footstep or even an ability drop
 */
export interface SoundDetails {
    // The location of the sound
    location: Vector
    /**
     * Tag describing the sound
     *
     * Examples: *Weapon, Taunt, Nuke, Pickup.Heal, Pickup.ShieldBuff, Pickup.Ammo*
     */
    tag: string
    // The sound came from a friendly source (ally), check this if you want to ignore friendly gunshots
    friendly: boolean
}

export interface DamageDetails {
    // The amount of damage
    amount: number
    // Whether the damage was down to your shield
    shieldDamage: boolean
    // Whether the damage was friendly fire (caused by an ally)
    friendly?: boolean
    // The type of damage
    damageType: DamageType
    // The direction of the damage relative to the war machine that received the damage
    damageDirection: Vector
    // The unique hash of the war machine that caused the damage
    instigatorHash: string
    // The unique hash of the weapon that caused the damage
    sourceHash: string
    /** The name of what caused the damage (for damage with no {@link sourceHash} such as abilities) */
    sourceName: string
}

// Everything the mech can currently perceive
export interface Perception {
    // Everything the war machine can currently see
    sight: WarMachine[]
    // Everything the war machine heard since the last tick
    sound: SoundDetails[]
    // Details on damage the war machine has taken since the last tick
    damage: DamageDetails[]
}

export interface EnvironmentQuery {
    status: EnvironmentQueryStatus
    location: Vector
}

export interface EQSResults {
    away?: EnvironmentQuery
    cover?: EnvironmentQuery
    hidden?: EnvironmentQuery
    patrol?: EnvironmentQuery
    strafe?: EnvironmentQuery
}

// The input provided to {@link onTick}
export interface BrainInput {
    self: WarMachine
    deltaTime: number
    perception: Perception
    errors: ScriptError[]
    eqs: EQSResults
}
