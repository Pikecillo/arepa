#pragma once

#include <arepa/Mesh.h>

namespace arepa {

class MeshLoader {
  public:
    virtual Meshf::Ptr load() = 0;
};

class OBJMeshLoader : public MeshLoader {
  public:
    OBJMeshLoader(const std::string &filename);

    Meshf::Ptr load() override;

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

} // namespace arepa
