#pragma once

#include <cstdint>

#include <arepa/Buffer.h>
#include <arepa/Mesh.h>

namespace arepa {

class BufferBuilder {
  public:
    BufferBuilder(Meshf::Ptr mesh);

    void set_mesh(Meshf::Ptr mesh);

    VertexBuffer::Ptr build_position_buffer() const;

    VertexBuffer::Ptr build_normal_buffer() const;

    VertexBuffer::Ptr build_uv_buffer() const;

    IndexBuffer::Ptr build_index_buffer() const;

  private:
    Meshf::Ptr m_mesh;
};

inline BufferBuilder::BufferBuilder(Meshf::Ptr mesh) : m_mesh(mesh) {
}

inline void BufferBuilder::set_mesh(Meshf::Ptr mesh) {
    m_mesh = mesh;
}

} // namespace arepa
