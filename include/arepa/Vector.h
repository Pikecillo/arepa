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

#include <arepa/Common.h>

namespace arepa {

template <class Type, template <typename, size_t> class VectorType, size_t Size>
class BaseVector {
    static_assert(Size > 0, "BaseVector: size of vector cannot be zero");

  protected:
    BaseVector() = default;

    explicit BaseVector(Type s) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] = s;
    }

  public:
    size_t size() const {
        return Size;
    }

    const Type &at(size_t i) const {
        AREPA_ASSERT(i >= 0 && i < Size);
        return m_elements[i];
    }

    Type &at(size_t i) {
        AREPA_ASSERT(i >= 0 && i < Size);
        return m_elements[i];
    }

    const Type &operator[](size_t i) const {
        AREPA_ASSERT(i >= 0 && i < Size);
        return m_elements[i];
    }

    Type &operator[](size_t i) {
        AREPA_ASSERT(i >= 0 && i < Size);
        return m_elements[i];
    }

    bool operator==(const VectorType<Type, Size> &other) const {
        for (size_t i = 0; i < Size; i++) {
            if (m_elements[i] != other.m_elements[i])
                return false;
        }

        return true;
    }

    bool operator==(const Type &scalar) const {
        for (size_t i = 0; i < Size; i++) {
            if (m_elements[i] != scalar)
                return false;
        }

        return true;
    }

    bool operator!=(const VectorType<Type, Size> &other) const {
        return !((*this) == other);
    }

    bool operator!=(const Type &scalar) const {
        return !((*this) == scalar);
    }

    VectorType<Type, Size> operator-() const {
        VectorType<Type, Size> res(
            *(static_cast<const VectorType<Type, Size> *>(this)));

        for (size_t i = 0; i < Size; i++)
            res[i] = -m_elements[i];

        return res;
    }

    VectorType<Type, Size> &operator+=(const Type &scalar) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] += scalar;

        return *(static_cast<VectorType<Type, Size> *>(this));
    }

    VectorType<Type, Size> &operator+=(const VectorType<Type, Size> &other) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] += other.m_elements[i];

        return *(static_cast<VectorType<Type, Size> *>(this));
    }

    VectorType<Type, Size> &operator-=(const VectorType<Type, Size> &other) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] -= other.m_elements[i];

        return *(static_cast<VectorType<Type, Size> *>(this));
    }

    VectorType<Type, Size> &operator-=(const Type &scalar) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] -= scalar;

        return *(static_cast<VectorType<Type, Size> *>(this));
    }

    VectorType<Type, Size> &operator*=(const Type &scalar) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] *= scalar;

        return *(static_cast<VectorType<Type, Size> *>(this));
    }

    VectorType<Type, Size> &operator*=(const VectorType<Type, Size> &other) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] *= other.m_elements[i];

        return *(static_cast<VectorType<Type, Size> *>(this));
    }

    VectorType<Type, Size> &operator/=(const Type &scalar) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] /= scalar;

        return *(static_cast<VectorType<Type, Size> *>(this));
    }

    VectorType<Type, Size> &operator/=(const VectorType<Type, Size> &other) {
        for (size_t i = 0; i < Size; i++)
            m_elements[i] /= other.m_elements[i];

        return *(static_cast<VectorType<Type, Size> *>(this));
    }

    VectorType<Type, Size> operator+(const Type &scalar) const {
        VectorType<Type, Size> res(
            *(static_cast<const VectorType<Type, Size> *>(this)));
        res += scalar;
        return res;
    }

    VectorType<Type, Size>
    operator+(const VectorType<Type, Size> &other) const {
        VectorType<Type, Size> res(
            *(static_cast<const VectorType<Type, Size> *>(this)));
        res += other;
        return res;
    }

    VectorType<Type, Size> operator-(const Type &scalar) const {
        VectorType<Type, Size> res(
            *(static_cast<const VectorType<Type, Size> *>(this)));
        res -= scalar;
        return res;
    }

    VectorType<Type, Size>
    operator-(const VectorType<Type, Size> &other) const {
        VectorType<Type, Size> res(
            *(static_cast<const VectorType<Type, Size> *>(this)));
        res -= other;
        return res;
    }

    VectorType<Type, Size> operator*(const Type &scalar) const {
        VectorType<Type, Size> res(
            *(static_cast<const VectorType<Type, Size> *>(this)));
        res *= scalar;
        return res;
    }

    VectorType<Type, Size>
    operator*(const VectorType<Type, Size> &other) const {
        VectorType<Type, Size> res(
            *(static_cast<const VectorType<Type, Size> *>(this)));
        res *= other;
        return res;
    }

    VectorType<Type, Size> operator/(const Type &scalar) const {
        VectorType<Type, Size> res(
            *(static_cast<VectorType<Type, Size> *>(this)));
        res /= scalar;
        return res;
    }

    VectorType<Type, Size>
    operator/(const VectorType<Type, Size> &other) const {
        VectorType<Type, Size> res(
            *(static_cast<VectorType<Type, Size> *>(this)));
        res /= other;
        return res;
    }

    bool operator<=(const VectorType<Type, Size> &other) const {
        for (size_t i = 0; i < Size; i++)
            if (m_elements[i] > other.m_elements[i])
                return false;
        return true;
    }

    bool operator>=(const VectorType<Type, Size> &other) const {
        for (size_t i = 0; i < Size; i++)
            if (m_elements[i] < other.m_elements[i])
                return false;
        return true;
    }

    bool operator<(const VectorType<Type, Size> &other) const {
        for (size_t i = 0; i < Size; i++)
            if (m_elements[i] >= other.m_elements[i])
                return false;
        return true;
    }

    bool operator>(const VectorType<Type, Size> &other) const {
        for (size_t i = 0; i < Size; i++)
            if (m_elements[i] <= other.m_elements[i])
                return false;
        return true;
    }

    Type dot(const VectorType<Type, Size> &other) const {
        Type sum = static_cast<Type>(0);
        for (size_t i = 0; i < Size; i++)
            sum += m_elements[i] * other.m_elements[i];
        return sum;
    }

    Type length() const {
        VectorType<Type, Size> v(
            *(static_cast<const VectorType<Type, Size> *>(this)));
        return sqrt(v.dot(v));
    }

    VectorType<Type, Size> normalize() const {
        VectorType<Type, Size> u(
            *(static_cast<const VectorType<Type, Size> *>(this)));
        u /= u.length();
        return u;
    }

    /*
     * Projection of other onto this vector
     */
    VectorType<Type, Size> project(const VectorType<Type, Size> &other) const {
        VectorType<Type, Size> p(
            *(static_cast<VectorType<Type, Size> *>(this)));
        p = (*this) * (dot(other) / dot(this));
        return p;
    }

    Type extent() const {
        Type prod = static_cast<Type>(1);
        for (size_t i = 0; i < Size; i++)
            prod *= m_elements[i];
        return prod;
    }

    VectorType<Type, Size> max(const VectorType<Type, Size> &other) const {
        VectorType<Type, Size> res;

        for (size_t i = 0; i < Size; i++) {
            res[i] =
                (m_elements[i] > other.m_elements[i] ? m_elements[i]
                                                     : other.m_elements[i]);
        }

        return res;
    }

    VectorType<Type, Size> min(const VectorType<Type, Size> &other) const {
        VectorType<Type, Size> res;

        for (size_t i = 0; i < Size; i++) {
            res[i] =
                (m_elements[i] < other.m_elements[i] ? m_elements[i]
                                                     : other.m_elements[i]);
        }

        return res;
    }

    VectorType<Type, Size + 1> homogeneous() const {
        VectorType<Type, Size + 1> h;

        for (size_t i = 0; i < Size; i++)
            h[i] = m_elements[i];

        h[Size] = static_cast<Type>(1);

        return h;
    }

    VectorType<Type, Size - 1> cartesian() const {
        VectorType<Type, Size - 1> c;

        for (size_t i = 0; i < Size - 1; i++)
            c[i] = m_elements[i] / m_elements[Size - 1];

        return c;
    }

  protected:
    Type m_elements[Size];
};

