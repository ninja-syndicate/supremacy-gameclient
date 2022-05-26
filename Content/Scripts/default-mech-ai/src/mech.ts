import {EnvironmentQueryStatus, EQSArgument, EQSQueryType, WeaponTag} from "enums";
import {WarMachine, BrainInput, AIController, JavascriptContext, EnvironmentQuery} from "types";

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

let Target: WarMachine | null = null;
let TargetVisible = false;

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

    // EQS - Run callbacks when they succeed
    for (let [key, value] of Object.entries(input.eqs)) {
        if (value.status === EnvironmentQueryStatus.Success && !!eqsCallbacks[key]) {
            eqsCallbacks[key](value);
            input.eqs[key].status = EnvironmentQueryStatus.Ready;
        }
    }

    TargetVisible = Target !== null && input.perception.sight.findIndex(m => m.hash == Target.hash) !== -1;
    if (!TargetVisible) {
        // Find Target
        if (input.perception.sight.length > 0) {
            Target = input.perception.sight[0];
            TargetVisible = true;
        } else {
            // Patrol
            if (input.eqs.patrol.status === EnvironmentQueryStatus.Ready && input.self.velocity.X === 0 && input.self.velocity.Y === 0) {
                eqsCallbacks.patrol = (query: EnvironmentQuery) => AI.MoveTo(query.location.X, query.location.Y);
                AI.EQS_Query(EQSQueryType.Patrol);
                console.log("Moving to new patrol point");
            }
        }
    }

    // if (Target !== null) {
    //     AI.EQS_SetArgumentString(EQSArgument.TargetHash, Target.hash);
    //     AI.EQS_SetArgumentVector(EQSArgument.TargetLastKnownLocation, Target.location);
    // }

    // TODO: Weapon LOS check
    if (TargetVisible) {
        AI.FocusHash(Target.hash);
        AI.WeaponTrigger(WeaponTag.Primary)
    } else {
        AI.ClearFocus();
        AI.WeaponRelease();
    }
}