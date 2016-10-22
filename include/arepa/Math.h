#ifndef MATH_HPP
#define MATH_HPP

#include "Common.h"

#define PI 3.14159265

namespace Math {
    inline double degrees_to_radians(float x) {
	return x * PI / 180.0;
    }
}

class Random {
public:
    static Random common(int seed=0) {
	return Random(seed);
    }
    
    int range(int lo, int hi) {
	return (rand() % (hi - lo)) + lo;
    }
    
    float uniform() const {
	return (float(rand()) / m_randMax);
    }
    
    float uniform(float lo, float hi) {
	return lo + (hi - lo) * uniform();
    }
    
private:
Random(int seed=0) : m_randMax(RAND_MAX) {
	srand(seed);
    }
    
private:
    const unsigned int m_randMax;
};

class Vector2 {
public:
Vector2() : x(0.0f), y(0.0f) {};
Vector2(float _x, float _y) : x(_x), y(_y) {};
    
    const Vector2 &operator=(const Vector2 &other) {
	x = other.x; y = other.y;
	
	return (*this);
    }
    
    Vector2 operator-(const Vector2 &other) const {
	Vector2 res;
	
	res.x = x - other.x;
	res.y = y - other.y;
	
	return res;
    }
    
    float dot(const Vector2 &other) const {
	return x * other.x + y * other.y;
    }
    
    float squaredLength() const {
	return dot(*this);
    }
    
public:
    float x, y;
};

class Vector3 {
public:
Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
Vector3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z) {}
    
    Vector3 operator*(float scalar) const {
	Vector3 res;
	
	res.x = x * scalar;
	res.y = y * scalar;
	res.z = z * scalar;
	
	return res;
    }
    
public:
    float x, y, z;
};

class Vector2i {
public:
Vector2i() : x(0), y(0) {}
Vector2i(int _x, int _y)
    : x(_x), y(_y) {}
    int &operator[](int i) {
	return *((int *)this + i);
    }
    
public:
    int x, y;
};

class Vector3i {
public:
Vector3i() : x(0), y(0), z(0) {}
Vector3i(int _x, int _y, int _z)
    : x(_x), y(_y), z(_z) {}
    int &operator[](int i) {
	return *((int *)this + i);
    }
    
public:
    int x, y, z;
};

class Matrix3 {
public:
    static Matrix3 identity() {
	Matrix3 id;
	
	id.m_elements[0] = 1.0f;
		id.m_elements[4] = 1.0f;
		id.m_elements[8] = 1.0f;

		return id;
	}

	Matrix3() {
		m_elements = new float[9];

		for(int i = 0; i < 9; i++)
			m_elements[i] = 0.0f;
	}

	~Matrix3() {
		delete [] m_elements;
	}

	Matrix3(const Matrix3 &other) {
		m_elements = new float[9];

		(*this) = other;
	}

	Matrix3 &operator=(const Matrix3 &other) {
		for(int i = 0; i < 9; i++)
			m_elements[i] = other.m_elements[i];

		return (*this);
	}

	float *elements() const {
		return m_elements;
	}

private:
	float *m_elements;
};

class Matrix4 {
public:
	static Matrix4 identity() {
		Matrix4 id;

		id.m_elements[0] = 1.0f;
		id.m_elements[5] = 1.0f;
		id.m_elements[10] = 1.0f;
		id.m_elements[15] = 1.0f;

		return id;
	}

	Matrix4() {
		m_elements = new float[16];

		for(int i = 0; i < 16; i++)
			m_elements[i] = 0.0f;
	}

	Matrix4(const Matrix4 &other) {
		m_elements = new float[16];
		(*this) = other;
	}

	Matrix4(float elements[]) {
		m_elements = new float[16];

		for(int i = 0; i < 16; i++)
			m_elements[i] = elements[i];
	}

	~Matrix4() {
		delete [] m_elements;
	}


	Matrix4 &operator=(const Matrix4 &other) {
		for(int i = 0; i < 16; i++)
			m_elements[i] = other.m_elements[i];

		return (*this);
	}

	Matrix4 operator*(const Matrix4 &other) {
		Matrix4 mat;

		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++) {
				float dot = 0.0f;

				for(int k = 0; k < 3; k++)
					dot += (m_elements[k * 3 + i] *
						other.m_elements[j * 3 + k]);

				mat.m_elements[j * 3 + i] = dot;
			}

		return mat;
	}

	float *elements() const {
		return m_elements;
	}

public:
	float *m_elements; // Elements in column major order
};

class Rect2D {
public:
	Vector2 x0y0() const {
		return m_x0y0;
	}

	float width() const {
		return (m_x1y1 - m_x0y0).x;
	}

	float height() const {
		return (m_x1y1 - m_x0y0).y;
	}

private:
	Vector2 m_x0y0;
	Vector2 m_x1y1;
};

class Plane {};

class Face {
public:
	Plane plane;
};

class CFrame {
public:
	CFrame inverse() const {
		CFrame cframe;

		return cframe;
	}

public:
	Matrix3 rotation;
	Vector3 translation;
};

class Ray {
public:
	Vector3 direction() const {
		return m_direction;
	}

	Vector3 origin() const {
		return m_origin;
	}

private:
	Vector3 m_direction;
	Vector3 m_origin;
};

#endif
