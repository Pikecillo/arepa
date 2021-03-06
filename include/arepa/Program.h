#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <arepa/Attribute.h>
#include <arepa/Buffer.h>
#include <arepa/Shader.h>

namespace arepa {

class Program {
  public:
    enum class Mode { Triangles, TriangleStrip, TriangleFan };

    using Ptr = std::shared_ptr<Program>;

  public:
    static Ptr create(const std::vector<Shader::Ptr> &shaders);

    ~Program();

    bool init(const std::vector<Shader::Ptr> &shaders);

    bool is_valid();

    void bind();

    void unbind();

    bool draw(Mode mode, IndexBuffer::Ptr index);

    bool set_attribute(const Attribute &attr, VertexBuffer::Ptr buffer);

    void set_uniform_1f(const std::string &name, const float value);

    void set_uniform_1i(const std::string &name, const std::int32_t value);

    void set_uniform_matrix_4f(const std::string &name, const float matrix[],
                               bool transpose = false);

    void set_uniform_3f(const std::string &name, const float vector[]);

  private:
    Program(const std::vector<Shader::Ptr> &shaders);

  private:
    std::vector<Shader::Ptr> m_shaders;

    std::uint32_t m_handle;
};

} // namespace arepa
