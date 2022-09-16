import { Predicate } from "@decorators/Predicate"
import { Predicate_CloseCombat } from "@predicates/combat/Predicate_CloseCombat"
import { Predicate_HasAmmoByTag } from "@predicates/combat/Predicate_HasAmmo"
import { BTT_MeleeAttack } from "@tasks/BTT_MeleeAttack"
import { BTT_Shoot } from "@tasks/weapon/BTT_Shoot"
import { WeaponTag } from "enums"
import { ObserverAborts, ParallelSelector, Selector } from "behaviortree"
import { ForceSuccess } from "@trees/helper/BT_Helper"
import { BTT_Running } from "@root/tasks/BTT_Running"

export const BT_PrimaryAttack = new Selector({
    nodes: [
        Predicate(BTT_MeleeAttack(WeaponTag.Melee), Predicate_CloseCombat, true, ObserverAborts.Both),
        Predicate(
            new ParallelSelector({
                nodes: [ForceSuccess(BTT_Shoot(WeaponTag.PrimaryLeftArm)), ForceSuccess(BTT_Shoot(WeaponTag.PrimaryRightArm))],
            }),
            Predicate_HasAmmoByTag(WeaponTag.Primary, WeaponTag.Shootable),
            true,
            ObserverAborts.Both,
        ),
        BTT_Running
    ],
})
