#include <assert.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <arepa/Shader.h>

Shader::Shader() : m_handle(0) {}

Shader::~Shader() {
    glDeleteShader(m_handle);
}

std::uint32_t Shader::handle() const {
    return m_handle;
}

void Shader::init(const std::string &src) {
    create();

    const char *raw_src = src.c_str();
    glShaderSource(m_handle, 1, &raw_src, 0);
    glCompileShader(m_handle);
}

bool Shader::is_valid() const {
    int is_compiled;
    int max_length;
    char *info_log;
    
    if(m_handle == 0)
	return false;

    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &is_compiled);
    
    if(!is_compiled) {
	glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &max_length);
	info_log = new char[max_length];
	
	glGetShaderInfoLog(m_handle, max_length, &max_length, info_log);

	// TODO: put into singleton Log
	printf("Error validating shader: %s\n", info_log);
	delete [] info_log;
	
	return false;
    }

    return true;
}

void VertexShader::create() {
    m_handle = glCreateShader(GL_VERTEX_SHADER);
}

void FragmentShader::create() {
    m_handle = glCreateShader(GL_FRAGMENT_SHADER);
}

void GeometryShader::create() {
    m_handle = glCreateShader(GL_GEOMETRY_SHADER);
}
