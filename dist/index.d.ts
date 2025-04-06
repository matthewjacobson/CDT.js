declare module "cdt-js" {
  export interface Point {
    x: number;
    y: number;
  }

  export interface Edge {
    from: number;
    to: number;
  }
    
  export enum VertexInsertionOrder {
    Auto = 0,
    AsProvided = 1
  }

  export enum IntersectingConstraintEdges {
    NotAllowed = 0,
    TryResolve = 1,
    DontCheck = 2
  }

  export class Triangulation {
    constructor(vertexInsertionOrder?: VertexInsertionOrder, intersectingConstraintEdges?: IntersectingConstraintEdges, minDistToConstraintEdge?: number);
    getVertices(): Point[];
    getTriangles(): number[][];
    getFixedEdges(): Edge[];
    insertVertices(vertices: Point[]): void;
    insertEdges(edges: Edge[]): void;
    conformToEdges(edges: Edge[]): void;
    eraseSuperTriangle(): void;
    eraseOuterTriangles(): void;
    eraseOuterTrianglesAndHoles(): void;
  }

  export default function createCDTModule(): Promise<{
    Triangulation: typeof Triangulation;
    VertexInsertionOrder: typeof VertexInsertionOrder;
    IntersectingConstraintEdges: typeof IntersectingConstraintEdges;
  }>;
}