template <class Type, size_t Size>
class Vector : public BaseVector<Type, Vector, Size> {
  public:
    Vector() : BaseVector<Type, Vector, Size>() {
    }

    explicit Vector(Type s) : BaseVector<Type, Vector, Size>(s) {
    }

    Vector(const Vector<Type, Size> &other) : BaseVector<Type, Vector, Size>() {
        (*this) = other;
    }

    void operator=(const Vector<Type, Size> &other) {
        for (size_t i = 0; i < Size; i++)
            this->m_elements[i] = other.m_elements[i];
    }
};

template <class Type>
class Vector<Type, 2> : public BaseVector<Type, Vector, 2> {
  public:
    Vector() : BaseVector<Type, Vector, 2>() {
    }

    explicit Vector(Type s) : BaseVector<Type, Vector, 2>(s) {
    }

    Vector(const Type &e0, const Type &e1) : BaseVector<Type, Vector, 2>() {
        this->m_elements[0] = e0;
        this->m_elements[1] = e1;
    }

    Vector(const Vector<Type, 2> &other) : BaseVector<Type, Vector, 2>() {
        (*this) = other;
    }

    void operator=(const Vector<Type, 2> &other) {
        this->m_elements[0] = other.m_elements[0];
        this->m_elements[1] = other.m_elements[1];
    }

