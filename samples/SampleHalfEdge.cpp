#include <arepa/HalfEdgeMesh.h>
#include <arepa/MeshLoader.h>

#include <arepa/Matrix.h>

#include <iostream>
#include <map>
#include <vector>

int main() {
    arepa::OBJMeshLoader mesh_loader("../assets/happy_buddha.obj");

    const auto mesh = mesh_loader.load();
    const auto half_edge_mesh = arepa::convertToHalfEdgeMesh<float>(mesh);
    std::cout << half_edge_mesh.edges.size() << std::endl;
}
