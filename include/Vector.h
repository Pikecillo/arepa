/**
 * Copyright (C) 2013. Mario Rincon-Nigro.
 *
 * This file is a part of Flowie.
 *
 * Flowie is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Flowie is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Flowie.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <assert.h>
#include <math.h>

#include <cstdint>

template <class TType,
    template <typename, std::uint32_t> class TVec, std::uint32_t v_size>
class BasicVector {
protected:
    BasicVector() {
	static_assert(v_size >= 1, "BasicVector: wrong size");
    }

    explicit BasicVector(TType s) {
	static_assert(v_size >= 1, "BasicVector: wrong size");
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] = s;
    }

public:
    std::uint32_t size() const {
	return v_size;
    }

    const TType& at(std::uint32_t i) const {
	assert(i >= 0 && i < v_size);
	return m_elements[i];
    }

    TType &at(std::uint32_t i) {
	assert(i >= 0 && i < v_size);
	return m_elements[i];
    }

    const TType& operator[](std::uint32_t i) const {
	assert(i >= 0 && i < v_size);
	return m_elements[i];
    }

    TType &operator[](std::uint32_t i) {
	assert(i >= 0 && i < v_size);
	return m_elements[i];
    }

    bool operator==(const TVec<TType, v_size> &other) const {
	for(std::uint32_t i = 0; i < v_size; i++) {
	    if(m_elements[i] != other.m_elements[i])
		return false;
	}
	
	return true;
    }

    bool operator==(const TType &scalar) const {
	for(std::uint32_t i = 0; i < v_size; i++) {
	    if(m_elements[i] != scalar)
		return false;
	}
	
	return true;
    }

    bool operator!=(const TVec<TType, v_size> &other) const {
	return !((*this) == other);
    }
    
    bool operator!=(const TType &scalar) const {
	return !((*this) == scalar);
    }
    
    TVec<TType, v_size> operator-() const {
	TVec<TType, v_size> res(
	    *(static_cast<const TVec<TType, v_size> *>(this)));
	
	for(std::uint32_t i = 0; i < v_size; i++)
	    res[i] = -m_elements[i];
	
	return res;
    }
    
    TVec<TType, v_size> &operator+=(const TType &scalar) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] += scalar;
	
	return *(static_cast<TVec<TType, v_size> *>(this));
    }
    
    TVec<TType, v_size> &operator+=(const TVec<TType, v_size> &other) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] += other.m_elements[i];
	
	return *(static_cast<TVec<TType, v_size> *>(this));
    }

    TVec<TType, v_size> &operator-=(const TVec<TType, v_size> &other) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] -= other.m_elements[i];
	
	return *(static_cast<TVec<TType, v_size> *>(this));
    }
    
    TVec<TType, v_size> &operator-=(const TType &scalar) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] -= scalar;
	
	return *(static_cast<TVec<TType, v_size> *>(this));
    }
    
    TVec<TType, v_size> &operator*=(const TType &scalar) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] *= scalar;
	
	return *(static_cast<TVec<TType, v_size> *>(this));
    }
    
    TVec<TType, v_size> &operator*=(const TVec<TType, v_size> &other) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] *= other.m_elements[i];
	
	return *(static_cast<TVec<TType, v_size> *>(this));
    }
    
    TVec<TType, v_size> &operator/=(const TType &scalar) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] /= scalar;
	
	return *(static_cast<TVec<TType, v_size> *>(this));
    }
    
    TVec<TType, v_size> &operator/=(const TVec<TType, v_size> &other) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    m_elements[i] /= other.m_elements[i];
	
	return *(static_cast<TVec<TType, v_size> *>(this));
    }
    
    TVec<TType, v_size> operator+(const TType &scalar) const {
	TVec<TType, v_size> res
	    (*(static_cast<const TVec<TType, v_size> *>(this)));
	res += scalar;
	return res;
    }
    
    TVec<TType, v_size> operator+(const TVec<TType, v_size> &other) const {
	TVec<TType, v_size> res
	    (*(static_cast<const TVec<TType, v_size> *>(this)));
	res += other;
	return res;
    }
    
    TVec<TType, v_size> operator-(const TType &scalar) const {
	TVec<TType, v_size> res
	    (*(static_cast<const TVec<TType, v_size> *>(this)));
	res -= scalar;
	return res;
    }
    
    TVec<TType, v_size> operator-(const TVec<TType, v_size> &other) const {
	TVec<TType, v_size> res
	    (*(static_cast<const TVec<TType, v_size> *>(this)));
	res -= other;
	return res;
    }
    
    TVec<TType, v_size> operator*(const TType &scalar) const {
	TVec<TType, v_size> res
	    (*(static_cast<const TVec<TType, v_size> *>(this)));
	res *= scalar;
	return res;
    }
    
    TVec<TType, v_size> operator*(const TVec<TType, v_size> &other) const {
	TVec<TType, v_size> res
	    (*(static_cast<const TVec<TType, v_size> *>(this)));
	res *= other;
	return res;
    }
    
    TVec<TType, v_size> operator/(const TType &scalar) const {
	TVec<TType, v_size> res(*(static_cast<TVec<TType, v_size> *>(this)));
	res /= scalar;
	return res;
    }
    
    TVec<TType, v_size> operator/(const TVec<TType, v_size> &other) const {
	TVec<TType, v_size> res(*(static_cast<TVec<TType, v_size> *>(this)));
	res /= other;
	return res;
    }
    
    bool operator<=(const TVec<TType, v_size> &other) const {
	for(std::uint32_t i = 0 ; i < v_size; i++)
	    if(m_elements[i] > other.m_elements[i])
		return false;
	return true;
    }
    
    bool operator>=(const TVec<TType, v_size> &other) const {
	for(std::uint32_t i = 0 ; i < v_size; i++)
	    if(m_elements[i] < other.m_elements[i])
		return false;
	return true;
    }
    
    bool operator<(const TVec<TType, v_size> &other) const {
	for(std::uint32_t i = 0 ; i < v_size; i++)
	    if(m_elements[i] >= other.m_elements[i])
		return false;
	return true;
    }
    
    bool operator>(const TVec<TType, v_size> &other) const {
	for(std::uint32_t i = 0 ; i < v_size; i++)
	    if(m_elements[i] <= other.m_elements[i])
		return false;
	return true;
    }
    
    TType dot(const TVec<TType, v_size> &other) const {
	TType sum = static_cast<TType>(0);
	for(std::uint32_t i = 0; i < v_size; i++)
	    sum += m_elements[i] * other.m_elements[i];
	return sum;
    }
    
    TType length() const {
	TVec<TType, v_size> v
	    (*(static_cast<const TVec<TType, v_size> *>(this)));
	return sqrt(v.dot(v));
    }
    
    TVec<TType, v_size> normalize() const {
	TVec<TType, v_size> u
	    (*(static_cast<const TVec<TType, v_size> *>(this)));
	u /= u.length();
	return u;
    }
    
    /*
     * Projection of other onto this vector
     */
    TVec<TType, v_size> project(const TVec<TType, v_size> &other) const {
	TVec<TType, v_size> p(*(static_cast<TVec<TType, v_size> *>(this)));
	p = (*this) * (dot(other) / dot(this));
	return p;
    }
    
    TType extent() const {
	TType prod = static_cast<TType>(1);
	for(std::uint32_t i = 0; i < v_size; i++)
	    prod *= m_elements[i];
	return prod;
    }
    
    TVec<TType, v_size> max(const TVec<TType, v_size> &other) const {
	TVec<TType, v_size> res;
	
	for(std::uint32_t i = 0; i < v_size; i++) {
	    res[i] = (m_elements[i] > other.m_elements[i] ?
		      m_elements[i] : other.m_elements[i]);
	}
	
	return res;
    }
    
    TVec<TType, v_size> min(const TVec<TType, v_size> &other) const {
	TVec<TType, v_size> res;
	
	for(std::uint32_t i = 0; i < v_size; i++) {
	    res[i] = (m_elements[i] < other.m_elements[i] ?
		      m_elements[i] : other.m_elements[i]);
	}
	
	return res;
    }
    
    TVec<TType, v_size + 1> homogeneous() const {
	TVec<TType, v_size + 1> h;
	
	for(std::uint32_t i = 0; i < v_size; i++)
	    h[i] = m_elements[i];
	
	h[v_size] = static_cast<TType>(1);
	
	return h;
    }
    
    TVec<TType, v_size - 1> cartesian() const {
	TVec<TType, v_size - 1> c;
	
	for(std::uint32_t i = 0; i < v_size - 1; i++)
	    c[i] = m_elements[i] / m_elements[v_size - 1];
	
	return c;
    }
    
