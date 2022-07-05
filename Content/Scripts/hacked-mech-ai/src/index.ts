import { AIController, JavascriptContext } from "types"
import { onBegin, onTick } from "./mech"

declare var Context: JavascriptContext
export const AI: AIController = Context.GetOwner()

// Listen to incoming messages from the game
Context.OnMessage = (name, message) => {
    try {
        switch (name) {
            case "onTick":
                onTick(JSON.parse(message))
                break
            case "onBegin":
                onBegin(JSON.parse(message))
                break
        }
    } catch (e) {
        console.log(e)
    }
}