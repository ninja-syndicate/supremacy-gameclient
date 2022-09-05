import { ObserverAborts, ParallelSelector, Selector, Sequence } from "behaviortree"
import { ParallelBackground } from "@branches/ParallelBackground"
import { BTT_LogString } from "@tasks/debug/BTT_LogString"
import { Predicate } from "@decorators/Predicate"

export const BT_ParallelTest = new ParallelBackground({
    nodes: [
        new ParallelSelector({
            nodes: [BTT_LogString("main1"), BTT_LogString("main2")],
        }),

        // Background tasks:
        BTT_LogString("background1"),
        BTT_LogString("background2"),
        new Selector({
            nodes: [
                Predicate(BTT_LogString("paralell selector predicate"), (blackboard) => blackboard.canSeeTarget, true, ObserverAborts.LowerPriority),
                new Selector({
                    nodes: [
                        BTT_LogString("background sub selector 3-1"),
                        BTT_LogString("background sub selector 3-2"),
                    ]
                }),
                BTT_LogString("background3-1"),
                BTT_LogString("background3-2"),
            ],
        }),
    ],
})

export const BT_SelectorTest = new Selector({
    nodes: [
        Predicate(BTT_LogString("selector test predicate"), (blackboard) => blackboard.canSeeTarget, true, ObserverAborts.LowerPriority),
        new Selector({
            nodes: [
                Predicate(BTT_LogString("sub Selector test predicate"), (blackboard) => blackboard.canSeeTarget, true, ObserverAborts.LowerPriority),
                BTT_LogString("sub Selector 1"),
                BTT_LogString("sub Selector 2"),
            ],
        }),
        BTT_LogString("Selector 1"),
        BTT_LogString("Selector 2"),
    ],
})

export const BT_SequenceTest = new Sequence({
    nodes: [
        Predicate(BTT_LogString("sequence test predicate"), (blackboard) => blackboard.canSeeTarget, true, ObserverAborts.LowerPriority),
        new Sequence({
            nodes: [
                Predicate(BTT_LogString("sub sequence test predicate"), (blackboard) => blackboard.canSeeTarget, true, ObserverAborts.LowerPriority),
                BTT_LogString("sub Sequence 1"),
                BTT_LogString("sub Sequence 2"),
            ],
        }),
        BTT_LogString("Sequence 1"),
        BTT_LogString("Sequence 2"),
    ],
})
