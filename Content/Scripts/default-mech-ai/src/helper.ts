import {WarMachine} from "types";

export function isDead(mech: WarMachine): boolean {
    return mech.health <= 0.0;
}

// export function distanceTo(this)