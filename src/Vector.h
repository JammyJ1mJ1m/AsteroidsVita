#pragma once
#include <iostream>
#include <cmath>
#include <iostream>

template<typename T, int N>
class Vector
{
	T _elements[N];
public:

	const T& x = _elements[0];
	const T& y = _elements[1];
	const T& z = _elements[2];
	const T& w = _elements[3];

	Vector() {
		for (int i = 0; i < N; ++i)
			_elements[i] = T();
	}

	Vector(const T values[]) {
		for (int i = 0; i < N; ++i)
			_elements[i] = values[i];
	}

	Vector(const Vector& copy) {
		for (int i = 0; i < N; ++i)
			_elements[i] = copy._elements[i];
	}

	Vector(const std::initializer_list<T>& list) {
		int i = 0;
		for (const auto& element : list) {
			if (i >= N) break;
			_elements[i++] = element;
		}
	}

	Vector(const T x, const T y) {
		_elements[0] = x;
		_elements[1] = y;
	}

	//Vector(const T x, const T y, const T z) {
	//	_elements[0] = x;
	//	_elements[1] = y;
	//	_elements[2] = z;
	//}

	Vector(const T x, const T y, const T z, const T w = 0) {
		_elements[0] = x;
		_elements[1] = y;
		_elements[2] = z;
		_elements[3] = w;
	}

	Vector& operator=(const Vector& copy) {
		if (this != &copy) {
			for (int i = 0; i < N; ++i)
				_elements[i] = copy._elements[i];
		}
		return *this;
	}

	Vector operator+(const Vector& other) const {
		Vector result;
		for (int i = 0; i < N; ++i)
			result._elements[i] = _elements[i] + other._elements[i];
		return result;
	}

	Vector operator-(const Vector& other) const {
		Vector result;
		for (int i = 0; i < N; ++i)
			result._elements[i] = _elements[i] - other._elements[i];
		return result;
	}

	Vector& operator*(T scalar) {
		for (int i = 0; i < N; ++i)
			_elements[i] *= scalar;
		return *this;
	}

	Vector& operator+=(const Vector& other) {
		for (int i = 0; i < N; ++i)
			_elements[i] += other._elements[i];
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec) {
		for (int i = 0; i < N; ++i) {
			os << vec._elements[i];
			if (i < N - 1) {
				os << " ";  // Separate elements by space
			}
		}
		return os;
	}

	T GetX() const { return _elements[0]; }
	T GetY() const { return _elements[1]; }
	T GetZ() const { return _elements[2]; }
	T GetW() const { return _elements[3]; }

	void SetX(T value) { _elements[0] = value; }
	void SetY(T value) { _elements[1] = value; }
	void SetZ(T value) { _elements[2] = value; }
	void SetW(T value) { _elements[3] = value; }

	T Length() const {
		T sumSquares = T();
		for (int i = 0; i < N; ++i)
			sumSquares += _elements[i] * _elements[i];
		return std::sqrt(sumSquares);
	}

	void Normalize() {
		T len = Length();
		if (len != T()) {
			for (int i = 0; i < N; ++i)
				_elements[i] /= len;
		}
	}

	virtual ~Vector() {}
};

typedef Vector<float, 2> Vector2f;
typedef Vector<float, 3> Vector3f;
typedef Vector<float, 4> Vector4f;

typedef Vector<double, 2> Vector2d;
typedef Vector<double, 3> Vector3d;
typedef Vector<double, 4> Vector4d;

typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;
typedef Vector<int, 4> Vector4i;