#pragma once

#include <map>
#include <vector>

#include <arepa/Mesh.h>
#include <arepa/Vector.h>

namespace arepa {

template <typename Type> struct HalfEdge;

template <typename Type> struct HalfEdgeVertex {
    Vec3<Type> position;
    HalfEdge<Type> *edge;
};

template <typename Type> struct HalfEdgeFace { HalfEdge<Type> *edge; };

template <typename Type> struct HalfEdge {
    HalfEdgeVertex<Type> *vertex;
    HalfEdgeFace<Type> *face;
    HalfEdge<Type> *next;
    HalfEdge<Type> *pair;
};

template <typename Type> struct HalfEdgeMesh {
    std::vector<HalfEdge<Type>> edges;
    std::vector<HalfEdgeVertex<Type>> vertices;
    std::vector<HalfEdgeFace<Type>> faces;
};

template <typename Type>
HalfEdgeMesh<Type> convertToHalfEdgeMesh(typename Mesh<Type>::Ptr mesh) {
    HalfEdgeMesh<Type> half_edge_mesh;
    const auto &positions = mesh->get_positions();
    const auto &positions_index = mesh->get_positions_index();

    const size_t num_triangles = mesh->num_triangles();
    half_edge_mesh.vertices.reserve(positions.size());
    half_edge_mesh.edges.reserve(3 * num_triangles);
    half_edge_mesh.faces.reserve(num_triangles);

    // Create half edge vertices
    for (const auto &pos : positions) {
        const Vec3<Type> p = {pos.at(0), pos.at(1), pos.at(2)};
        half_edge_mesh.vertices.push_back({p, nullptr});
    }

    std::map<std::pair<HalfEdgeVertex<Type> *, HalfEdgeVertex<Type> *>,
             HalfEdge<Type> *>
        vertex_pair_to_edge;

    // Create half edges and faces
    for (const auto &triangle : positions_index) {
        auto &v0 = half_edge_mesh.vertices[triangle.at(0)];
        auto &v1 = half_edge_mesh.vertices[triangle.at(1)];
        auto &v2 = half_edge_mesh.vertices[triangle.at(2)];

        half_edge_mesh.faces.push_back({nullptr});
        auto &face = half_edge_mesh.faces.back();

        half_edge_mesh.edges.push_back({&v2, &face, nullptr, nullptr});
        auto &edge2 = half_edge_mesh.edges.back();
        half_edge_mesh.edges.push_back({&v1, &face, &edge2, nullptr});
        auto &edge1 = half_edge_mesh.edges.back();
        half_edge_mesh.edges.push_back({&v0, &face, &edge1, nullptr});
        auto &edge0 = half_edge_mesh.edges.back();
        edge2.next = &edge0;

        face.edge = &edge0;

        v0.edge = &edge0;
        v1.edge = &edge1;
        v2.edge = &edge2;

        vertex_pair_to_edge[std::make_pair(&v0, &v1)] = &edge0;
        vertex_pair_to_edge[std::make_pair(&v1, &v2)] = &edge1;
        vertex_pair_to_edge[std::make_pair(&v2, &v0)] = &edge2;
    }

    for (const auto &kv_pair : vertex_pair_to_edge) {
        const auto &vertex_pair = kv_pair.first;
        auto edge = kv_pair.second;
        const auto &v0 = vertex_pair.first;
        const auto &v1 = vertex_pair.second;

        if (edge->next == nullptr) {
            const auto it = vertex_pair_to_edge.find(std::make_pair(v1, v0));
            if (it != vertex_pair_to_edge.end()) {
                auto pair_edge = it->second;
                edge->pair = pair_edge;

                pair_edge->pair = edge;
            }
        }
    }

    return half_edge_mesh;
}

} // namespace arepa
