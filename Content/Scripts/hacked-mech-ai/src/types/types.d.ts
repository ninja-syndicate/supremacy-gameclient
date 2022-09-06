import {
    Action,
    DamageType,
    EnvironmentQueryStatus,
    EQSArgument,
    EQSQueryType,
    InteractableTag,
    MovementMode,
    MovementResult,
    Signal,
    UserAction,
    WeaponTag,
    Status,
} from "enums"

/**
 * The AI Controller, containing all the available commands a Mech can be given.
 */
declare class AIController {
    /**
     * Move to the following location ignoring Z-axis. Will automatically path find.
     *
     * @param {number} [acceptanceRadius=525] Fixed distance added to threshold between AI and goal location in destination reach test
     * @returns true if MoveTo request succeed and false otherwise
     */
    MoveTo(x: number, y: number, acceptanceRadius?: number): boolean

    /**
     * Move to the following location. Will automatically path find.
     * For cases when you know the z axis.
     *
     * @param location The location to move to
     * @param {number} [acceptanceRadius=600] Fixed distance added to threshold between AI and goal location in destination reach test
     * @returns true if MoveTo request succeed and false otherwise
     */
    MoveToVector(location: Vector, acceptanceRadius?: number): boolean

    /**
     * Stops the current AI movement. This will cancel {@link MoveTo} and {@link MoveToVector}.
     */
    StopMoveTo(): void

    /**
     * Sets the current AI movement mode to the specified {@link movementMode}.
     *
     * @param movementMode The movement mode to set to. @see {@link MovementMode}
     * @returns true if the AI movement mode is successfully set to requested {@link movementMode} and false otherwise.
     */
    SetMovementMode(movementMode: MovementMode): boolean

    /**
     * Checks if the given location is navigable.
     *
     * @param location the location to check for
     * @returns true if the given location is navigable and false otherwise
     */
    IsNavigable(location: Vector): boolean

    /**
     * Makes AI look at the specified location. Note that this will change the current focal point as well.
     *
     * @param location The location to look at
     * @returns true if setting the look at by location succeed and false otherwise
     */
    LookAt(location: Vector): boolean

    /**
     * Sets the focal point of AI to the target. AI will continuously set the focal point to the target until it loses sight to the target or focus is cleared
     * with {@link ClearFocus}. Note that this will also make primary shootable weapons aim at the target. You will need to use this function to properly aim
     * at small mechs like Robot Dogs.
     *
     * @param hash The hash of the target (Mech or other AI like Robot Dogs). Get hashes and other details from perception in {@link BrainInput}.
     * @returns true if setting the focal point by hash succeed and false otherwise
     */
    SetFocalPointByHash(hash: string): boolean

    /**
     * Sets the focal point of AI to the specified location.
     *
     * AI will maintain the focal point towards this location until the focus is cleared with {@link ClearFocus}.
     * @returns true if setting the focal point by location succeed and false otherwise
     */
    SetFocalPointByLocation(location: Vector): boolean

    /**
     * Checks if the focal point is set.
     *
     * @returns true if AI has focal point and false otherwise.
     */
    IsFocalPointSet(): boolean

    /**
     * Clears the current focal point.
     */
    ClearFocus(): void

    /**
     * Starts firing all weapons that match the supplied tag, defaults to All Weapons
     *
     * *Note that this will not trigger weapons that are currently out of ammo.*
     *
     * @param tag The weapon tag to trigger
     * @param location If set, will not trigger limited-range weapons if the location is not within the weapon's range (eg: melee weapons and flamethrowers)
     */
    WeaponTrigger(tag?: WeaponTag, location?: Vector): void

    /**
     * Releases triggered weapons that match the supplied tag, defaults to All Weapons.
     *
     * @param tag The weapon tag to release
     */
    WeaponRelease(tag?: WeaponTag): void

    /**
     * Get the current ammo count of a weapon.
     *
     * Always returns 1 if weapon has infinite ammo.
     *
     * *Note: Can only get the ammo count of your own weapons.*
     *
     * @param hash The hash of the weapon you want to get ammo count of
     * @returns The ammo count of the weapon
     */
    WeaponGetAmmo(hash: string): number

    /**
     * Get the current ammo count of a weapon by tag. Note that if AI has more than one weapon of the specified tag, the sum of ammo count for all those weapons
     * is returned.
     *
     * @param tag The weapon tag to get ammo count of
     * @returns the sum of ammo count for all weapons that match the {@link tag}
     */
    WeaponGetAmmoByTag(tag: WeaponTag): number

