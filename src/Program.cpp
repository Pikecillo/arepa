#include <assert.h>

#include <arepa/Common.h>
#include <arepa/Program.h>

Program::Ptr Program::create(const std::vector<Shader::Ptr>& shaders)
{
    return std::shared_ptr<Program>(new Program{shaders});
}

bool Program::init(const std::vector<Shader::Ptr>& shaders) {
    m_shaders = shaders;

    for(auto &shader : shaders) {
	if(!shader)
	    return false;

	glAttachShader(m_handle, shader->handle());
    }

    glLinkProgram(m_handle);

    return true;
}

Program::Program(const std::vector<Shader::Ptr>& shaders)
    : m_handle(0) {
    m_handle = glCreateProgram();

    init(shaders);
}

Program::~Program() {
    glDeleteProgram(m_handle);
}

void Program::bind() {
    glUseProgram(m_handle);
}

void Program::unbind() {
    glUseProgram(0);
}

bool Program::set_attribute(const Attribute& attr, VertexBuffer::Ptr buffer) {
    static auto gl_type = [](Attribute::Type type) {
	switch(type) {
	case Attribute::Type::Float:
	return GL_FLOAT;
	case Attribute::Type::Int:
	return GL_INT;
	}
    };

    if(!buffer)
	return false;

    std::int32_t location = glGetAttribLocation(m_handle, attr.name().c_str());

    if(location == -1) {
	assert(false);
	return false;
    }

    glEnableVertexAttribArray(location);
    buffer->bind();
    glVertexAttribPointer(location, attr.components(),
			  gl_type(attr.type()), GL_FALSE, attr.stride(),
			  static_cast<char *>(0) + attr.offset());

    return true;
}

bool Program::draw(Program::Mode mode, IndexBuffer::Ptr index) {
    static auto gl_mode = [](Mode mode) {
	switch(mode) {
	case Mode::Triangles:
	return GL_TRIANGLES;
	case Mode::TriangleStrip:
	return GL_TRIANGLE_STRIP;
	case Mode::TriangleFan:
	return GL_TRIANGLE_FAN;
	}
    };

    if(!index)
	return false;

    index->bind();

    bind();
    glDrawElements(gl_mode(mode), index->size(), GL_UNSIGNED_INT, 0);
    unbind();

    return true;
}

bool Program::is_valid() {
    int valid_status;
    int max_length;
    char *info_log;

    if(m_handle == 0)
	return false;
    
    glValidateProgram(m_handle);
    glGetProgramiv(m_handle, GL_VALIDATE_STATUS, &valid_status);
    
    if(!valid_status) {
	glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &max_length);
	info_log = new char[max_length];
	
	glGetProgramInfoLog(m_handle, max_length, &max_length, info_log);

	// TODO: put into singleton Log
	printf("%s\n", info_log);
	delete [] info_log;
	
	return false;
    }

    return true;
}

void Program::set_uniform_1f(const std::string &name, const float value) {
    int location = glGetUniformLocation(m_handle, name.c_str());
    assert(location != -1);
    glUniform1f(location, value);
}

void Program::set_uniform_1i(const std::string &name,
			     const std::int32_t value) {
    int location = glGetUniformLocation(m_handle, name.c_str());
    assert(location != -1);
    glUniform1i(location, value);
}

void Program::set_uniform_matrix_4f(const std::string &name,
				    const float matrix[],
				    bool transpose) {
    int location = glGetUniformLocation(m_handle, name.c_str());
    assert(location != -1);
    glUniformMatrix4fv(location, 1, transpose, matrix);
}

void Program::set_uniform_3f(const std::string &name, const float vector[]) {
    int location = glGetUniformLocation(m_handle, name.c_str());
    assert(location != -1);
    glUniform3fv(location, 1, vector);
}
