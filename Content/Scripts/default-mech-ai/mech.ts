/// <reference path="../typings/types.d.ts" />

const Owner = Context.GetOwner();
console.log(Owner); // returns [object BP_MechController_C]

Context.OnMessage = (name, message) => {
     const input = JSON.parse(message);

     Owner.MoveTo(input["location"]["X"] + Math.floor(Math.random() * 5000), input["location"]["Y"] + Math.floor(Math.random() * 5000));
     console.log(`${input["location"]["X"]} ${input["location"]["Y"]}`)
}
