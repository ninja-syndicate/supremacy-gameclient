import {EnvironmentQueryStatus, EQSQueryType, WeaponTag} from "enums";
import {WarMachine, BrainInput, AIController, JavascriptContext, EnvironmentQuery} from "types";
import {StringToEQSQueryType} from "./utils";

declare var Context: JavascriptContext;
const AI: AIController = Context.GetOwner();

Context.OnMessage = (name, message) => {
    try {
        switch (name) {
            case "onTick":
                onTick(JSON.parse(message));
                break;
            case "onBegin":
                onBegin(JSON.parse(message));
                break;
        }
    } catch (e) {
        console.log(e);
    }
}

let target: WarMachine | null = null;
let targetVisible = false;

const eqsCallbacks: {
    patrol?: (query: EnvironmentQuery) => void
} = {}

const onBegin = (input: BrainInput) => {
    console.log(`${input.self.name} AI Started`);
}

const onTick = (input: BrainInput) => {
    // Check errors
    if (input.errors.length !== 0) {
        input.errors.forEach(e => console.log(`${e.severity}: ${e.command}: ${e.message}`));
    }

    targetVisible = target !== null && input.perception.sight.findIndex(m => m.hash == target.hash) !== -1;
    if (!targetVisible) {
        // Find Target
        if (input.perception.sight.length > 0) {
            target = input.perception.sight[0];
            targetVisible = true;
        } else {
            // Patrol
            if (input.eqs.patrol.status === EnvironmentQueryStatus.Ready && input.self.velocity.X === 0 && input.self.velocity.Y === 0) {
                eqsCallbacks.patrol = (query: EnvironmentQuery) => AI.MoveTo(query.location.X, query.location.Y);
                AI.EQS_Query(EQSQueryType.Patrol);
            }
        }
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
        AI.WeaponTrigger(WeaponTag.Primary)
    } else {
        AI.ClearFocus();
        AI.WeaponRelease();
    }
}

