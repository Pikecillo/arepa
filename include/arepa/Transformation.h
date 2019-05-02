#pragma once

#include <arepa/Vector.h>

namespace arepa {

namespace Transformation {

void view(const Vec3f &eye, const Vec3f &lookat_point, const Vec3f &up,
          float mat[16]) {
    const Vec3f z = (eye - lookat_point).normalize();
    const Vec3f x = up.normalize().cross(z);
    const Vec3f y = z.cross(x);

    mat[0] = x.x();
    mat[4] = x.y();
    mat[8] = x.z();
    mat[12] = -eye.dot(x);
    mat[1] = y.x();
    mat[5] = y.y();
    mat[9] = y.z();
    mat[13] = -eye.dot(y);
    mat[2] = z.x();
    mat[6] = z.y();
    mat[10] = z.z();
    mat[14] = -eye.dot(z);
    mat[3] = 0;
    mat[7] = 0;
    mat[11] = 0;
    mat[15] = 1;
}

void orthographic(const Vec2f &left_right, const Vec2f &bottom_top,
                  const Vec2f &near_far, float mat[16]) {
    const float l = left_right.x(), r = left_right.y();
    const float b = bottom_top.x(), t = bottom_top.y();
    const float n = near_far.x(), f = near_far.y();
    const float rl = r - l, tb = t - b, fn = f - n;

    mat[0] = 2.0f / rl;
    mat[4] = 0.0f;
    mat[8] = 0.0f;
    mat[12] = -(r + l) / rl;
    mat[1] = 0.0f;
    mat[5] = 2.0f / tb;
    mat[9] = 0.0f;
    mat[13] = -(t + b) / tb;
    mat[2] = 0.0f;
    mat[6] = 0.0f;
    mat[10] = -2.0f / fn;
    mat[14] = -(f + n) / fn;
    mat[3] = 0.0f;
    mat[7] = 0.0f;
    mat[11] = 0.0f;
    mat[15] = 1.0f;
}

void perspective(const Vec2f &left_right, const Vec2f &bottom_top,
                 const Vec2f &near_far, float matrix[16]) {
    const float rl = left_right.y() - left_right.x();
    const float tb = bottom_top.y() - bottom_top.x();
    const float n = near_far.x();
    const float f = near_far.y();
    const float fn = f - n;

    matrix[0] = 2.0f * n / rl;
    matrix[5] = 2.0f * n / tb;
    matrix[8] = (left_right.y() + left_right.x()) / rl;
    matrix[9] = (bottom_top.y() + bottom_top.x()) / tb;
    matrix[10] = -(f + n) / fn;
    matrix[11] = -1.0f;
    matrix[14] = -2.0f * f * n / fn;

    matrix[1] = matrix[2] = matrix[3] = matrix[4] = matrix[6] = matrix[7] =
        matrix[12] = matrix[13] = matrix[15] = 0.0f;
}

} // namespace Transformation

} // namespace arepa
