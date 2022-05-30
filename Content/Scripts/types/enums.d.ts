export const enum WeaponTag {
    All = "Weapon",
    Primary = "Weapon.Primary",
    PrimaryLeftArm = "Weapon.Primary.LeftArm",
    PrimaryRightArm = "Weapon.Primary.RightWeapon",
    Secondary = "Weapon.Secondary",
    Melee = "Weapon.Melee",
    Flamethrower = "Weapon.Flamethrower",
    Arced = "Weapon.Arced",
}

export const enum EQSQueryType {
    Away,
    Cover,
    Hidden,
    Patrol,
    Strafe,
}

export const enum EQSArgument {
    TargetHash,
    TargetLastKnownLocation,
    LastHitLocation
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