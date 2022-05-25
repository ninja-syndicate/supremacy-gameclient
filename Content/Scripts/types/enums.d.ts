export const enum WeaponTag {
    All,
    Primary,
    PrimaryLeftArm,
    PrimaryRightArm,
    Secondary,
    Melee,
    Flamethrower,
    Arced,
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