declare class Mech {
     MoveTo(x: number, y: number): void;
}

declare class Context {
     static GetOwner(): Mech;
     static OnMessage(name: string, message: string);
}

interface IntVector {
     X: number;
     Y: number;
     Z: number;
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

interface WarMachine {
     hash: string;
     location: IntVector;
     rotation: number;
     factionID: string;
     name: string;
     model: string;
     health: number;
     healthMax: number;
     shield: number;
     shieldMax: number;
}

interface AbilityInfo {
     type: AbilityID;
     location: IntVector;
}

declare enum SightType {
     WarMachine,
     Ability,
}

interface PerceptionSight {
     type: SightType;
     target?: WarMachine;
     ability?: AbilityInfo;
}

interface Perception {
     // Everything the mech can currently see
     sight: PerceptionSight[];
}

interface BrainInput {
     self: WarMachine;
     perception: Perception;
}