    /**
     * Shoot up a flare and trigger a loud horn, attracting enemies towards you.
     *
     * Useful if the AI is having trouble finding any enemies to fight.
     *
     * @returns true if taunt action succeed and false otherwise
     */
    Taunt(): boolean

    // TODO: This probably isn't needed anymore. Might be removed.
    /**
     *
     */
    TryMeleeAttack(): boolean

    /**
     * Launch missiles from the rocket pod (secondary weapon) to the specified location.
     *
     * @param location The location where you want to launch missile to
     * @returns true if special attack request succeed and false otherwise
     */
    TrySpecialAttack(location: Vector): boolean

    /**
     * Query action status for the given action.
     *
     * @param action The action to query status for
     * @returns @see {@link Status}
     */
    QueryStatus(action: Action | Signal): Status

    /**
     * Query current movement result of {@link MoveTo} or {@link MoveToVector}.
     *
     * @returns @see {@link MovementResult}
     */
    QueryMovementResult(): MovementResult

    /**
     * Checks if the action can be activated (i.e. not on a cooldown).
     *
     * @param action The action to check activation for
     * @returns true if the {@link action} can be activated and false otherwise
     */
    CanActivateAction(action: Action | UserAction): boolean

    /**
     * Run an Environment Query System query to get the optimal position to move the war machine to.
     *
     * Get results from EQS in {@link BrainInput}.
     *
     * @param query The environment query type (@see {@link EQSQueryType})
     * @returns true if the specified EQS query succeeded and false otherwise.
     */
    EQS_Query(query: EQSQueryType): boolean

    /**
     * Removes EQS query status from {@link BrainInput.eqs}, essentially marking it as complete so you know you can run it again.
     *
     * @param query The environment query type (@see {@link EQSQueryType})
     */
    EQS_Complete(query: EQSQueryType): void

    /**
     * Set string argument for an EQS query, generally a {@link WarMachine} hash. Call before {@link EQS_Query}.
     *
     * @param query The environment query type (@see {@link EQSQueryType})
     * @param argument The argument type (@see {@link EQSArgument})
     * @param value The value you want to set the argument to
     */
    EQS_SetArgumentString(query: EQSQueryType, argument: EQSArgument, value: string): void

    /**
     * Set vector argument for an EQS query. Call before {@link EQS_Query}.
     *
     * @param query The environment query type (@see {@link EQSQueryType})
     * @param argument The argument type (@see {@link EQSArgument})
     * @param value The value you want to set the argument to
     */
    EQS_SetArgumentVector(query: EQSQueryType, argument: EQSArgument, value: Vector): void

    /**
     * Set float argument for an EQS query. Call before {@link EQS_Query}.
     *
     * @param query The environment query type (@see {@link EQSQueryType})
     * @param argument The argument type (@see {@link EQSArgument})
     * @param value The value you want to set the argument to
     */
    EQS_SetArgumentFloat(query: EQSQueryType, argument: EQSArgument, value: number): void

    /**
     * Makes AI wait for the specified number of {@link seconds}.
     *
     * @param seconds the number of seconds to wait
     * @returns true if wait request succeed and false otherwise
     */
    Wait(seconds: number): boolean

    // TODO: Don't use this yet, not complete.
    /**
     *
     * @param signal
     */
    SendSignal(signal: Signal): boolean

    /**
     * Checks if the given location is inside the battle zone.
     *
     * @param location the location to test
     * @returns true if the given location is inside the battle zone and false otherwise
     */
    IsInsideBattleZone(location: Vector): boolean

    /**
     * Checks whether the battle zone present in the current map.
     *
     * @returns true if the battle zone is present in the current map and false otherwise
     */
    IsBattleZonePresent(): boolean

    /**
     * Checks if the mech with the given hash is in weapon line of sight.
     *
     * *Note: Will always return false if the mech with the given hash is not in sight.*
     *
     * @param hash The hash of the mech to check for
     * @returns true if the mech is in weapon line of sight and false otherwise
     */
    IsTargetInLOS(hash: string): boolean

