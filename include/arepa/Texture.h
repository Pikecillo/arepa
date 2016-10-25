#pragma once

#include <cstdint>
#include <memory>
#include <vector>

class Texture {
public:
    using Ptr = std::shared_ptr<Texture>;

    enum class Format { RGBA, RGB, Depth };
    enum class InternalFormat { RGBA, RGB16F, Depth };
    enum class Type { UByte, Float };

public:
    static Ptr create();

    virtual ~Texture();

    void init(const std::vector<std::uint8_t> &data,
	      std::uint32_t width,
	      std::uint32_t height,
	      InternalFormat internal_format,
	      Format format, Type type);

    void init(std::uint32_t width,
	      std::uint32_t height,
	      InternalFormat internal_format,
	      Format format, Type type);

    std::uint32_t handle() const;

protected:
    Texture();

private:
    std::uint32_t m_handle;
};
