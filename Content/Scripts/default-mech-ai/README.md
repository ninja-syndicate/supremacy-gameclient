## Supremacy Scriptable AI

### Getting Started

To get started with scripting your own AI, you will need to understand how behavior tree works. You may want to read the following article to get some basic
understanding of

https://www.gamedeveloper.com/programming/behavior-trees-for-ai-how-they-work

In addition to the standard behavior tree, Observer Aborts feature is implemented.
Providing another layer to make tweaking behavior to make things easier for user is not done yet.

The main script file is mech.ts and BT_Root.

The BT prefix means BehaviorTree.
The BTT prefix means BehaviorTreeTask.

You may refer to the

blackboard

onBegin()

This is the function that will be called from

onTick()

### Setup

-   `npm install`
-   `npm run-script build` (or `npm run-script watch` if you want to build after each change)
-   Set the AI to use the compiled script file: `default-mech-ai/build/mech.js`
