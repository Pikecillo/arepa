#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <arepa/Vector.h>

namespace arepa {

template <typename Type> class Mesh {
  public:
    using Ptr = std::shared_ptr<Mesh<Type>>;

  public:
    Mesh() = default;

    std::uint32_t num_triangles() const;

    std::uint32_t num_positions() const;

    std::uint32_t num_normals() const;

    std::uint32_t num_uvs() const;

    void set_positions_index(const std::vector<Vec3i> &positions_index);

    void set_normals_index(const std::vector<Vec3i> &normals_index);

    void set_uvs_index(const std::vector<Vec3i> &uvs_index);

    void set_positions(const std::vector<Vec3<Type>> &positions);

    void set_normals(const std::vector<Vec3<Type>> &normals);

    void set_uvs(const std::vector<Vec2<Type>> &uvs);

    const std::vector<Vec3i> &get_positions_index() const;

    const std::vector<Vec3i> &get_normals_index() const;

    const std::vector<Vec3i> &get_uvs_index() const;

    const std::vector<Vec3<Type>> &get_positions() const;

    const std::vector<Vec3<Type>> &get_normals() const;

    const std::vector<Vec2<Type>> &get_uvs() const;

  private:
    std::vector<Vec3i> m_positions_index;
    std::vector<Vec3i> m_normals_index;
    std::vector<Vec3i> m_uvs_index;

    std::vector<Vec3<Type>> m_positions;
    std::vector<Vec3<Type>> m_normals;
    std::vector<Vec2<Type>> m_uvs;
};

template <typename Type> std::uint32_t Mesh<Type>::num_triangles() const {
    return m_positions_index.size();
}

template <typename Type> std::uint32_t Mesh<Type>::num_positions() const {
    return m_positions.size();
}

template <typename Type> std::uint32_t Mesh<Type>::num_normals() const {
    return m_normals.size();
}

template <typename Type> std::uint32_t Mesh<Type>::num_uvs() const {
    return m_uvs.size();
}

template <typename Type>
void Mesh<Type>::set_positions_index(
    const std::vector<Vec3i> &positions_index) {
    m_positions_index = positions_index;
}

template <typename Type>
void Mesh<Type>::set_normals_index(const std::vector<Vec3i> &normals_index) {
    m_normals_index = normals_index;
}

template <typename Type>
void Mesh<Type>::set_uvs_index(const std::vector<Vec3i> &uvs_index) {
    m_uvs_index = uvs_index;
}

template <typename Type>
void Mesh<Type>::set_positions(const std::vector<Vec3<Type>> &positions) {
    m_positions = positions;
}

template <typename Type>
void Mesh<Type>::set_normals(const std::vector<Vec3<Type>> &normals) {
    m_normals = normals;
}

template <typename Type>
void Mesh<Type>::set_uvs(const std::vector<Vec2<Type>> &uvs) {
    m_uvs = uvs;
}

template <typename Type>
const std::vector<Vec3i> &Mesh<Type>::get_positions_index() const {
    return m_positions_index;
}

template <typename Type>
const std::vector<Vec3i> &Mesh<Type>::get_normals_index() const {
    return m_normals_index;
}

template <typename Type>
const std::vector<Vec3i> &Mesh<Type>::get_uvs_index() const {
    return m_uvs_index;
}

template <typename Type>
const std::vector<Vec3<Type>> &Mesh<Type>::get_positions() const {
    return m_positions;
}

template <typename Type>
const std::vector<Vec3<Type>> &Mesh<Type>::get_normals() const {
    return m_normals;
}

template <typename Type>
const std::vector<Vec2<Type>> &Mesh<Type>::get_uvs() const {
    return m_uvs;
}

using Meshf = Mesh<float>;
using Meshd = Mesh<double>;

} // namespace arepa
