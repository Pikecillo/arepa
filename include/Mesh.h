#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "Vector.h"

class Mesh {
public:
    using Ptr = std::shared_ptr<Mesh>;

public:
    Mesh() = default;
    
    std::uint32_t num_triangles() const;
    
    std::uint32_t num_positions() const;
    
    std::uint32_t num_normals() const;
    
    std::uint32_t num_uvs() const;

    void set_positions_index(const std::vector<Vec3i> &positions_index);

    void set_normals_index(const std::vector<Vec3i> &normals_index);

    void set_uvs_index(const std::vector<Vec3i> &uvs_index);

    void set_positions(const std::vector<Vec3f> &positions);
    
    void set_normals(const std::vector<Vec3f> &normals);

    void set_uvs(const std::vector<Vec2f> &uvs);

    const std::vector<Vec3i> &get_positions_index() const;
    
    const std::vector<Vec3i> &get_normals_index() const;
    
    const std::vector<Vec3i> &get_uvs_index() const;
    
    const std::vector<Vec3f> &get_positions() const;
    
    const std::vector<Vec3f> &get_normals() const;
    
    const std::vector<Vec2f> &get_uvs() const;
  
private:
    std::vector<Vec3i> m_positions_index;
    std::vector<Vec3i> m_normals_index;
    std::vector<Vec3i> m_uvs_index;

    std::vector<Vec3f> m_positions;
    std::vector<Vec3f> m_normals;
    std::vector<Vec2f> m_uvs;
};
    
inline
std::uint32_t Mesh::num_triangles() const {
    return m_positions_index.size();
}

inline
std::uint32_t Mesh::num_positions() const {
    return m_positions.size();
}

inline
std::uint32_t Mesh::num_normals() const {
    return m_normals.size();
}

inline
std::uint32_t Mesh::num_uvs() const {
    return m_uvs.size();
}

inline
void Mesh::set_positions_index(const std::vector<Vec3i> &positions_index) {
    m_positions_index = positions_index;
}

inline
void Mesh::set_normals_index(const std::vector<Vec3i> &normals_index) {
    m_normals_index = normals_index;
}

inline
void Mesh::set_uvs_index(const std::vector<Vec3i> &uvs_index) {
    m_uvs_index = uvs_index;
}

inline
void Mesh::set_positions(const std::vector<Vec3f> &positions) {
    m_positions = positions;
}

inline
void Mesh::set_normals(const std::vector<Vec3f> &normals) {
    m_normals = normals;
}

inline
void Mesh::set_uvs(const std::vector<Vec2f> &uvs) {
    m_uvs = uvs;
}

inline
const std::vector<Vec3i> &Mesh::get_positions_index() const {
    return m_positions_index;
}

inline
const std::vector<Vec3i> &Mesh::get_normals_index() const {
    return m_normals_index;
}

inline
const std::vector<Vec3i> &Mesh::get_uvs_index() const {
    return m_uvs_index;
}

inline
const std::vector<Vec3f> &Mesh::get_positions() const {
    return m_positions;
}

inline
const std::vector<Vec3f> &Mesh::get_normals() const {
    return m_normals;
}

inline
const std::vector<Vec2f> &Mesh::get_uvs() const {
    return m_uvs;
}
