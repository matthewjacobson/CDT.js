#include "CDT.h"
#include <emscripten/bind.h>

using namespace emscripten;
using namespace CDT;

// -------------------
// Helper Functions
// -------------------

emscripten::val getVerticesJS(const Triangulation<double>& t) {
    emscripten::val array = emscripten::val::array();
    for (const auto& item : t.vertices) {
        emscripten::val vertex = emscripten::val::object();
        vertex.set("x", item.x);
        vertex.set("y", item.y);
        array.call<void>("push", vertex);
    }
    return array;
}

emscripten::val getTrianglesJS(const Triangulation<double>& t) {
    emscripten::val array = emscripten::val::array();
    for (const auto& item : t.triangles) {
        emscripten::val vertices = emscripten::val::array();
        vertices.set(0, item.vertices[0]);
        vertices.set(1, item.vertices[1]);
        vertices.set(2, item.vertices[2]);
        emscripten::val neighbors = emscripten::val::array();
        neighbors.set(0, item.neighbors[0]);
        neighbors.set(1, item.neighbors[1]);
        neighbors.set(2, item.neighbors[2]);
        emscripten::val triangle = emscripten::val::object();
        triangle.set("vertices", vertices);
        triangle.set("neighbors", neighbors);
        array.call<void>("push", triangle);
    }
    return array;
}

emscripten::val getFixedEdgesJS(const Triangulation<double>& t) {
    emscripten::val array = emscripten::val::array();
    for (const auto& item : t.fixedEdges) {
        emscripten::val fixedEdge = emscripten::val::object();
        fixedEdge.set("from", item.v1());
        fixedEdge.set("to", item.v2());
        array.call<void>("push", fixedEdge);
    }
    return array;
}

void insertVerticesJS(Triangulation<double>& t, val jsArray) {
    std::vector<V2d<double>> verts;
    const unsigned length = jsArray["length"].as<unsigned>();
    for (unsigned i = 0; i < length; ++i) {
        auto obj = jsArray[i];
        verts.emplace_back(obj["x"].as<double>(), obj["y"].as<double>());
    }
    t.insertVertices(verts);
}

void insertEdgesJS(Triangulation<double>& t, val jsArray) {
    std::vector<Edge> edges;
    const unsigned length = jsArray["length"].as<unsigned>();
    for (unsigned i = 0; i < length; ++i) {
        auto obj = jsArray[i];
        edges.emplace_back(obj["from"].as<int>(), obj["to"].as<int>());
    }
    t.insertEdges(edges);
}

void conformToEdgesJS(Triangulation<double>& t, val jsArray) {
    std::vector<Edge> edges;
    const unsigned length = jsArray["length"].as<unsigned>();
    for (unsigned i = 0; i < length; ++i) {
        auto obj = jsArray[i];
        edges.emplace_back(obj["from"].as<int>(), obj["to"].as<int>());
    }
    t.conformToEdges(edges);
}

EMSCRIPTEN_BINDINGS(cdt_module) {
    class_<Triangulation<double>>("Triangulation")
        .constructor<>()
        .function("getVertices", &getVerticesJS)
        .function("getTriangles", &getTrianglesJS)
        .function("getFixedEdges", &getFixedEdgesJS)
        .function("insertVertices", &insertVerticesJS)
        .function("insertEdges", &insertEdgesJS)
        .function("conformToEdges", &conformToEdgesJS)
        .function("eraseSuperTriangle", &Triangulation<double>::eraseSuperTriangle)
        .function("eraseOuterTriangles", &Triangulation<double>::eraseOuterTriangles)
        .function("eraseOuterTrianglesAndHoles", &Triangulation<double>::eraseOuterTrianglesAndHoles);
}
