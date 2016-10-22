#pragma once

#include <cstdint>

#include "Buffer.h"
#include "Mesh.h"

class BufferBuilder {
public:
    BufferBuilder(Mesh::Ptr mesh);

    void set_mesh(Mesh::Ptr mesh);

    VertexBuffer::Ptr build_position_buffer() const;

    VertexBuffer::Ptr build_normal_buffer() const;

    VertexBuffer::Ptr build_uv_buffer() const;

    IndexBuffer::Ptr build_index_buffer() const;

private:
    Mesh::Ptr m_mesh;
};

inline
BufferBuilder::BufferBuilder(Mesh::Ptr mesh) : m_mesh(mesh) {}

inline
void BufferBuilder::set_mesh(Mesh::Ptr mesh) {
    m_mesh = mesh;
}
