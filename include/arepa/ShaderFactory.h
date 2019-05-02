#pragma once

#include <memory>

#include <arepa/Shader.h>

namespace arepa {

class ShaderFactory {
  public:
    template <class ShaderType>
    static Shader::Ptr create(const std::string &src);
};

template <class ShaderType>
Shader::Ptr ShaderFactory::create(const std::string &src) {
    auto shader = std::make_shared<ShaderType>();
    shader->init(src);
    return shader;
}

} // namespace arepa
