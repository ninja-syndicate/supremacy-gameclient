import {EnvironmentQueryStatus, EQSQueryType, WeaponTag} from "enums";
import {WarMachine, Weapon, BrainInput, EnvironmentQuery} from "types";
import {StringToEQSQueryType} from "./utils";
import {AI} from "./index";

let target: WarMachine | null = null;
let targetVisible = false;

const eqsCallbacks: {
    patrol?: (query: EnvironmentQuery) => void
} = {}

export const onBegin = (input: BrainInput) => {
    console.log(`${input.self.name} AI Started`);
}

export const onTick = (input: BrainInput) => {
    // Check errors
    if (input.errors.length !== 0) {
        input.errors.forEach(e => console.log(`${e.severity}: ${e.command}: ${e.message}`));
    }

    const targetVisIndex = target === null ? -1 : input.perception.sight.findIndex(m => m.hash == target.hash);
    targetVisible = target !== null && targetVisIndex !== -1;
    if (!targetVisible) {
        // Find Target
        if (input.perception.sight.length > 0) {
            target = input.perception.sight[0];
            targetVisible = true;
        } else {
            // Patrol
            if (!input.eqs.patrol && input.self.velocity.X === 0 && input.self.velocity.Y === 0) {
                eqsCallbacks.patrol = (query: EnvironmentQuery) => AI.MoveToVector(query.location);
                AI.EQS_Query(EQSQueryType.Patrol);
            }
        }
    } else {
        // Update Target
        if (targetVisIndex !== -1)
            target = input.perception.sight[targetVisIndex];
    }

    // EQS - Run callbacks when they succeed
    for (let [key, value] of Object.entries(input.eqs)) {
        if (value.status === EnvironmentQueryStatus.Success && !!eqsCallbacks[key]) {
            eqsCallbacks[key](value);
            AI.EQS_Complete(StringToEQSQueryType(key));
        }
    }

    // if (Target !== null) {
    //     AI.EQS_SetArgumentString(EQSArgument.TargetHash, Target.hash);
    //     AI.EQS_SetArgumentVector(EQSArgument.TargetLastKnownLocation, Target.location);
    // }

    // TODO: Weapon LOS check
    if (targetVisible) {
        AI.FocusHash(target.hash);
        AI.WeaponTrigger(WeaponTag.Primary, target.location)
    } else {
        AI.ClearFocus();
        AI.WeaponRelease();
    }
}

