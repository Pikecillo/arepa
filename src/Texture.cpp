#include "Texture.h"

#include <GL/glew.h>
#include <GL/glut.h>

Texture::Ptr Texture::create() {
    return std::shared_ptr<Texture>(new Texture());
}

Texture::Texture() {
    glGenTextures(1, &m_handle);
} 

Texture::~Texture() {
    glDeleteTextures(1, &m_handle);
}

void Texture::init(const std::vector<std::uint8_t> &data,
		   std::uint32_t width,
		   std::uint32_t height,
		   Texture::Format format, Texture::Type type) {
    static auto gl_format = [](Format format) {
	switch(format) {
	case Format::RGBA:
	return GL_RGBA;
	case Format::RGB:
	return GL_RGB;
	}
    };
    static auto gl_type = [](Type type) {
	switch(type) {
	case Type::UByte:
	return GL_UNSIGNED_BYTE;
	}
    };

    glBindTexture(GL_TEXTURE_2D, m_handle);
    
    glTexImage2D(GL_TEXTURE_2D, 0, gl_format(format), width, height, 0,
		 gl_format(format), gl_type(type), data.data());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
