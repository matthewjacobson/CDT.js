#include "CDT.h"
#include <emscripten/bind.h>

using namespace CDT;

struct CustomPoint2D {
    double x;
    double y;
    CustomPoint2D(double x, double y) : x(x), y(y) { }
};

struct CustomEdge {
    std::pair<std::size_t, std::size_t> vertices;
    CustomEdge(std::pair<std::size_t, std::size_t> vertices) : vertices(vertices) { }
};

// Expose a simple triangulation function
emscripten::val triangulate(emscripten::val pointsJS, emscripten::val edgesJS) {
    
//    int len = points["length"].as<int>();
//    float sum = 0;
//    for (int i = 0; i < len; i++) {
//        sum += points[i][1].as<float>();
//    }
//    return emscripten::val(sum);
    
    std::vector<CustomPoint2D> points;
    for (int i = 0; i < pointsJS["length"].as<int>(); ++i) {
        double x = pointsJS[i][0].as<double>();
        double y = pointsJS[i][1].as<double>();
        points.emplace_back(x, y);
    }
    
    std::vector<CustomEdge> edges;
    for (int i = 0; i < edgesJS["length"].as<int>(); ++i) {
        int v1 = edgesJS[i][0].as<int>();
        int v2 = edgesJS[i][1].as<int>();
        edges.emplace_back(std::make_pair(v1, v2));
    }

    CDT::Triangulation<double> cdt;
    cdt.insertVertices(
        points.begin(),
        points.end(),
        [](const CustomPoint2D& p){ return p.x; },
        [](const CustomPoint2D& p){ return p.y; }
    );
    cdt.insertEdges(
        edges.begin(),
        edges.end(),
        [](const CustomEdge& e){ return e.vertices.first; },
        [](const CustomEdge& e){ return e.vertices.second; }
    );
    cdt.eraseSuperTriangle();
//    cdt.eraseOuterTrianglesAndHoles();

    const auto& triangles = cdt.triangles;
    const auto& vertices = cdt.vertices;
    
    emscripten::val trianglesResult = emscripten::val::array();
    for (size_t i = 0; i < triangles.size(); ++i) {
        emscripten::val tri = emscripten::val::array();
        tri.set(0, triangles[i].vertices[0]);
        tri.set(1, triangles[i].vertices[1]);
        tri.set(2, triangles[i].vertices[2]);
        trianglesResult.set(i, tri);
    }
    
    emscripten::val verticesResult = emscripten::val::array();
    for (size_t i = 0; i < vertices.size(); ++i) {
        emscripten::val vert = emscripten::val::array();
        vert.set(0, vertices[i].x);
        vert.set(1, vertices[i].y);
        verticesResult.set(i, vert);
    }
    
    emscripten::val result = emscripten::val::object();
    result.set("triangles", trianglesResult);
    result.set("vertices", verticesResult);
    return result;
    
//    return result;
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("triangulate", &triangulate);
}
