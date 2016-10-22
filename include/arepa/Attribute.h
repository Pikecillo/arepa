#pragma once

#include <cstdint>
#include <string>

class Attribute {
public:
    enum class Type { Float, Int };

    Attribute(const std::string &name,
	      Type type,
	      std::uint8_t components,
	      std::uint32_t stride,
	      std::uint32_t offset);

    const std::string &name() const;

    Type type() const;

    std::uint8_t components() const;

    std::uint32_t stride() const;

    std::uint32_t offset() const;

private:
    std::string m_name;
    Type m_type;
    std::uint8_t m_components;
    std::uint32_t m_stride;
    std::uint32_t m_offset;
};

inline
Attribute::Attribute(const std::string &name,
		     Type type,
		     std::uint8_t components,
		     std::uint32_t stride,
		     std::uint32_t offset)
	  : m_name(name),
	  m_type(type),
	  m_components(components),
	  m_stride(stride),
	  m_offset(offset) {}

inline
const std::string &Attribute::name() const {
    return m_name;
}

inline
Attribute::Type Attribute::type() const {
    return m_type;
}

inline
std::uint8_t Attribute::components() const {
    return m_components;
}

inline
std::uint32_t Attribute::stride() const {
    return m_stride;
}

inline
std::uint32_t Attribute::offset() const {
    return m_offset;
}