protected:
    TType m_elements[v_size];
};

template <class TType, std::uint32_t v_size>
class Vector : public BasicVector<TType, Vector, v_size> {
public:
    Vector() : BasicVector<TType, Vector, v_size>() {}
    
    explicit Vector(TType s)
	: BasicVector<TType, Vector, v_size>(s) {}
    
    Vector(const Vector<TType, v_size> &other)
	: BasicVector<TType, Vector, v_size>() {
	(*this) = other;
    }

    void operator=(const Vector<TType, v_size> &other) {
	for(std::uint32_t i = 0; i < v_size; i++)
	    this->m_elements[i] = other.m_elements[i];
    }
};

template <class TType>
class Vector<TType, 2> : public BasicVector<TType, Vector, 2> {
public:
    Vector() : BasicVector<TType, Vector, 2>() {}

    explicit Vector(TType s)
	: BasicVector<TType, Vector, 2>(s) {}
    
    Vector(const TType &e0, const TType &e1)
	: BasicVector<TType, Vector, 2>() {
	this->m_elements[0] = e0;
	this->m_elements[1] = e1;
    }
    
    Vector(const Vector<TType, 2> &other)
	: BasicVector<TType, Vector, 2>() {
	(*this) = other;
    }
    
    void operator=(const Vector<TType, 2> &other) {
	this->m_elements[0] = other.m_elements[0];
	this->m_elements[1] = other.m_elements[1];
    }
    
