import { Vector, WarMachine } from "types"

export function isDead(mech: WarMachine): boolean {
    return mech.health <= 0.0
}

// NOTE:
// For testing, to be removed when we get vector library.
export const distanceTo = (thisMech: WarMachine, otherMech: WarMachine): number => distanceToVec(thisMech.location, otherMech.location)
export const distanceToVec = (v1: Vector, v2: Vector): number => {
    const { X: x1, Y: y1, Z: z1 }: Vector = v1
    const { X: x2, Y: y2, Z: z2 }: Vector = v2

    const diff: Vector = { X: x2 - x1, Y: y2 - y1, Z: z2 - z1 }
    return Math.sqrt(diff.X ** 2 + diff.Y ** 2 + diff.Z ** 2)
}
export const add = (v1: Vector, v2: Vector): Vector => {
    const { X: x1, Y: y1, Z: z1 }: Vector = v1
    const { X: x2, Y: y2, Z: z2 }: Vector = v2

    return { X: x1 + x2, Y: y1 + y2, Z: z1 + z2 }
}
export const multiply = (v1: Vector, scalar: number): Vector => {
    const { X: x1, Y: y1, Z: z1 }: Vector = v1

    return { X: x1 * scalar, Y: y1 * scalar, Z: z1 * scalar }
}
export const rotateZ = (v1: Vector, degrees: number): Vector => {
    const radians: number = degrees * (Math.PI / 180.0)
    const { X, Y, Z } = v1

    return { X: X * Math.cos(radians) - Y * Math.sin(radians), Y: X * Math.sin(radians) + Y * Math.cos(radians), Z: Z }
}
export const fmod = (x: number, y: number): number => {
    // for tolerance testing, probably not needed in typescript
    const absY: number = Math.abs(y)

    const div: number = x / y
    const int: number = y * Math.trunc(div)
    const result: number = x - int
    return result
}
/** Gets the forward vector based on the rotation. */
export const getForwardVector = (rotation: Vector): Vector => {
    const { X: roll, Y: pitch, Z: yaw } = rotation
    const radians = (degrees) => degrees * (Math.PI / 180.0)

    // Remove winding and clamp to [-360, 360]
    const pitchNoWinding = fmod(pitch, 360.0)
    const yawNoWinding = fmod(yaw, 360.0)

    const ps = Math.sin(radians(pitchNoWinding))
    const pc = Math.cos(radians(pitchNoWinding))
    const ys = Math.sin(radians(yawNoWinding))
    const yc = Math.cos(radians(yawNoWinding))

    return { X: pc * yc, Y: pc * ys, Z: ps }
}
