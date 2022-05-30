import {DamageType, EnvironmentQueryStatus, EQSArgument, EQSQueryType, WeaponTag} from "./enums";

// The AI Controller, containing all the available commands a Mech can be given
declare class AIController {
    // Move to the following location. Will automatically path find.
    MoveTo(x: number, y: number): void;

    /**
     * Move to the following location. Will automatically path find.
     * *For cases when you know the z axis (ie: from an EQS result)*
     */
    MoveToVector(location: IntVector): void;

    /**
     * Aim at a target. The mech will continously aim towards this target until it loses sight or focus is cleared with {@link ClearFocus}
     * @param hash The hash of the target (Mech or damageable AI like Robot Dogs). Get hashes and other details from perception in {@link BrainInput}.
     */
    FocusHash(hash: string): void;

    // Stop aiming at the current target.
    ClearFocus(): void;

    /**
     * Starts firing all weapons that match the supplied tag, defaults to All Weapons
     *
     * *Will not trigger weapons that are currently out of ammo*
     * @param tag
     * @param location If set, will not trigger limited-range weapons if location is not within the weapon's range (eg: melee weapons and flamethrowers)
     * @constructor
     */
    WeaponTrigger(tag?: WeaponTag, location?: IntVector): void;

    // Stops firing all weapons that match the supplied tag, defaults to All Weapons
    WeaponRelease(tag?: WeaponTag): void;

    /**
     * Get the current ammo count of a weapon.
     * Always returns 1 if weapon has infinite ammo.
     * *Note: Can only get the ammo count of your own weapons*
     */
    WeaponGetAmmo(hash: string): number;

    /** Returns true if location is within {@link range} of the war machine */
    InRange(location: IntVector, range: number): boolean;

    /**
     * Shoot up a flare and trigger a loud horn, attracting enemies towards you.
     * Useful if the AI is having trouble finding any enemies to fight.
     */
    Taunt(): void;

    /**
     * Run an Environment Query System query to get the optimal position to move the mech to
     * Get results from eqs in {@link BrainInput}.
     */
    EQS_Query(query: EQSQueryType): void;
    /** Removes EQS query status from {@link BrainInput.eqs}, essentially marking it as complete so you know you can run it again */
    EQS_Complete(query: EQSQueryType): void;

    /** Set string argument for an EQS query, generally a {@link WarMachine} hash. Call before {@link EQS_Query} */
    EQS_SetArgumentString(argument: EQSArgument, value: string): void;
    /** Set vector argument for an EQS query. Call before {@link EQS_Query} */
    EQS_SetArgumentVector(argument: EQSArgument, value: IntVector): void;
}

declare class JavascriptContext {
    GetOwner(): AIController;

    OnMessage(name: string, message: string);
}

export interface IntVector {
    X: number;
    Y: number;
    Z: number;
}

export interface ScriptError {
    // Which function from {@link AIController} the error/warning is from
    command: string;
    severity: "error" | "warning";
    message: string;
}

export interface Weapon {
    // Unique hash of the weapon
    hash: string;
    // The weapon model
    model: string;
    // The weapon skin
    skin: string;
    // The weapon name
    name: string;
    // The amount of damage the weapon deals per shot/projectile
    damage: number;
    // Distance at which damage starts decreasing
    damageFalloff: number;
    // How much the damage decreases by per km
    damageFalloffRate: number;
    // Enemies within this radius when the projectile hits something is damaged
    damageRadius: number;
    // Distance at which damage starts decreasing (must be greater than 0 and less than damageRadius to have any affect)
    damageRadiusFalloff: number;
    // The damage type of the weapon
    damageType: DamageType;
    //  Projectiles are randomly offset inside a cone. Spread is the half-angle of the cone, in degrees.
    spread: number;
    //  Rounds per minute
    rateOfFire: number;
    // Speed of the weapon's projectiles in cm/s
    projectileSpeed: number;
    // The max amount of ammo this weapon can hold
    maxAmmo: number;
    /** The weapon's tags. For use with {@link WeaponTrigger} and {@link WeaponRelease} */
    tags: WeaponTag[];
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
    hash: string;
    // Last known location of the war machine
    location: IntVector;
    // Last known yaw of the war machine (direction the war machine is facing)
    rotation: number;
    // Last known velocity of the war machine
    velocity: IntVector;
    // The ID of faction the mech belongs to
    factionID: string;
    // The name of the war machine
    name: string;
    // The model name of the war machine
    model: string;
    // Last known health of the war machine
    health: number;
    // Max amount of health of the war machine
    healthMax: number;
    // Last known shield health of the war machine
    shield: number;
    // Max amount of shield health of the war machine
    shieldMax: number;
    // Rate at which the shield is recharged when out of combat (health per second)
    shieldRechargeRate: number;
    // Movement speed (cm/s)
    speed: number;
    // All the weapons this war machine has
    weapons: Weapon[];
}

/**
 * Details of a detected sound.
 *
 * Could be a taunt, gunshot, sword swing, explosion, footstep or even an ability drop
 */
export interface SoundDetails {
    // The location of the sound
    location: IntVector;
    /**
     * Tag describing the sound
     *
     * Examples: *Weapon, Taunt, Nuke, Pickup.Heal, Pickup.ShieldBuff, Pickup.Ammo*
     */
    tag: string;
    // The sound came from a friendly source (ally), check this if you want to ignore friendly gunshots
    friendly: boolean;
}

// Everything the mech can currently perceive
export interface Perception {
    // Everything the mech can currently see
    sight: WarMachine[];
    // Everything the mech heard since the last tick
    sound: SoundDetails[];
}

export interface EnvironmentQuery {
    status: EnvironmentQueryStatus;
    location: IntVector;
}

export interface EQSResults {
    away?: EnvironmentQuery;
    cover?: EnvironmentQuery;
    hidden?: EnvironmentQuery;
    patrol?: EnvironmentQuery;
    strafe?: EnvironmentQuery;
}

// The input provided to {@link onTick}
export interface BrainInput {
    self: WarMachine;
    perception: Perception;
    errors: ScriptError[];
    eqs: EQSResults;
}