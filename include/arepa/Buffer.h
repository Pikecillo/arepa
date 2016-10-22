#pragma once

#include <cstdint>
#include <memory>
#include <vector>

class Buffer {
public:
    virtual ~Buffer();

protected:
    Buffer();

protected:
    std::uint32_t m_handle;
};

class VertexBuffer : public Buffer {
public:
    using Ptr = std::shared_ptr<VertexBuffer>;

    static Ptr create();

    void bind();

    void set_data(const std::vector<float> &data);

private:
    VertexBuffer() = default;
};

class IndexBuffer : public Buffer {
public:
    using Ptr = std::shared_ptr<IndexBuffer>;

    static Ptr create();

    void bind();

    void set_data(const std::vector<std::uint32_t>& data);

    std::uint32_t size() const;

private:
    IndexBuffer();

private:
    std::uint32_t m_size;
};

inline
std::uint32_t IndexBuffer::size() const {
    return m_size;
}
