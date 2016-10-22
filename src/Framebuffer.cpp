#include <arepa/Common.h>
#include <arepa/Framebuffer.h>

Renderbuffer::Renderbuffer(std::uint32_t width, std::uint32_t height,
			   Type type) {
    glGenRenderbuffers(1, &m_handle);

    bind();

    if (type == Type::Color)
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
    else
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
			      width, height);

    unbind();
}

Renderbuffer::~Renderbuffer() {
    glDeleteRenderbuffers(1, &m_handle);
}

Renderbuffer::Ptr Renderbuffer::create(std::uint32_t width,
				       std::uint32_t height,
				       Type type) {
    return std::shared_ptr<Renderbuffer>(new Renderbuffer(width, height, type));
}

void Renderbuffer::bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
}

void Renderbuffer::unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &m_handle);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_handle);
}

Framebuffer::Ptr Framebuffer::create() {
    return std::shared_ptr<Framebuffer>(new Framebuffer);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
