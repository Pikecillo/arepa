#include <arepa/Common.h>
#include <arepa/Framebuffer.h>

namespace arepa {
Renderbuffer::Renderbuffer(size_t width, size_t height, Type type) {
    glGenRenderbuffers(1, &m_handle);

    bind();

    if (type == Type::Color)
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
    else
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,
                              height);

    unbind();
}

Renderbuffer::~Renderbuffer() {
    glDeleteRenderbuffers(1, &m_handle);
}

Renderbuffer::Ptr Renderbuffer::create(size_t width, size_t height, Type type) {
    return std::shared_ptr<Renderbuffer>(new Renderbuffer(width, height, type));
}

void Renderbuffer::bind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
}

void Renderbuffer::unbind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &m_handle);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_handle);
}

Framebuffer::Ptr Framebuffer::create() {
    return std::make_shared<Framebuffer>();
}

void Framebuffer::bind() const {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_handle);
}

void Framebuffer::unbind() const {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Framebuffer::attach_color(Texture::Ptr texture, std::uint8_t slot) const {
    bind();
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot,
                           GL_TEXTURE_2D, texture->handle(), 0);
    unbind();
}

void Framebuffer::attach_depth(Texture::Ptr texture) const {
    bind();
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D, texture->handle(), 0);
    unbind();
}

bool Framebuffer::is_valid() const {
    return GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER);
}

void Framebuffer::blit() const {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_handle);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    // TODO: remove hardcoded values
    glBlitFramebuffer(0, 0, 255, 255, 0, 0, 255, 255, GL_COLOR_BUFFER_BIT,
                      GL_NEAREST);
}

} // namespace arepa
