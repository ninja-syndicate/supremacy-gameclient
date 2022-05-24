/// <reference path="../typings/types.d.ts" />

const AI: Mech = Context.GetOwner();

Context.OnMessage = (name, message) => {
     switch (name) {
          case "onTick":
               onTick(JSON.parse(message));
               break;
     }
}

const onTick = (input: BrainInput) => {
     AI.MoveTo(input.self.location.X + Math.floor(Math.random() * 5000), input.self.location.Y + Math.floor(Math.random() * 5000));


     if (input.perception.sight.length > 0) {
          const target = input.perception.sight[0].target!;
          console.log(`${target.location.X} ${target.location.Y}`);
     }

     //console.log(`${input.self.hash}: ${input.self.location.X} ${input.self.location.Y}`)
}
