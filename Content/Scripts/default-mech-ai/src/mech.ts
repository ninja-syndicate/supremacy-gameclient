import {WeaponTag} from "enums";
import {WarMachine, BrainInput, AIController, JavascriptContext} from "types";

declare var Context : JavascriptContext;
const AI: AIController = Context.GetOwner();

Context.OnMessage = (name, message) => {
     switch (name) {
          case "onTick":
               onTick(JSON.parse(message));
               break;
          case "onBegin":
               onBegin(JSON.parse(message));
               break;
     }
}

let Target: WarMachine | null = null;
let TargetVisible = false;

const onBegin = (input: BrainInput) => {
     console.log(`${input.self.name} AI Started`);
}

const onTick = (input: BrainInput) => {
     if (input.errors.length !== 0) {
          input.errors.forEach(e => console.log(`${e.severity}: ${e.command}: ${e.message}`));
     }

     TargetVisible = Target !== null && input.perception.sight.findIndex(m => m.hash == Target.hash) !== -1;
     if (!TargetVisible) {
          // Find Target
          if (input.perception.sight.length > 0) {
               Target = input.perception.sight[0];
               TargetVisible = true;
          }
     }

     //AI.MoveTo(input.self.location.X + Math.floor(Math.random() * 5000), input.self.location.Y + Math.floor(Math.random() * 5000));

     // TODO: Weapon LOS check
     if (TargetVisible) {
          AI.FocusHash(Target.hash);
          AI.WeaponTrigger(WeaponTag.Primary)
     } else {
          AI.ClearFocus();
          AI.WeaponRelease();
     }
}