    const TType &x() const { return this->m_elements[0]; }
    const TType &y() const { return this->m_elements[1]; }
    TType &x() { return this->m_elements[0]; }
    TType &y() { return this->m_elements[1]; }
};

template <class TType>
class Vector<TType, 3> : public BasicVector<TType, Vector, 3> {
public:
    Vector() : BasicVector<TType, Vector, 3>() {}
    
    explicit Vector(TType s)
	: BasicVector<TType, Vector, 3>(s) {}
    
    Vector(const TType &e0, const TType &e1, const TType &e2)
	: BasicVector<TType, Vector, 3>() {
	this->m_elements[0] = e0;
	this->m_elements[1] = e1;
	this->m_elements[2] = e2;
    }
    
    Vector(const Vector<TType, 3> &other)
	: BasicVector<TType, Vector, 3>() {
	(*this) = other;
    }

    void operator=(const Vector<TType, 3> &other) {
	this->m_elements[0] = other.m_elements[0];
	this->m_elements[1] = other.m_elements[1];
	this->m_elements[2] = other.m_elements[2];
    }
    
    const TType &x() const { return this->m_elements[0]; }
    const TType &y() const { return this->m_elements[1]; }
    const TType &z() const { return this->m_elements[2]; }
    TType &x() { return this->m_elements[0]; }
    TType &y() { return this->m_elements[1]; }
    TType &z() { return this->m_elements[2]; }
    
    Vector<TType, 3> cross(const Vector<TType, 3> &other) const {
	Vector<TType, 3> res;
	
	res.x() = y() * other.z() - z() * other.y();
	res.y() = z() * other.x() - x() * other.z();
	res.z() = x() * other.y() - y() * other.x();
	
	return res;
    }
};

template <class TType>
class Vector<TType, 4> : public BasicVector<TType, Vector, 4> {
public:
    Vector() : BasicVector<TType, Vector, 4>() {}
    
    explicit Vector(TType s)
	: BasicVector<TType, Vector, 4>(s) {}
    
    Vector(const TType &e0, const TType &e1, const TType &e2, const TType &e3)
	: BasicVector<TType, Vector, 4>() {
	this->m_elements[0] = e0;
	this->m_elements[1] = e1;
	this->m_elements[2] = e2;
	this->m_elements[3] = e3;
    }
    
    Vector(const Vector<TType, 4> &other)
	: BasicVector<TType, Vector, 4>() {
	(*this) = other;
    }
    
    void operator=(const Vector<TType, 4> &other) {
	this->m_elements[0] = other.m_elements[0];
	this->m_elements[1] = other.m_elements[1];
	this->m_elements[2] = other.m_elements[2];
	this->m_elements[3] = other.m_elements[3];
    }
    
    const TType &x() const { return this->m_elements[0]; }
    const TType &y() const { return this->m_elements[1]; }
    const TType &z() const { return this->m_elements[2]; }
    const TType &w() const { return this->m_elements[3]; }
    TType &x() { return this->m_elements[0]; }
    TType &y() { return this->m_elements[1]; }
    TType &z() { return this->m_elements[2]; }
    TType &w() { return this->m_elements[3]; }
};

template <class TType, int v_size>					       
inline Vector<TType, v_size>					
operator+(TType s, const Vector<TType, v_size> &v) {		
    Vector<TType, v_size> res;						
    for(std::uint32_t i = 0; i < v_size; i++)					
	res[i] = s + v[i];						
    return res;							
}									

template <class TType, int v_size>					       
inline Vector<TType, v_size>					
operator-(TType s, const Vector<TType, v_size> &v) {		
    Vector<TType, v_size> res;						
    for(std::uint32_t i = 0; i < v_size; i++)					
	res[i] = s - v[i];						
    return res;							
}

template <class TType, int v_size>					       
inline Vector<TType, v_size>					
operator*(TType s, const Vector<TType, v_size> &v) {		
    Vector<TType, v_size> res;						
    for(std::uint32_t i = 0; i < v_size; i++)					
	res[i] = s * v[i];						
    return res;							
}

template <class TType, int v_size>					       
inline Vector<TType, v_size>					
operator/(TType s, const Vector<TType, v_size> &v) {		
    Vector<TType, v_size> res;						
    for(std::uint32_t i = 0; i < v_size; i++)					
	res[i] = s / v[i];						
    return res;							
}	

using Vec2i = Vector<std::int32_t, 2>;
using Vec3i = Vector<std::int32_t, 3>;
using Vec4i = Vector<std::int32_t, 4>;

using Vec2f = Vector<float, 2>;
using Vec3f = Vector<float, 3>;
using Vec4f = Vector<float, 4>;

using Vec2d = Vector<double, 2>;
using Vec3d = Vector<double, 3>;
using Vec4d = Vector<double, 4>;
