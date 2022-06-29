## Supremacy Scriptable AI

### Setup

Download and install the latest [Node.js](https://nodejs.org/en/download/).
Also install the latest [Git for Windows](https://git-scm.com/downloads) if you are using Windows.

Navigate to Content/Scripts/default-mech-ai folder and run the following commands:

`npm install`

You can then build it by running the following command:

`npm run-script build` (or `npm run-script watch` if you want to build after each change)

The compiled script file is located in the `default-mech-ai/build/mech.js`.

### Testing

If you are testing within Unreal Engine, you don't need to do anything after building the script. By default, the AI will use the script from
`default-mech-ai/build/mech.js`. But if you're trying to hot-swap the AI script on built gameclient, after you've built, you will need to copy the folder
`default-mech-ai` and place it relative to where gameclient binary file is located at. This is because the AI is trying to find the `mech.js` script relative to
the base directory of where gameclient is running (note that this may change in the future).

### Getting Started

To get started with scripting your own AI, you will need to first understand how behavior tree works. You may want to read the following article to get some
basic understanding of how it works: https://www.gamedeveloper.com/programming/behavior-trees-for-ai-how-they-work

While you could script your own AI without using behavior tree, we recommend that you use it over if-else based AI as it will be a lot easier to work with. Feel
free to implement finite-state machine/goal-oriented-action-planner (GOAP) or other variant AI if you want.

In addition to the standard behavior tree, Observer Aborts feature is implemented. If you have some background in Unreal Engine behavior tree, you will see a
lot of similarities. The observer aborts allow you to abort a subtree based on the condition you specify. There are four types:

-   None: Do not abort anything when the condition is not satisfied. Keeps the subtree running if it is running.
-   Self: Abort self and subtrees running under this node. Useful if you want to stop the subtree when the condition is not satisfied.
-   LowerPriority: Abort any nodes after this node (not including itself). Useful if you want to abort lower priority behaviors when the condition is satisfied.
    _Note that the scope is limited to the wrapping branch node._
-   Both: Both the self and LowerPriority combined.

These observer abort options can be used with decorators.

The AI follows Sense-Think-Act model. The AI receives information by its perception (sense), and make decisions in the behavior tree (think) and execute the
desired task (act). To make decisions, you will need to store perceived information to the memory. The `src/Blackboard.ts` is the memory and this is what our
behavior tree expects. You don't have to use this, but it is recommended to keep things organized.

A task is where you will usually give command(s) to the AI (see the list of commands you can give in `AIController` interface in `types/types.d.ts`). In a task,
you can implement start, run, end and/or abort properties to do something in its respective stages. The `start` property only gets called when the task begins,
`run` when it is running, `end` when `run` ends, `abort` if the task aborted by observer aborts. Note that `end` does not get called if the task is aborted. You
will also need to return a status in {`SUCCESS`, `RUNNING`, `FAILURE`} for `run` function to denote whether the task succeed, is running or has failed,
respectively. The status `RUNNING` is invalid for `start` function and if `start` function returns `FAILURE`, `run` and `end` functions will not run.

Finally, there's a lot of freedom on what you can do, but it can be daunting to figure out something as simple as strafe location while AI is fighting. To help
you with this, the Environment Query System is provided to allow you to query the environment to generate an optimal location for the most of the things you
will need (see `EQSQueryType` in `types/enums.d.ts` and `src/trees/BT_Strafe.ts` as an example of usage).

As a starting point, if you want to only tweak the overall behaviors of the existing AI, take a look at `src/trees/BT_Root.ts`. It contains the root behavior
tree that is run by AI. But if you want to dive straight to nitty-gritty details such as how it should behave on different perception stimulus or just want to
understand how everything works, see the main script file in `src/mech.ts` and step through each line of code, especially `onBegin` and `onTick` functions.

### Naming Convention

-   BT - BehaviorTree.
-   BTT - BehaviorTreeTask.
