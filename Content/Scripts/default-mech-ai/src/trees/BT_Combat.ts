
import {FAILURE, Parallel, ParallelComplete, Selector, Sequence, SUCCESS, Task} from 'behaviortree'
import {ParallelImmediate} from "../branches/ParallelImmediate";
import {BTT_SetFocalPoint, BTT_StopFocus} from "../tasks/BTT_SetFocalPoint"
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
import { ParallelBackground } from '../branches/ParallelBackground';
import { BTT_FocusDirection } from '../tasks/BTT_FocusDirection';

export const BT_MeleeCombat = new Parallel({
    nodes: [
        new Sequence({
            nodes: [
                BTT_SetFocalPoint("target"),
                BTT_MoveTo("targetLastKnownLocation")
            ]
        }),
        BTT_TriggerWeapon(WeaponTag.Melee)
    ]
});

export const BT_Shoot = new Sequence({
    nodes: [
        BTT_SetFocalPoint("target"),
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
        BTT_SpecialAttack("targetLastKnownLocation"),
        /*
        new Selector({ 
            nodes: [
                CanActivateAbility(BT_MeleeCombat, Ability.MeleeAttack), 
                BTT_ReleaseWeapon(WeaponTag.Melee) 
            ]
        }),
        */
        IsSet(BT_Shoot, "canSeeTarget")
    ]
});

export const BT_Combat = new Selector({
    nodes: [
        // IsSet(BT_CanSeeTarget, "canSeeTarget"),
        new Sequence({nodes: [BTT_FocusDirection("damageStimulusDirection")]})
        

        /*
        new Sequence({
            nodes: [
                // Can See Target
                new Task({
                    run: (blackboard: AIBlackboard) => blackboard.canSeeTarget ? SUCCESS : FAILURE
                }),
            ]
        }),
        */
    ],
});