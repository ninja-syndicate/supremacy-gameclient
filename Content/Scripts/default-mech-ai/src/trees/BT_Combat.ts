
import {FAILURE, Parallel, Selector, Sequence, SUCCESS, Task} from 'behaviortree'
import {BTT_Focus, BTT_StopFocus} from "../tasks/BTT_Focus"
import {IsSet} from "../decorators/IsSet"
import {AIBlackboard} from "../blackboard"
import { BTT_SpecialAttack } from '../tasks/BTT_SpecialAttack';
import {AlwaysSucceedDecorator} from 'behaviortree/lib/decorators';

export const BT_Combat = new Selector({
    nodes: [
        new Sequence({
            nodes: [
                // Can See Target
                new Task({
                    run: (blackboard: AIBlackboard) => blackboard.canSeeTarget ? SUCCESS : FAILURE
                }),
                BTT_Focus("target"),
                new Parallel({
                    nodes: [
                        BTT_Shoot(WeaponTag.LeftArmWeapon),
                        BTT_Shoot(WeaponTag.RightArmWeapon)
                    ]
                }),
                BTT_SpecialAttack("targetLastKnownLocation"),
            ]
        }),
    ],
});