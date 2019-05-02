/*
 * University of Houston
 * Mario Rincon-Nigro. April 2013.
 */

#pragma once

#include <assert.h>
#include <math.h>

#include <arepa/Common.h>
#include <arepa/Vector.h>

namespace arepa {

template <template <typename, size_t, size_t> class MatrixType, typename Type,
          size_t Rows, size_t Cols>
class BaseMatrix {
private:
    static_assert(Rows > 0, "BaseMatrix: number of rows cannot be zero");
    static_assert(Cols > 0, "BaseMatrix: number of columns cannot be zero");

  protected:
    void set(Type s) {
        for (size_t i = 0; i < Rows; i++)
            elements[i] = Vector<Type, Cols>(s);
    }

    MatrixType<Type, Rows, Cols>* cast() const {
        return static_cast<MatrixType<Type, Rows, Cols> *>(this);
    }

  public:
    const Vector<Type, Cols> operator[](size_t i) const {
        AREPA_ASSERT(i <= Rows);
        return elements[i];
    }

    Vector<Type, Cols> &operator[](size_t i) {
        AREPA_ASSERT(i <= Rows);
        return elements[i];
    }

    const Vector<Type, Cols> row(size_t i) const {
        AREPA_ASSERT(i <= Rows);
        return elements[i];
    }

    Vector<Type, Cols> &row(size_t i) {
        AREPA_ASSERT(i <= Rows);
        return elements[i];
    }

    Vector<Type, Rows> col(size_t j) const {
        AREPA_ASSERT(j <= Cols);
        Vector<Type, Rows> c;
        for (size_t i = 0; i < Rows; i++)
            c[i] = elements[i][j];
        return c;
    }

    MatrixType<Type, Rows, Cols> &
    operator+=(const MatrixType<Type, Rows, Cols> &other) {
        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < Cols; j++)
                elements[i][j] += other.elements[i][j];

        return *cast();
    }

    MatrixType<Type, Rows, Cols> &
    operator-=(const MatrixType<Type, Rows, Cols> &other) {
        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < Cols; j++)
                elements[i][j] -= other.elements[i][j];

        return *cast();
    }

    MatrixType<Type, Rows, Cols> &operator*=(const Type &scalar) {
        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < Cols; j++)
                elements[i][j] *= scalar;

        return *cast();
    }

    template <size_t RowsInput, size_t ColsInput>
    MatrixType<Type, Rows, Cols> &
    operator*=(const MatrixType<Type, RowsInput, ColsInput> &other) {
        static_assert(Cols == RowsInput && Cols == ColsInput, "BaseMatrix: size mismatch in multiplications operands");
        MatrixType<Type, Rows, Cols> copy(*cast());

        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < ColsInput; j++) {
                Type dot = static_cast<Type>(0);

                for (size_t k = 0; k < Cols; k++)
                    dot += (copy.elements[i][k] * other.elements[k][j]);

                elements[i][j] = dot;
            }

        return *cast();
    }

    MatrixType<Type, Rows, Cols> &operator/=(const Type &scalar) {
        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < Cols; j++)
                elements[i][j] /= scalar;

        return *cast();
    }

    MatrixType<Type, Rows, Cols>
    operator+(const MatrixType<Type, Rows, Cols> &other) const {
        MatrixType<Type, Rows, Cols> result(*cast());
        result += other;
        return result;
    }

    MatrixType<Type, Rows, Cols> operator-() const {
        MatrixType<Type, Rows, Cols> result(*cast());
        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < Cols; j++)
                result[i][j] = -elements[i][j];

        return result;
    }

    MatrixType<Type, Rows, Cols>
    operator-(const MatrixType<Type, Rows, Cols> &other) const {
        MatrixType<Type, Rows, Cols> result(*cast());
        result -= other;
        return result;
    }

    MatrixType<Type, Rows, Cols> operator*(const Type &scalar) const {
        MatrixType<Type, Rows, Cols> result(*cast());
        result *= scalar;
        return result;
    }

    Vector<Type, Rows> operator*(const Vector<Type, Cols> &vector) const {
        Vector<Type, Rows> result;
        for (size_t i = 0; i < Rows; i++)
            result[i] = elements[i].dot(vector);

        return result;
    }

    template <size_t RowsInput, size_t ColsInput>
    MatrixType<Type, Rows, ColsInput>
    operator*(const MatrixType<Type, RowsInput, ColsInput> &other) const {
        static_assert(Cols == RowsInput, "BaseMatrix: size mismatch in multiplications operands");
        MatrixType<Type, Rows, ColsInput> result;
        for (size_t i = 0; i < Rows; i++) {
            for(size_t j = 0; j < ColsInput; j++) {
                Type dot = static_cast<Type>(0);
                for(size_t k = 0; k < Cols; k++) {
                    dot += elements[i][k] * other.elements[k][j];
                }

                result.elements[i][j] = dot;
            }
        }

        return result;
    }

    MatrixType<Type, Rows, Cols> operator/(const Type &scalar) const {
        MatrixType<Type, Rows, Cols> result(*cast());
        result /= scalar;
        return result;
    }

    MatrixType<Type, Cols, Rows> transpose() const {
        MatrixType<Type, Cols, Rows> trans(*cast());

        for (size_t i = 0; i < Cols; i++)
            for (size_t j = i + 1; j < Rows; j++)
                trans[i][j] = this->elements[j][i];

        return trans;
    }

    MatrixType<Type, Rows - 1, Cols - 1> subMatrix(size_t i, size_t j) const {
        AREPA_ASSERT(i < Rows && j < Cols);

        MatrixType<Type, Rows - 1, Cols - 1> m;
        for (size_t x = 0; x < Rows - 1; x++)
            for (size_t y = 0; y < Cols - 1; y++)
                m[x][y] =
                    this->elements[(x < i ? x : x + 1)][(y < j ? y : y + 1)];
        return m;
    }

    static MatrixType<Type, Rows, Cols> identity() {
        MatrixType<Type, Rows, Cols> id;

        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < Cols; j++)
                id[i][j] = (i == j ? static_cast<Type>(1) : static_cast<Type>(0));

        return id;
    }

    template <size_t Dim>
    static MatrixType<Type, Dim, Dim> outerProduct(const Vector<Type, Dim> &a,
                                                   const Vector<Type, Dim> &b) {
        MatrixType<Type, Dim, Dim> outer;

        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < Cols; j++)
                outer[i][j] = a[i] * b[j];

        return outer;
    }

    template <size_t Dim>
    static MatrixType<Type, Dim, Dim> projection(const Vector<Type, Dim> &v) {
        return (MatrixType<Type, Dim, Dim>::identity() -
                MatrixType<Type, Dim, Dim>::outerProduct(v, v));
    }

  protected:
    Vector<Type, Cols> elements[Rows];
};

