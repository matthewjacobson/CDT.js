# CDT.js

A JavaScript library for Constrained Delaunay Triangulation powered by WebAssembly.

## Installation

```bash
npm install cdt-js
```

## Usage

### ES Modules

```javascript
import CDTModule, { Point, Edge } from 'cdt-js';

CDTModule().then((CDT) => {
  const triangulation = new CDT.Triangulation();
  const vertices: Point[] = [
    { x:   0, y:   0 },
    { x: 100, y:   0 },
    { x: 100, y: 100 },
    { x:   0, y: 100 },
    { x:  50, y:  50 }
  ];
  const edges: Edge[] = [
    { from: 0, to: 1 },
    { from: 1, to: 2 },
    { from: 2, to: 3 },
    { from: 3, to: 0 },
  ];
  triangulation.insertVertices(vertices);
  triangulation.insertEdges(edges);
  triangulation.eraseOuterTrianglesAndHoles();
  const vertices = triangulation.getVertices();
  const triangles = triangulation.getTriangles();
  const fixedEdges = triangulation.getFixedEdges();
  const extractedEdges = CDT.extractEdgesFromTriangles(triangles);
  console.log(vertices);
  console.log(triangles);
  console.log(fixedEdges);
  console.log(extractedEdges);
});
```

## API

### Triangulation

Main class for triangulation operations.

#### Constructor

```javascript
new Triangulation(
  vertexInsertionOrder?: VertexInsertionOrder,
  intersectingConstraintEdges?: IntersectingConstraintEdges,
  minDistToConstraintEdge?: number
);
```

- `vertexInsertionOrder`: Strategy specifying order in which a range of vertices is inserted (default: Auto)
- `intersectingConstraintEdges`: Strategy for treating intersecting constraint edges (default: NotAllowed)
- `minDistToConstraintEdge`: Distance within which a point is considered to be lying on a constraint edge (default: 0)

#### Methods

- `insertVertices(vertices)`: Add an array of points
- `insertEdges(edges)`: Add an array of constraint edges
- `triangulate()`: Perform triangulation
- `getVertices()`: Get array of vertices
- `getEdges()`: Get array of edges
- `getTriangles()`: Get array of triangles as vertex indices

### Enums

#### VertexInsertionOrder

- `Auto`: Automatic insertion order optimized for better performance (default)
- `AsProvided`: Insert vertices in same order they are provided

#### IntersectingConstraintEdges

- `NotAllowed`: Constraint edge intersections are not allowed (default)
- `TryResolve`: Attempt to resolve constraint edge intersections
- `DontCheck`: No checks, slightly faster but less safe, user must provide a valid input without intersecting constraints

## Examples

See the [examples folder](examples/) for complete examples.

## Development

### Prerequisites

- Emscripten SDK
- Node.js and npm

### Building

```bash
npm run build
```

## License

MIT
