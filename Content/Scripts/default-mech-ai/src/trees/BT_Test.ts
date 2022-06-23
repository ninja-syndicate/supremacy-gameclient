import { Parallel, Selector } from "behaviortree"
import { WeaponTag } from "../../../types/enums"
import { ParallelBackground } from "../branches/ParallelBackground"
import { ForceSuccess } from "../decorators/ForceSuccess"
import { BTT_LogString } from "../tasks/BTT_LogString"
import { BTT_Shoot } from "../tasks/BTT_Shoot"

/**
 *
 */
export const BT_Test = new ParallelBackground({
    nodes: [
        new Parallel({
            // nodes: [BTT_LogString("Parallel background main - parallel 1"), BTT_LogString("Parallel background main - parallel 2")],
            nodes: [BTT_LogString("before"), BTT_Shoot(WeaponTag.PrimaryLeftArm)],
        }),
        new Parallel({
            nodes: [
                new Selector({
                    nodes: [BTT_LogString("sub-parallell background main selector")],
                }),
                ForceSuccess(
                    new Selector({
                        nodes: [BTT_LogString("sub-paralell background sub"), BTT_LogString("sub-parallel background sub2")],
                    }),
                ),
            ],
        }),
    ],
})

/*
ew Selector({
                    nodes: [
                        // Predicate(BT_GetCover, HasVeryLowTotalHealth, true, ObserverAborts.Both),
                        /*
                        Predicate(
                            // TODO: This should ideally be getting closer, not directly to target.
                            BTT_MoveTo("targetLastKnownLocation"),
                            (blackboard: AIBlackboard) => !TargetHasMoreTotalHealth(blackboard) || OutnumberingEnemies(blackboard),
                            true,
                            ObserverAborts.Both,
                        ),
                        BT_Strafe,
                    ],
                }),
                ForceSuccess(
                    new Selector({
                        nodes: [BTT_SetFocalPoint("target"), BTT_SetFocalPoint("targetLastKnownLocation")],
                    }),
                ),

*/
