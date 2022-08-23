/**
 * Available weapon tags.
 */
export const enum WeaponTag {
    All = "Weapon",
    Primary = "Weapon.Primary",
    PrimaryLeftArm = "Weapon.Primary.LeftArm",
    PrimaryRightArm = "Weapon.Primary.RightArm",
    Secondary = "Weapon.Secondary",
    Melee = "Weapon.Melee",
    Flamethrower = "Weapon.Flamethrower",
    Arced = "Weapon.Arced",
}

/**
 * Available environment query types
 *
 * {@link EQSQueryType.Cover} - Generates a cover location. This requires {@link Origin} and {@link LastHitLocation} arguments to be set.
 * {@link EQSQueryType.Hidden} - Generates a possible target hidden location. This requires {@link EQSArgument.TargetPredictedLocation} argument to be set.
 * {@link EQSQueryType.Patrol} - Generates a patrol location. This requires {@link Origin} argument to be set. And optionally {@link EQSArgument.GridSize} and
 * {@link EQSArgument.SpaceBetween}.
 * {@link EQSQueryType.Strafe} - Generates a strafe location. Useful when AI is in combat state. This environment query requires {@link EQSArgument.TargetHash}
 * argument to be set. And optionally {@link EQSArgument.GridSize} and {@link EQSArgument.SpaceBetween}.
 */
export const enum EQSQueryType {
    Away = "away", // DO NOT use this yet, there will be some changes
    Cover = "cover",
    Hidden = "hidden",
    Patrol = "patrol",
    Strafe = "strafe",
    CloseStrafe = "closeStrafe",
    BattleZone = "battleZone",
}

/**
 * Environment query arguments.
 *
 * Some environment query need some of these arguments.
 * @see {@link EQSQueryType} for which environment query needs which arguments.
 */
export const enum EQSArgument {
    Origin = "Origin",
    GridSize = "GridSize",
    SpaceBetween = "SpaceBetween",
    TargetHash = "TargetHash",
    TargetLastKnownLocation = "TargetLastKnownLocation",
    TargetPredictedLocation = "TargetPredictedLocation",
    MinDistanceToTarget = "MinDistanceToTarget",
    MaxDistanceToTarget = "MaxDistanceToTarget",
    LastHitLocation = "LastHitLocation",
}

/**
 * Possible environment query statuses.
 */
export const enum EnvironmentQueryStatus {
    /** The environment query is ready to run. */
    Ready,
    /** The environment query is being processed. */
    Processing,
    /** The environment query executed and finished successfully. */
    Success,
    /** The environment query failed. */
    Failed,
}

/**
 * Available damage types.
 */
export const enum DamageType {
    Default,
    /** Does extra damage to shields */
    Energy,
    Explosive,
}

export const enum MovementMode {
    /** Walking movement mode. */
    Walk = "Walk",
    /** Sprint movement mode. */
    Sprint = "Sprint",
}

/**
 * Possible movement result.
 */
export const enum MovementResult {
    /** AI is currently moving to the destination. */
    Moving,
    /** AI reached the destination. */
    Success,
    /** AI got blocked. */
    Blocked,
    /** AI is off-path. */
    OffPath,
    /** Movement got aborted. */
    Aborted,
    /** Movement request is invalid. */
    Invalid,
}

/**
 * Actions that can be performed by AI.
 */
export const enum Action {
    LookAt = "Action.LookAt",
    Wait = "Action.Wait",
    MeleeAttack = "Action.MeleeAttack", // NOTE: Not currently supported in Unreal-side. Internal script usage only.
    SpecialAttack = "Action.SpecialAttack",
    Taunt = "Action.Taunt",
}

/**
 * All the user actions that may be available to the AI.
 */
export const enum UserAction {
    Overcharge = "UserAction.Overcharge",
    Repair = "UserAction.Repair",
}

/**
 * Possible action status
 */
export const enum Status {
    /** Action is currently running. */
    Running,
    /** Action has finished executing. */
    Finished,
    /** Action failed. */
    Failed,
    // TODO: Support Cancelled?
}

/**
 * Available sound type given to AI on sound perception event.
 */
export const enum SoundType {
    Weapon = "Weapon",
    Taunt = "Taunt",
    Nuke = "Nuke",
    HealCrate = "Pickup.Heal",
    ShieldCrate = "Pickup.Shield",
    AmmoCrate = "Pickup.Ammo",
}

/**
 * Available interactable tags.
 */
export const enum InteractableTag {
    HealCrate = "Pickup.Heal",
    ShieldCrate = "Pickup.Shield",
    AmmoCrate = "Pickup.Ammo",
}

// TODO: implementation
/**
 * Not supported yet. Do not use it.
 */
export const enum Signal {
    Help = "Signal.Help",
}
