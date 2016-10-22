#pragma once

#include "Mesh.h"

class MeshLoader {
public:
    virtual Mesh::Ptr load() = 0;
};

class OBJMeshLoader : public MeshLoader {
public:
    OBJMeshLoader(const std::string &filename);
    
    Mesh::Ptr load() override;

private:
    void init(const std::string &filename);
    
private:
    std::vector<Vec3i> m_positions_index;
    std::vector<Vec3i> m_normals_index;
    std::vector<Vec3i> m_uvs_index;
    
    std::vector<Vec3f> m_positions;
    std::vector<Vec3f> m_normals;
    std::vector<Vec2f> m_uvs;
};
