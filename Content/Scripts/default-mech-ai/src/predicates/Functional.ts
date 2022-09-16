import { AIBlackboard } from "@blackboards/blackboard"

const AND_OP = () => true
const OR_OP = () => false

const ComposeAux = (
    blackboard: AIBlackboard,
    predicates: ((AIBlackboard) => boolean)[],
    currentIdx: number = 0,
    overallResult: boolean,
    auxOp: () => boolean,
): boolean => {
    if (currentIdx >= predicates.length) return overallResult

    // Return early to mimic short-circuit evaluation.
    const result: boolean = predicates[currentIdx](blackboard)
    if (result !== auxOp()) return !auxOp()

    return ComposeAux(blackboard, predicates, currentIdx + 1, overallResult, auxOp)
}

export const negate = (predicate: ((AIBlackboard) => boolean)): ((AIBlackboard) => boolean) => {
    return (blackboard: AIBlackboard) => !predicate(blackboard)
}

export const conjunct = (...predicates: ((AIBlackboard) => boolean)[]): ((AIBlackboard) => boolean) => {
    return (blackboard: AIBlackboard) => ComposeAux(blackboard, predicates, 0, true, AND_OP)
}

export const disjunct = (...predicates: ((AIBlackboard) => boolean)[]): ((AIBlackboard) => boolean) => {
    return (blackboard: AIBlackboard) => ComposeAux(blackboard, predicates, 0, false, OR_OP)
}