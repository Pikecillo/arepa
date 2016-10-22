#include <GL/glew.h>
#include <GL/glut.h>

#include "Buffer.h"

Buffer::Buffer() : m_handle(0) {
    glGenBuffers(1, &m_handle);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &m_handle);
}

VertexBuffer::VertexBuffer() : Buffer() {}

VertexBuffer::Ptr VertexBuffer::create() {
    return std::shared_ptr<VertexBuffer>(new VertexBuffer);
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void VertexBuffer::set_data(const std::vector<float> &data) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(),
		 GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer() : Buffer(), m_size(0) {}

IndexBuffer::Ptr IndexBuffer::create() {
    return std::shared_ptr<IndexBuffer>(new IndexBuffer);
}

void IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void IndexBuffer::set_data(const std::vector<std::uint32_t> &data) {
    m_size = data.size();

    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(std::uint32_t),
    		 data.data(), GL_STATIC_DRAW);
}