    /**
     * Triggers the given user action.
     *
     * @param userAction The user action to trigger. @see {@link UserAction}
     * @returns true if successfully triggered the given {@link userAction} and false otherwise
     */
    TriggerUserAction(userAction: UserAction): boolean
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

/**
 * Detected script errors.
 */
export interface ScriptError {
    // Which function from {@link AIController} the error/warning is from
    command: string
    severity: "error" | "warning"
    message: string
}

/**
 * Weapon details.
 */
export interface Weapon {
    /** The unique hash of the weapon. */
    hash: string
    /** The weapon model. */
    model: string
    /** The weapon skin. */
    skin: string
    /** The weapon name. */
    name: string
    /** The amount of damage the weapon deals per shot/projectile. */
    damage: number
    /** The distance at which the damage starts decreasing. */
    damageFalloff: number
    /** How much the damage decreases by per km. */
    damageFalloffRate: number
    /** Enemies within this radius when the projectile hits something is damaged (radial damage). */
    damageRadius: number
    /** Distance at which damage starts decreasing (must be greater than 0 and less than damageRadius to have any affect). */
    damageRadiusFalloff: number
    /** The damage type of the weapon. */
    damageType: DamageType
    /** The spread of the weapon. Projectiles are randomly offset inside a cone. Spread is the half-angle of the cone, in degrees. */
    spread: number
    /** The number of rounds that can be fired per minute. */
    rateOfFire: number
    /** The speed of the weapon's projectiles in cm/s. */
    projectileSpeed: number
    /** The maximum amount of ammo this weapon can hold. */
    maxAmmo: number
    /** The weapon's tags. For use with {@link WeaponTrigger} and {@link WeaponRelease} */
    tags: WeaponTag[]
}

/**
 * War Machine details.
 * -----
 * A War Machine may be a Mech or pure AI controlled machine (eg: Robot Dog).
 *
 * *Note: If the war machine is not currently visible; not all details will be up to date (hence the "last known").*
 */
export interface WarMachine {
    /** The unique hash of the war machine. This can be used to identify a particular mech. */
    hash: string
    /** The last known location of the war machine. */
    location: Vector
    /** The last known rotation (roll, pitch, yaw) of the war machine. */
    rotation: Vector
    /** The last known velocity of the war machine. */
    velocity: Vector
    /** The ID of the faction the mech belongs to. */
    factionID: string
    /** The name of the war machine. */
    name: string
    /** The model name of the war machine. */
    model: string
    /** The last known health of the war machine. */
    health: number
    /** The maximum amount of health this war machine has. */
    healthMax: number
    /** The last known shield of the war machine. */
    shield: number
    /** The maximum amount of shield this war machine has. */
    shieldMax: number
    /** The rate at which the shield is re-charged when out of combat (shield per second). */
    shieldRechargeRate: number
    /** The maximum movement speed (cm/s) of the war machine. */
    speed: number
    /** All the weapons this war machine has. */
    weapons: Weapon[]
    /** All the abilities this war machine can perform. */
    abilities: UserAction[]
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

/**
 * Details of a received damage.
 */
export interface DamageDetails {
    // The amount of damage
    amount: number
    // Whether the damage was down to your shield
    shieldDamage: boolean
    // Whether the damage was friendly fire (caused by an ally)
    friendly?: boolean
    // The type of damage
    damageType: DamageType
    // The direction of the damage. This is normalized.
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
    /** Everything the war machine can currently see. */
    sight: WarMachine[]
    // Everything the war machine heard since the last tick
    sound: SoundDetails[]
    // Details on damage the war machine has taken since the last tick
    damage: DamageDetails[]
    // Everything the war machine can interact with
    interactable: InteractableDetails[]
}

/**
 * Environment query.
 */
export interface EnvironmentQuery {
    /** The current status of environment query (@see {@link EnvironmentQueryStatus}). */
    status: EnvironmentQueryStatus
    /** The resulting location of environment query. Only valid if the environment query succeeded. */
    location: Vector
}

/**
 * Environment query result.
 */
export interface EQSResults {
    away?: EnvironmentQuery
    cover?: EnvironmentQuery
    hidden?: EnvironmentQuery
    patrol?: EnvironmentQuery
    strafe?: EnvironmentQuery
    closeStrafe?: EnvironmentQuery
    battleZone?: EnvironmentQuery
}

/**
 * Details of an interactable such as heal crate.
 */
export interface InteractableDetails {
    tag: InteractableTag
    eventID: string
    location: Vector
    /** If this interactable is spawned via user action, this will be set to the faction ID that instigated it. Empty string otherwise. */
    instigatorFactionID: string
}

/**
 * The input provided to {@link onBegin} and {@link onTick}.
 */
export interface BrainInput {
    /** Information about itself (@see {@link WarMachine}). */
    self: WarMachine
    /** Time elapsed since last tick. 0 on {@link onBegin}. */
    deltaTime: number
    /** Things that AI can currently perceive (@see {@link Perception}). */
    perception: Perception
    /** List of detected runtime warnings/errors in the script (@see {@link ScriptError}). */
    errors: ScriptError[]
    /** Result of executed environment queries (@see {@link EQSResults}). */
    eqs: EQSResults
}
