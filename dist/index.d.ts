import type { Point, Edge, Triangle, Triangulation, VertexInsertionOrder, IntersectingConstraintEdges } from './cdt';

// Export the module's Promise
declare const CDTModulePromise: Promise<{
  Triangulation: typeof Triangulation;
  VertexInsertionOrder: typeof VertexInsertionOrder;
  IntersectingConstraintEdges: typeof IntersectingConstraintEdges;
  extractEdgesFromTriangles: (triangles: Triangle[]) => Edge[];
}>;

export default CDTModulePromise;

// Export pre-initialized components
export declare const CDT: {
  Triangulation: typeof Triangulation;
  VertexInsertionOrder: typeof VertexInsertionOrder;
  IntersectingConstraintEdges: typeof IntersectingConstraintEdges;
  extractEdgesFromTriangles: (triangles: Triangle[]) => Edge[];
};

export declare const Triangulation: typeof Triangulation;
export declare const VertexInsertionOrder: typeof VertexInsertionOrder;
export declare const IntersectingConstraintEdges: typeof IntersectingConstraintEdges;
export declare const extractEdgesFromTriangles: (triangles: Triangle[]) => Edge[];

// Re-export the types
export type { Point, Edge, Triangle };