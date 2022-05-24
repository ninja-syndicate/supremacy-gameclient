// The AI Controller, containing all the available commands a Mech can be given
declare class AIController {
     // Move to the following location. Will automatically path find.
     MoveTo(x: number, y: number): void;

     /**
      * Aim at a target. The mech will continously aim towards this target until it loses sight or focus is cleared with {@link ClearFocus}
      * @param hash The hash of the target (Mech or damageable AI like as Robot Dogs). Get hashes and other details from {@link BrainInput.perception}
      */
     FocusHash(hash: string): void;
     // Stop aiming at the current target.
     ClearFocus(): void;

     // Starts firing all weapons that match the supplied tag, defaults to All Weapons
     WeaponTrigger(tag?: WeaponTag): void;
     // Stops firing all weapons that match the supplied tag, defaults to All Weapons
     WeaponRelease(tag?: WeaponTag): void;
}

declare class Context {
     static GetOwner(): AIController;
     static OnMessage(name: string, message: string);
}

interface IntVector {
     X: number;
     Y: number;
     Z: number;
}

interface ScriptError {
     // Which function from {@link AIController} the error/warning is from
     command: string;
     severity: "error" | "warning";
     message: string;
}

declare enum AbilityID {
     Airstrike,
     Nuke,
     Heal,
     RobotDogs,
     RedMountainReinforcement,
     SatelliteOverload,
     LowerTile,
     Fireworks,
     MoveCommand,
     CancelMoveCommand,
     ShieldBuff,
     Landmines,
     EMP,
     HackerDrone,
     CameraDrone,
     Incognito,
     Blackout,
     Ammo,
}

declare enum WeaponTag {
     All,
     Primary,
     PrimaryLeftArm,
     PrimaryRightArm,
     Secondary,
     Melee,
     Flamethrower,
     Arced,
}

interface WarMachine {
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
}

interface AbilityInfo {
     type: AbilityID;
     location: IntVector;
}

// Everything the mech can currently perceive
interface Perception {
     // Everything the mech can currently see
     sight: WarMachine[];
}

// The input provided to {@link onTick}
interface BrainInput {
     self: WarMachine;
     perception: Perception;
     errors: ScriptError[];
}