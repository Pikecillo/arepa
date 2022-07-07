#include <arepa/Common.h>
#include <arepa/Texture.h>

namespace arepa {

namespace {
auto gl_internal_format = [](Texture::InternalFormat format) {
    switch (format) {
    case Texture::InternalFormat::RGBA:
        return GL_RGBA;
    case Texture::InternalFormat::RGB16F:
        return GL_RGB16F;
    case Texture::InternalFormat::Depth:
        return GL_DEPTH_COMPONENT24;
    default:
        return GL_NONE;
    }
};

auto gl_format = [](Texture::Format format) {
    switch (format) {
    case Texture::Format::RGBA:
        return GL_RGBA;
    case Texture::Format::RGB:
        return GL_RGB;
    case Texture::Format::Depth:
        return GL_DEPTH_COMPONENT;
    default:
        return GL_NONE;
    }
};

auto gl_type = [](Texture::Type type) {
    switch (type) {
    case Texture::Type::UByte:
        return GL_UNSIGNED_BYTE;
    case Texture::Type::Float:
        return GL_FLOAT;
    default:
        return GL_NONE;
    }
};
} // namespace

Texture::Ptr Texture::create() {
    return std::shared_ptr<Texture>(new Texture());
}

Texture::Texture() {
    glGenTextures(1, &m_handle);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_handle);
}

void Texture::init(std::uint32_t width, std::uint32_t height,
                   Texture::InternalFormat internal_format,
                   Texture::Format format, Texture::Type type) {
    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexImage2D(GL_TEXTURE_2D, 0, gl_internal_format(internal_format), width,
                 height, 0, gl_format(format), gl_type(type), nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Texture::init(const std::vector<std::uint8_t> &data, std::uint32_t width,
                   std::uint32_t height,
                   Texture::InternalFormat internal_format,
                   Texture::Format format, Texture::Type type) {
    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexImage2D(GL_TEXTURE_2D, 0, gl_internal_format(internal_format), width,
                 height, 0, gl_format(format), gl_type(type), data.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

std::uint32_t Texture::handle() const {
    return m_handle;
}

} // namespace arepa
