#pragma once

#include <cstdint>
#include <memory>

#include <arepa/Texture.h>

namespace arepa {

class Renderbuffer {
  public:
    using Ptr = std::shared_ptr<Renderbuffer>;

    enum class Type { Color, Depth };

  public:
    Ptr create(size_t width, size_t height, Type type);

    virtual ~Renderbuffer();

    void bind() const;

    void unbind() const;

  private:
    Renderbuffer(size_t width, size_t height, Type type);

  private:
    std::uint32_t m_handle;
};

class Framebuffer {
  public:
    using Ptr = std::shared_ptr<Framebuffer>;

  public:
    Framebuffer();

    static Ptr create();

    virtual ~Framebuffer();

    void bind() const;

    void unbind() const;

    void attach_color(Texture::Ptr texture, std::uint8_t slot) const;

    void attach_depth(Texture::Ptr texture) const;

    bool is_valid() const;

    void blit() const;

  private:
    std::uint32_t m_handle;
};

} // namespace arepa
