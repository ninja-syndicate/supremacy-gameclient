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

export const enum EQSQueryType {
    Away= "away",
    Cover = "cover",
    Hidden = "hidden",
    Patrol = "patrol",
    Strafe = "strafe",
}

export const enum EQSArgument {
    TargetHash = "TargetHash",
    TargetLastKnownLocation = "TargetLastKnownLocation",
    TargetPredictedLocation = "TargetPredictedLocation",
    LastHitLocation = "LastHitLocation"
}

export const enum EnvironmentQueryStatus {
    Ready,
    Processing,
    Success,
    Failed,
}

export const enum DamageType {
    Default,
    /** Does extra damage to shields */
    Energy,
    Explosive,
}

export const enum MovementResult {
    Moving,
    Success,
    Blocked,
    OffPath,
    Aborted,
    Invalid
}

export const enum Action {
    LookAt = "Action.LookAt",
    Wait = "Action.Wait"
}

export const enum Ability {
    Taunt = "Ability.Taunt",
    MeleeAttack = "Ability.MeleeAttack",
    SpecialAttack = "Ability.SpecialAttack",
}

export const enum Status {
    Running,
    Finished,
    Failed
}

export const enum SoundType {
    Weapon = "Weapon",
    Taunt = "Taunt",
    Nuke = "Nuke",
    // Might just give tag Pickup and use sight to figure out the type.
    HealCrate = "Pickup.Heal",
    ShieldCrate = "Pickup.Shield",
    AmmoCrate = "Pickup.Ammo"
}

export const enum Signal {
    Help = "Signal.Help",
}