    const Type &x() const {
        return this->m_elements[0];
    }
    const Type &y() const {
        return this->m_elements[1];
    }
    Type &x() {
        return this->m_elements[0];
    }
    Type &y() {
        return this->m_elements[1];
    }
};

template <class Type>
class Vector<Type, 3> : public BaseVector<Type, Vector, 3> {
  public:
    Vector() : BaseVector<Type, Vector, 3>() {
    }

    explicit Vector(Type s) : BaseVector<Type, Vector, 3>(s) {
    }

    Vector(const Type &e0, const Type &e1, const Type &e2)
        : BaseVector<Type, Vector, 3>() {
        this->m_elements[0] = e0;
        this->m_elements[1] = e1;
        this->m_elements[2] = e2;
    }

    Vector(const Vector<Type, 3> &other) : BaseVector<Type, Vector, 3>() {
        (*this) = other;
    }

    void operator=(const Vector<Type, 3> &other) {
        this->m_elements[0] = other.m_elements[0];
        this->m_elements[1] = other.m_elements[1];
        this->m_elements[2] = other.m_elements[2];
    }

    const Type &x() const {
        return this->m_elements[0];
    }
    const Type &y() const {
        return this->m_elements[1];
    }
    const Type &z() const {
        return this->m_elements[2];
    }
    Type &x() {
        return this->m_elements[0];
    }
    Type &y() {
        return this->m_elements[1];
    }
    Type &z() {
        return this->m_elements[2];
    }

    Vector<Type, 3> cross(const Vector<Type, 3> &other) const {
        Vector<Type, 3> res;

        res.x() = y() * other.z() - z() * other.y();
        res.y() = z() * other.x() - x() * other.z();
        res.z() = x() * other.y() - y() * other.x();

        return res;
    }
};

template <class Type>
class Vector<Type, 4> : public BaseVector<Type, Vector, 4> {
  public:
    Vector() : BaseVector<Type, Vector, 4>() {
    }

    explicit Vector(Type s) : BaseVector<Type, Vector, 4>(s) {
    }

    Vector(const Type &e0, const Type &e1, const Type &e2, const Type &e3)
        : BaseVector<Type, Vector, 4>() {
        this->m_elements[0] = e0;
        this->m_elements[1] = e1;
        this->m_elements[2] = e2;
        this->m_elements[3] = e3;
    }

    Vector(const Vector<Type, 4> &other) : BaseVector<Type, Vector, 4>() {
        (*this) = other;
    }

    void operator=(const Vector<Type, 4> &other) {
        this->m_elements[0] = other.m_elements[0];
        this->m_elements[1] = other.m_elements[1];
        this->m_elements[2] = other.m_elements[2];
        this->m_elements[3] = other.m_elements[3];
    }

    const Type &x() const {
        return this->m_elements[0];
    }
    const Type &y() const {
        return this->m_elements[1];
    }
    const Type &z() const {
        return this->m_elements[2];
    }
    const Type &w() const {
        return this->m_elements[3];
    }
    Type &x() {
        return this->m_elements[0];
    }
    Type &y() {
        return this->m_elements[1];
    }
    Type &z() {
        return this->m_elements[2];
    }
    Type &w() {
        return this->m_elements[3];
    }
};

template <class Type, size_t Size>
Vector<Type, Size> operator+(Type s, const Vector<Type, Size> &v) {
    Vector<Type, Size> res;
    for (size_t i = 0; i < Size; i++)
        res[i] = s + v[i];
    return res;
}

template <class Type, size_t Size>
Vector<Type, Size> operator-(Type s, const Vector<Type, Size> &v) {
    Vector<Type, Size> res;
    for (size_t i = 0; i < Size; i++)
        res[i] = s - v[i];
    return res;
}

template <class Type, size_t Size>
Vector<Type, Size> operator*(Type s, const Vector<Type, Size> &v) {
    Vector<Type, Size> res;
    for (size_t i = 0; i < Size; i++)
        res[i] = s * v[i];
    return res;
}

template <class Type, size_t Size>
Vector<Type, Size> operator/(Type s, const Vector<Type, Size> &v) {
    Vector<Type, Size> res;
    for (size_t i = 0; i < Size; i++)
        res[i] = s / v[i];
    return res;
}

template <typename Type> using Vec2 = Vector<Type, 2>;
template <typename Type> using Vec3 = Vector<Type, 3>;
template <typename Type> using Vec4 = Vector<Type, 4>;

using Vec2i = Vec2<std::int32_t>;
using Vec3i = Vec3<std::int32_t>;
using Vec4i = Vec4<std::int32_t>;

using Vec2f = Vec2<float>;
using Vec3f = Vec3<float>;
using Vec4f = Vec4<float>;

using Vec2d = Vec2<double>;
using Vec3d = Vec3<double>;
using Vec4d = Vec4<double>;

} // namespace arepa
