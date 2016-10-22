#pragma once

#include <memory>

#include "Shader.h"

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
