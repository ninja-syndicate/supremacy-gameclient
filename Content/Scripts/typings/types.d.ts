declare class Mech {
     MoveTo(x: number, y: number): void
}

declare class Context {
     static GetOwner(): Mech;
     static OnMessage(name: string, message: string);
}