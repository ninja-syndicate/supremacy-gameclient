import {EnvironmentQueryStatus, EQSArgument, EQSQueryType, WeaponTag} from "./enums";

// The AI Controller, containing all the available commands a Mech can be given
declare class AIController {
    // Move to the following location. Will automatically path find.
    MoveTo(x: number, y: number): void;

    /**
     * Aim at a target. The mech will continously aim towards this target until it loses sight or focus is cleared with {@link ClearFocus}
     * @param hash The hash of the target (Mech or damageable AI like Robot Dogs). Get hashes and other details from perception in {@link BrainInput}.
     */
    FocusHash(hash: string): void;

    // Stop aiming at the current target.
    ClearFocus(): void;

    // Starts firing all weapons that match the supplied tag, defaults to All Weapons
    WeaponTrigger(tag?: WeaponTag): void;

    // Stops firing all weapons that match the supplied tag, defaults to All Weapons
    WeaponRelease(tag?: WeaponTag): void;

    /**
     * Run an Environment Query System query to get the optimal position to move the mech to
     * Get results from eqs in {@link BrainInput}.
     */
    EQS_Query(query: EQSQueryType): void;
    // Sets EQS query status back to Ready, essentially marking it as complete so you know you can run it again
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

/**
 * War Machine details.
 * -----
 * A War Machine may be a Mech or pure AI controlled machine (eg: Robot Dog).
 *
 * *Note: If war machine is not currently visible; not all details will be up to date.*
 */
export interface WarMachine {
    // Unique hash of the mech
    hash: string;
    // Last known location of the mech
    location: IntVector;
    // Last known yaw of the mech (direction the mech is facing)
    rotation: number;
    // Last known velocity of the mech
    velocity: IntVector;
    // The ID of faction the mech belongs to
    factionID: string;
    // Mech's name
    name: string;
    // Mech's model name
    model: string;
    // Last known health of the mech
    health: number;
    // Max amount of health of the mech
    healthMax: number;
    // Last known shield health of the mech
    shield: number;
    // Max amount of shield health of the mech
    shieldMax: number;
    // Rate at which the shield is recharged when out of combat (health per second)
    shieldRechargeRate: number;
    // Movement speed (cm/s)
    speed: number;
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
    away: EnvironmentQuery;
    cover: EnvironmentQuery;
    hidden: EnvironmentQuery;
    patrol: EnvironmentQuery;
    strafe: EnvironmentQuery;
}

// The input provided to {@link onTick}
export interface BrainInput {
    self: WarMachine;
    perception: Perception;
    errors: ScriptError[];
    eqs: EQSResults;
}