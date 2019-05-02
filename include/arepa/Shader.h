#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace arepa {

class Shader {
  public:
    using Ptr = std::shared_ptr<Shader>;

    virtual ~Shader();

    std::uint32_t handle() const;

    bool is_valid() const;

    void init(const std::string &src);

  protected:
    Shader();

    virtual void create() = 0;

  protected:
    std::uint32_t m_handle;
};

class VertexShader : public Shader {
  public:
    VertexShader() = default;

    void operator=(const VertexShader &other) = delete;

  protected:
    void create() override;
};

class FragmentShader : public Shader {
  public:
    FragmentShader() = default;

    void operator=(const VertexShader &other) = delete;

  protected:
    void create() override;
};

class GeometryShader : public Shader {
  public:
    GeometryShader() = default;

    void operator=(const VertexShader &other) = delete;

  protected:
    void create() override;
};

} // namespace arepa
