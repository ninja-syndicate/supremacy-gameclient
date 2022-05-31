import {EnvironmentQueryStatus} from "enums";
import {WarMachine} from "types";
import {BrainInput} from "types";
import {StringToEQSQueryType} from "./utils";
import {AI} from "./index";
import {BT_Root} from "./trees/BT_Root";
import {BehaviorTree} from "behaviortree";
import {AIBlackboard} from "./blackboard";

export let tree = new BehaviorTree({
    tree: BT_Root,
    blackboard: {
        eqsResults: {},
    } as AIBlackboard,
})

let target: WarMachine | null = null;
let targetVisible = false;

export const onBegin = (input: BrainInput) => {
    console.log(`${input.self.name} AI Started`);
}

export const onTick = (input: BrainInput) => {
    const bb = tree.blackboard as AIBlackboard;
    // Check errors
    if (input.errors.length !== 0) {
        input.errors.forEach(e => console.log(`${e.severity}: ${e.command}: ${e.message}`));
    }

    // Perception
    const targetVisIndex = target === null ? -1 : input.perception.sight.findIndex(m => m.hash == target.hash);
    targetVisible = target !== null && targetVisIndex !== -1;
    if (!targetVisible) {
        // Find Target
        if (input.perception.sight.length > 0) {
            target = input.perception.sight[0];
            bb.targetHash = target.hash;
            targetVisible = true;
        }
    }

    // Update Target
    if (targetVisIndex !== -1) {
        target = input.perception.sight[targetVisIndex];
        bb.targetLastKnownLocation = target.location;
        bb.canSeeTarget = targetVisible;
    }

    // if (input.perception.damage.length > 0) {
    //     console.log(JSON.stringify(input.perception.damage[0]));
    // }

    // Run Behaviour Tree
    tree.step();

    // EQS - Run callbacks when they succeed
    for (let [key, value] of Object.entries(input.eqs)) {
        if (value.status === EnvironmentQueryStatus.Success) {
            bb.eqsResults[key] = value;
            AI.EQS_Complete(StringToEQSQueryType(key));
        }
    }

    // TODO: Weapon LOS check
    // if (targetVisible) {
    //     AI.FocusHash(target.hash);
    //     AI.WeaponTrigger(WeaponTag.Primary, target.location)
    // } else {
    //     AI.ClearFocus();
    //     AI.WeaponRelease(WeaponTag.Primary);
    // }
}

