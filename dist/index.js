import CDTModule from './cdt.js';

// Pre-initialize the module
const CDTModulePromise = CDTModule();

// Export a promise that resolves to the module
export default CDTModulePromise;

// Also export a pre-initialized version for convenience
export const CDT = await CDTModulePromise;
export const Triangulation = CDT.Triangulation;
export const VertexInsertionOrder = CDT.VertexInsertionOrder;
export const IntersectingConstraintEdges = CDT.IntersectingConstraintEdges;
export const extractEdgesFromTriangles = CDT.extractEdgesFromTriangles;