import {IntVector, WarMachine} from "types";

export function isDead(mech: WarMachine): boolean {
    return mech.health <= 0.0;
}

export function distanceTo(thisMech: WarMachine, otherMech: WarMachine): number {
    const {X: x1, Y: y1, Z: z1}: IntVector = thisMech.location;
    const {X: x2, Y: y2, Z: z2}: IntVector = otherMech.location;

    const diff: IntVector = {X: x2 - x1, Y: y2 - y1, Z: z2 - z1};
    return Math.sqrt(diff.X ** 2 + diff.Y ** 2 + diff.Z ** 2);
}