import { AIBlackboard } from "@blackboards/blackboard"
import { Weapon } from "types"
import { WeaponTag } from "enums"

const Predicate_HasAmmoByTagAux = (weapons: Weapon[], weaponTags: WeaponTag[], currentIdx: number = 0): Weapon[] => {
    if (weapons.length === 0) return []
    if (currentIdx >= weaponTags.length) return weapons

    const currentWeaponTag: WeaponTag = weaponTags[currentIdx]
    const filteredWeapons = weapons.filter((w) => w.Tags.find((t) => t === currentWeaponTag))
    return Predicate_HasAmmoByTagAux(filteredWeapons, weaponTags, currentIdx + 1)
}

export const Predicate_HasAmmoByHash =
    (weaponHash: string) =>
    (blackboard: AIBlackboard): boolean => {
        const weaponIdx: number = blackboard.input.Self.Weapons.findIndex((w) => w.Hash === weaponHash)
        return weaponIdx !== -1 && blackboard.input.Self.Weapons[weaponIdx].CurrentAmmo > 0
    }

export const Predicate_HasAmmoByTag =
    (...weaponTags: WeaponTag[]) =>
    (blackboard: AIBlackboard): boolean => {
        const filteredWeapons = Predicate_HasAmmoByTagAux(blackboard.input.Self.Weapons, weaponTags)
        const totalAmmoCount: number = filteredWeapons.map((w) => w.CurrentAmmo).reduce((a, b) => a + b, 0)
        return totalAmmoCount > 0
    }
