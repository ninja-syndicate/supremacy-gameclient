import { Vector, WarMachine } from "types"

export function isDead(mech: WarMachine): boolean {
    return mech.health <= 0.0
}

// NOTE:
// For testing, to be removed when we get vector library.
export function distanceTo(thisMech: WarMachine, otherMech: WarMachine): number {
    return distanceToVec(thisMech.location, otherMech.location)
}

export function distanceToVec(v1: Vector, v2: Vector) {
    const { X: x1, Y: y1, Z: z1 }: Vector = v1
    const { X: x2, Y: y2, Z: z2 }: Vector = v2

    const diff: Vector = { X: x2 - x1, Y: y2 - y1, Z: z2 - z1 }
    return Math.sqrt(diff.X ** 2 + diff.Y ** 2 + diff.Z ** 2)
}

export function add(v1: Vector, v2: Vector): Vector {
    const { X: x1, Y: y1, Z: z1 }: Vector = v1
    const { X: x2, Y: y2, Z: z2 }: Vector = v2

    return { X: x1 + x2, Y: y1 + y2, Z: z1 + z2 }
}

export function multiply(v1: Vector, scalar: number): Vector {
    const { X: x1, Y: y1, Z: z1 }: Vector = v1

    return { X: x1 * scalar, Y: y1 * scalar, Z: z1 * scalar }
}