template <typename Type, size_t Rows, size_t Cols>
class Matrix : public BaseMatrix<Matrix, Type, Rows, Cols> {
  public:
    Matrix() = default;

    Matrix(Type s) {
        this->set(s);
    }

    Matrix(const Matrix<Type, Rows, Cols> &other) {
        (*this) = other;
    }

    Matrix<Type, Rows, Cols> &operator=(const Matrix<Type, Rows, Cols> &other) {
        for (size_t i = 0; i < Rows; i++)
            this->elements[i] = other.elements[i];
        return (*this);
    }
};

template <class Type>
class Matrix<Type, 2, 2> : public BaseMatrix<Matrix, Type, 2, 2> {
  public:
    Matrix() = default;

    Matrix(Type s) {
        this->set(s);
    }

    Matrix(const Matrix<Type, 2, 2> &other) {
        (*this) = other;
    }

    Matrix<Type, 2, 2> &operator=(const Matrix<Type, 2, 2> &other) {
        this->elements[0] = other.elements[0];
        this->elements[1] = other.elements[1];
        return (*this);
    }

    Type det() const {
        return (this->elements[0][0] * this->elements[1][1] -
                this->elements[0][1] * this->elements[1][0]);
    }

    Matrix<Type, 2, 2> inverse() const {
        Matrix<Type, 2, 2> cof_trans;
        const Type tol = static_cast<Type>(1E-20);

        // Create matrix of cofactors
        cof_trans[0][0] = this->elements[1][1];
        cof_trans[0][1] = -this->elements[0][1];
        cof_trans[1][0] = -this->elements[1][0];
        cof_trans[1][1] = this->elements[0][0];

        Type d = det();
        AREPA_ASSERT(fabs(d) > tol);

        return cof_trans * (1 / d);
    }
};

template <class Type>
class Matrix<Type, 3, 3> : public BaseMatrix<Matrix, Type, 3, 3> {
  public:
    Matrix() = default;

    Matrix(Type s) {
        this->set(s);
    }

    Matrix(const Matrix<Type, 3, 3> &other) {
        (*this) = other;
    }

    Matrix<Type, 3, 3> &operator=(const Matrix<Type, 3, 3> &other) {
        this->elements[0] = other.elements[0];
        this->elements[1] = other.elements[1];
        this->elements[2] = other.elements[2];
        return (*this);
    }

    Type det() const {
        return (
            this->elements[0][0] * this->elements[1][1] * this->elements[2][2] +
            this->elements[0][1] * this->elements[1][2] * this->elements[2][0] +
            this->elements[0][2] * this->elements[1][0] * this->elements[2][1] -
            this->elements[0][2] * this->elements[1][1] * this->elements[2][0] -
            this->elements[0][0] * this->elements[1][2] * this->elements[2][1] -
            this->elements[0][1] * this->elements[1][0] * this->elements[2][2]);
    }

    Matrix<Type, 3, 3> inverse() const {
        Matrix<Type, 3, 3> cof;
        const Type tol = static_cast<Type>(1E-20);

        // Create matrix of cofactors
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++) {
                const Type c = this->subMatrix(i, j).det();
                AREPA_ASSERT(fabs(c) > tol);
                cof[i][j] = c * ((i + j) % 2 ? -1 : 1);
            }

        const Type d = det();
        assert(fabs(d) > tol);

        return cof.transpose() / d;
    }
};

template <typename Type> using Mat2 = Matrix<Type, 2, 2>;
template <typename Type> using Mat3 = Matrix<Type, 3, 3>;
template <typename Type> using Mat4 = Matrix<Type, 4, 4>;
template <typename Type> using Mat3x4 = Matrix<Type, 3, 4>;

using Mat2f = Mat2<float>;
using Mat3f = Mat3<float>;
using Mat4f = Mat4<float>;
using Mat3x4f = Mat3x4<float>;

using Mat2d = Mat2<double>;
using Mat3d = Mat3<double>;
using Mat4d = Mat4<double>;
using Mat3x4d = Mat3x4<double>;

} // namespace arepa
