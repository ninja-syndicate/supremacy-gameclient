/// <reference path="../typings/types.d.ts" />

const AI: AIController = Context.GetOwner();

Context.OnMessage = (name, message) => {
     switch (name) {
          case "onTick":
               onTick(JSON.parse(message));
               break;
     }
}

let Target: WarMachine | null = null;

const onTick = (input: BrainInput) => {
     if (input.errors.length !== 0) {
          input.errors.forEach(e => console.log(`${e.severity}: ${e.command}: ${e.message}`));
     }

     if (input.perception.sight.length > 0) {
          if (Target === null) {
               Target = input.perception.sight[0];
          }
     }

     //AI.MoveTo(input.self.location.X + Math.floor(Math.random() * 5000), input.self.location.Y + Math.floor(Math.random() * 5000));

     // TODO: Weapon LOS check
     if (Target !== null) {
          AI.FocusHash(Target.hash);
          AI.WeaponTrigger()
     } else {
          AI.ClearFocus();
          AI.WeaponRelease();
     }

     //console.log(`${input.self.hash}: ${input.self.location.X} ${input.self.location.Y}`)
}