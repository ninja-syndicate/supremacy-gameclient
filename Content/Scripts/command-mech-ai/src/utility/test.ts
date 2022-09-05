export class Test<T> {
    scoreFunc: (item: T) => number

    constructor(scoreFunc: (item: T) => number) {
        this.scoreFunc = scoreFunc
    }

    getScore(item: T): number {
        return this.scoreFunc(item)
    }
}