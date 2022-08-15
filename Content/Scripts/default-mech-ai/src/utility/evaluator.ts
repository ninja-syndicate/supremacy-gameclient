import { Test } from "@utility/Test"

export class Evaluator<T> {
    items: T[]
    tests: Test<T>[]

    constructor(items?: T[], tests?: Test<T>[]) {
        this.items = items !== undefined ? items : []
        this.tests = tests !== undefined ? tests : []
    }

    addItem(item: T): Evaluator<T> {
        this.items.push(item)
        return this
    }

    addItems(items: T[]): Evaluator<T> {
        this.items.push(...items)
        return this
    }

    addTest(test: Test<T>): Evaluator<T> {
        this.tests.push(test)
        return this
    }

    getBestItem(): T {
        const scores: number[] = this.run()
        const bestScoreIdx: number = scores.indexOf(Math.max(...scores))
        return bestScoreIdx !== -1 ? this.items[bestScoreIdx] : undefined
    }

    private run(): number[] {
        return this.items.map((i) => this.tests.map((test) => test.getScore(i)).reduce((a, b) => a + b))
    }
}
