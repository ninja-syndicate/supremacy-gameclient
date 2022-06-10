
import {FAILURE, Parallel, ParallelComplete, ParallelSelector, Selector, Sequence, SUCCESS, Task} from 'behaviortree'
import {ParallelImmediate} from "../branches/ParallelImmediate";
import {BTT_SetFocalPoint, BTT_StopFocus} from "../tasks/BTT_SetFocalPoint"
import {IsSet} from "../decorators/IsSet"
import {AIBlackboard} from "../blackboard"
import {Ability, EQSArgument, EQSQueryType, WeaponTag} from "../../../types/enums";
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
import { BTT_RunEQSQuery } from '../tasks/BTT_RunEQSQuery';
import { AlwaysFail } from "../decorators/AlwaysFailDecorator";
import { BTT_EQSSetArgumentString } from '../tasks/BTT_EQSSetArgument';
import { blackboard } from "../mech";

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

export const BT_RangeCombat = new Sequence({
    nodes: [
        // BTT_Shoot(WeaponTag.PrimaryLeftArm)
        /*
        BTT_SetFocalPoint("target"),
        new ParallelBackground({
            nodes: [
                // TODO: should be parallel selector, but can't use it right now...
                new Parallel({
                    nodes: [
                        new Selector({nodes: [IsSet(BTT_Shoot(WeaponTag.PrimaryLeftArm), "canSeeTarget"), BTT_ReleaseWeapon(WeaponTag.PrimaryLeftArm)] }),
                        new Selector({nodes: [IsSet(BTT_Shoot(WeaponTag.PrimaryRightArm), "canSeeTarget"), BTT_ReleaseWeapon(WeaponTag.PrimaryRightArm)] })
                    ]
                })
            ]
        })
        */
        new Sequence({
            nodes: [
                BTT_EQSSetArgumentString(EQSQueryType.Strafe, EQSArgument.TargetHash, blackboard.target.hash),
                BTT_RunEQSQuery(EQSQueryType.Strafe, "strafeLocation"),
                BTT_MoveTo("strafeLocation")
            ]
        })
    ]
});

const BT_SearchPredictedLocation = new ParallelBackground({
    nodes: [
        BTT_MoveTo("targetPredictedLocation"),
        BTT_SetFocalPoint("targetPredictedLocation")
    ]
});

const BT_CanSeeTarget = new Selector({
    nodes: [
        // BTT_SpecialAttack("targetLastKnownLocation"),
        /*
        new Selector({ 
            nodes: [
                CanActivateAbility(BT_MeleeCombat, Ability.MeleeAttack), 
                BTT_ReleaseWeapon(WeaponTag.Melee) 
            ]
        }),
        */
        BT_RangeCombat
    ]
});

export const BT_Combat = new Selector({
    nodes: [
        // BT_SearchPredictedLocation,
        IsSet(BT_CanSeeTarget, "canSeeTarget"),
        // IsSet(BT_SearchPredictedLocation, "canSeeTarget", false)

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