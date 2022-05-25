import {EnvironmentQueryStatus, EQSArgument, EQSQueryType, WeaponTag} from "./enums";

// The AI Controller, containing all the available commands a Mech can be given
declare class AIController {
    // Move to the following location. Will automatically path find.
    MoveTo(x: number, y: number): void;

    /**
     * Aim at a target. The mech will continously aim towards this target until it loses sight or focus is cleared with {@link ClearFocus}
     * @param hash The hash of the target (Mech or damageable AI like Robot Dogs). Get hashes and other details from {@link BrainInput.perception}
     */
    FocusHash(hash: string): void;

    // Stop aiming at the current target.
    ClearFocus(): void;

    // Starts firing all weapons that match the supplied tag, defaults to All Weapons
    WeaponTrigger(tag?: WeaponTag): void;

    // Stops firing all weapons that match the supplied tag, defaults to All Weapons
    WeaponRelease(tag?: WeaponTag): void;

    EQS_Query(query: EQSQueryType): void;

    EQS_SetArgumentString(argument: EQSArgument, value: string): void;
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

export interface WarMachine {
    // Unique hash of the mech
    hash: string;
    // Last known location of the mech
    location: IntVector;
    // Last known yaw of the mech (direction the mech is facing)
    rotation: number;
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

// Everything the mech can currently perceive
export interface Perception {
    // Everything the mech can currently see
    sight: WarMachine[];
}

export interface EnvironmentQuery {
    status: EnvironmentQueryStatus;
    location: IntVector;
}

export interface EQSResults {
    patrol: EnvironmentQuery;
}

// The input provided to {@link onTick}
export interface BrainInput {
    self: WarMachine;
    perception: Perception;
    errors: ScriptError[];
    eqs: EQSResults;
}