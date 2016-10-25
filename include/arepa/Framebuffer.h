#pragma once

#include <cstdint>
#include <memory>

#include <arepa/Texture.h>

class Renderbuffer {
public:
    using Ptr = std::shared_ptr<Renderbuffer>;

    enum class Type { Color, Depth };

public:
    Ptr create(std::uint32_t width, std::uint32_t height, Type type);

    virtual ~Renderbuffer();

    void bind() const;

    void unbind() const;

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

    void bind() const;

    void unbind() const;

    void attach_color(Texture::Ptr texture, std::uint8_t slot) const;

    void attach_depth(Texture::Ptr texture) const;

    bool is_valid() const;

    void blit() const;

private:
    Framebuffer();

private:
    std::uint32_t m_handle;
};
