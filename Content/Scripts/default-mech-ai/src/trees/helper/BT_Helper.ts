import { BTT_Failure } from "@tasks/BTT_Failure"
import { BTT_Success } from "@tasks/BTT_Success"
import { NodeOrRegistration, Selector, Sequence } from "behaviortree"

export const ForceSuccess = (node: NodeOrRegistration) => new Selector({ nodes: [node, BTT_Success] })
export const ForceFailure = (node: NodeOrRegistration) => new Sequence({ nodes: [node, BTT_Failure] })
