#pragma once

#include <cstdint>
#include <memory>
#include <vector>

class Texture {
public:
    using Ptr = std::shared_ptr<Texture>;

    enum class Format { RGBA, RGB };
    enum class Type { UByte };

public:
    static Ptr create();

    virtual ~Texture();

    void init(const std::vector<std::uint8_t> &data,
	      std::uint32_t width,
	      std::uint32_t height,
	      Format format, Type type);

protected:
    Texture();

private:
    std::uint32_t m_handle;
};
