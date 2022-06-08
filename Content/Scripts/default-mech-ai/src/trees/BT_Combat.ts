
import {FAILURE, Parallel, Selector, Sequence, SUCCESS, Task} from 'behaviortree'
import {BTT_Focus, BTT_StopFocus} from "../tasks/BTT_Focus"
import {IsSet} from "../decorators/IsSet"
import {AIBlackboard} from "../blackboard"
import {Ability, WeaponTag} from "../../../types/enums";
import {BTT_SpecialAttack} from '../tasks/BTT_SpecialAttack';
import {BTT_Shoot} from "../tasks/BTT_Shoot";
import {CanActivateAbility} from "../decorators/CanActivateAbility";
import { AI } from '..';
import {BTT_MoveTo} from "../tasks/BTT_MoveTo";
import {BTT_MeleeAttack} from "../tasks/BTT_MeleeAttack";
import {BTT_ReleaseWeapon} from "../tasks/BTT_ReleaseWeapon";
import {BTT_TriggerWeapon} from '../tasks/BTT_TriggerWeapon';

export const BT_MeleeCombat = new Selector({
    nodes: [
        new Parallel({
            nodes: [
                new Sequence({
                    nodes: [
                        BTT_TriggerWeapon(WeaponTag.Melee)
                    ]
                }),
                new Sequence({
                    nodes: [
                        BTT_Focus("target"),
                        BTT_MoveTo("targetLastKnownLocation")
                    ]
                })
            ]
        }),
        BTT_ReleaseWeapon(WeaponTag.Melee)
    ]}
);

export const BT_Shoot = new Sequence({
    nodes: [
        BTT_Focus("target"),
        new Parallel({
            nodes: [
                new Selector({ nodes: [
                    IsSet(BTT_Shoot(WeaponTag.PrimaryLeftArm), "canSeeTarget"),
                    BTT_ReleaseWeapon(WeaponTag.PrimaryLeftArm)
                ]}),
                new Selector({ nodes: [
                    IsSet(BTT_Shoot(WeaponTag.PrimaryRightArm), "canSeeTarget"), 
                    BTT_ReleaseWeapon(WeaponTag.PrimaryRightArm)
                ]})
            ]
        })
    ]
});

const BT_CanSeeTarget = new Selector({
    nodes: [
        new Selector({ nodes: [CanActivateAbility(BT_MeleeCombat, Ability.MeleeAttack), BTT_ReleaseWeapon(WeaponTag.Melee) ] })
        //CanActivateAbility(BTT_SpecialAttack("targetLastKnownLocation"), Ability.SpecialAttack),
        //BT_Shoot
    ]
});

export const BT_Combat = new Selector({
    nodes: [
        new Sequence({
            nodes: [
                // Can See Target
                new Task({
                    run: (blackboard: AIBlackboard) => blackboard.canSeeTarget ? SUCCESS : FAILURE
                }),
                BT_CanSeeTarget
            ]
        }),
    ],
});