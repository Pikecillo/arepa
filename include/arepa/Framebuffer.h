#pragma once

#include <cstdint>
#include <memory>

class Renderbuffer {
public:
    using Ptr = std::shared_ptr<Renderbuffer>;

    enum class Type { Color, Depth };

public:
    Ptr create(std::uint32_t width, std::uint32_t height, Type type);

    virtual ~Renderbuffer();

    void bind();

    void unbind();

private:
    Renderbuffer(std::uint32_t width, std::uint32_t height, Type type);

private:
    std::uint32_t m_handle;
};

class Framebuffer {
public:
    using Ptr = std::shared_ptr<Framebuffer>;

public:
    static Ptr create();

    virtual ~Framebuffer();

    void bind();

    void unbind();

private:
    Framebuffer();

private:
    std::uint32_t m_handle;
};
