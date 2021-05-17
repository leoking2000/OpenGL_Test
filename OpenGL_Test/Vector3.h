#pragma once
#include "Vector2.h"

template<typename T>
class Vector3D_t : public Vector2D_t<T>
{
public:
	T x = (T)0;
	T y = (T)0;
	T z = (T)0;
public:
	Vector3D_t() = default;
	Vector3D_t(T in_x, T in_y, T in_z);

	inline bool operator==(const Vector3D_t<T>& vec) const;
	inline bool operator!=(const Vector3D_t<T>& vec) const;

	inline Vector3D_t<T> operator+(const Vector3D_t<T>& vec) const;
	inline Vector3D_t<T>& operator+=(const Vector3D_t<T>& vec);
	inline Vector3D_t<T> operator+(T scaler) const;
	inline Vector3D_t<T>& operator+=(T scaler);

	inline Vector3D_t<T> operator-() const;
	inline Vector3D_t<T> operator-(const Vector3D_t<T>& vec) const;
	inline Vector3D_t<T> operator-(T scaler) const;
	inline Vector3D_t<T>& operator-=(const Vector3D_t<T>& vec);
	inline Vector3D_t<T>& operator-=(T scaler);

	inline Vector3D_t<T> operator/(T scaler) const;
	inline Vector3D_t<T>& operator/=(T scaler);

	inline float operator*(const Vector3D_t<T>& vec) const; // dot product
	inline Vector3D_t<T> operator*(T scaler) const;
	inline Vector3D_t<T>& operator*=(T scaler);

	operator Vector2D_t<T>()
	{
		return Vector2D_t<T>(x, y);
	}

	static Vector3D_t<T> cross(const Vector3D_t<T>& a, const Vector3D_t<T>& b)
	{
		Vector3D_t<T> out;

		out.x = a.y * b.z - a.z * b.y;
		out.y = a.z * b.x - a.x * b.z;
		out.z = a.x * b.y - a.y * b.x;

		return out;
	}

	void RotateZ(double radians);
	T GetLengthSq() const;
	T GetLength() const;
	T GetDistanceSq(const Vector3D_t<T>& vec) const;
	T GetDistance(const Vector3D_t<T>& vec) const;
	Vector3D_t  GetNormalized() const;
	Vector3D_t& Normalize();

};

template<typename T>
Vector3D_t<T>::Vector3D_t(T in_x, T in_y, T in_z) : x(in_x), y(in_y), z(in_z) {}


////////////////// == != ////////////////////////////
template<typename T>
inline bool Vector3D_t<T>::operator==(const Vector3D_t<T>& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

template<typename T>
inline bool Vector3D_t<T>::operator!=(const Vector3D_t<T>& vec) const
{
	return !(*this == vec);
}

//////////////////// + += ///////////////////////
template<typename T>
inline Vector3D_t<T> Vector3D_t<T>::operator+(const Vector3D_t<T>& vec) const
{
	return Vector3D_t<T>(x + vec.x, y + vec.y, z + vec.z);
}

template<typename T>
inline Vector3D_t<T>& Vector3D_t<T>::operator+=(const Vector3D_t<T>& vec)
{
	*this = *this + vec;
	return *this;
}

template<typename T>
inline Vector3D_t<T> Vector3D_t<T>::operator+(T scaler) const
{
	return Vector3D_t<T>(x + scaler, y + scaler, z + scaler);
}

template<typename T>
inline Vector3D_t<T> operator+(T scaler, const Vector3D_t<T>& vec)
{
	return Vector3D_t<T>(vec.x + scaler, vec.y + scaler, vec.z + scaler);
}

template<typename T>
inline Vector3D_t<T>& Vector3D_t<T>::operator+=(T scaler)
{
	x += scaler;
	y += scaler;
	z += scaler;
	return *this;
}

//////////////// - -= /////////////////////////

template<typename T>
inline Vector3D_t<T> Vector3D_t<T>::operator-() const
{
	return Vector3D_t<T>(-x,-y,-z);
}

template<typename T>
inline Vector3D_t<T> Vector3D_t<T>::operator-(const Vector3D_t<T>& vec) const
{
	return Vector3D_t<T>(x - vec.x, y - vec.y, z - vec.z);
}

template<typename T>
inline Vector3D_t<T> Vector3D_t<T>::operator-(T scaler) const
{
	return Vector3D_t<T>(x - scaler, y - scaler, z - scaler);
}

template<typename T>
inline Vector3D_t<T> operator-(T scaler, const Vector3D_t<T>& vec)
{
	return Vector3D_t<T>(scaler - vec.x, scaler - vec.y, scaler - vec.z);
}

template<typename T>
inline Vector3D_t<T>& Vector3D_t<T>::operator-=(const Vector3D_t<T>& vec)
{
	*this = *this - vec;
	return *this;
}

template<typename T>
inline Vector3D_t<T>& Vector3D_t<T>::operator-=(T scaler)
{
	x -= scaler;
	y -= scaler;
	z -= scaler;
	return *this;
}

/////////////// / /= //////////////////////////////

template<typename T>
inline Vector3D_t<T> Vector3D_t<T>::operator/(T scaler) const
{
	return Vector3D_t<T>(x / scaler, y / scaler, z / scaler);
}

template<typename T>
inline Vector3D_t<T>& Vector3D_t<T>::operator/=(T scaler)
{
	x /= scaler;
	y /= scaler;
	z /= scaler;
	return *this;
}

/////////////////// * //////////////////////////////

template<typename T>
inline float Vector3D_t<T>::operator*(const Vector3D_t<T>& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

template<typename T>
inline Vector3D_t<T> Vector3D_t<T>::operator*(T scaler) const
{
	return Vector3D_t(x * scaler, y * scaler, z * scaler);
}

template<typename T>
inline Vector3D_t<T> operator*(T scaler, const Vector3D_t<T>& vec)
{
	return Vector3D_t<T>(vec.x * scaler, vec.y * scaler, vec.z * scaler);
}

template<typename T>
inline Vector3D_t<T>& Vector3D_t<T>::operator*=(T scaler)
{
	x *= scaler;
	y *= scaler;
	z *= scaler;
	return *this;
}

/////////////////////////////////////////////////

template<typename T>
inline void Vector3D_t<T>::RotateZ(double radians)
{
	x = T(x * std::cos(radians) - y * std::sin(radians));
	y = T(x * std::sin(radians) + y * std::cos(radians));
}

template<typename T>
T Vector3D_t<T>::GetLengthSq() const
{
	return x * x + y * y + z * z;
}

template<typename T>
T Vector3D_t<T>::GetLength() const
{
	return T(std::sqrt(GetLengthSq()));
}

template<typename T>
T Vector3D_t<T>::GetDistanceSq(const Vector3D_t<T>& vec) const
{
	return (*this - vec).GetLengthSq();
}

template<typename T>
inline T Vector3D_t<T>::GetDistance(const Vector3D_t<T>& vec) const
{
	return (*this - vec).GetLength();
}

template<typename T>
Vector3D_t<T> Vector3D_t<T>::GetNormalized() const
{
	const T len = GetLength();
	if ((double)len == 0.0) return *this;
	
	return Vector3D_t<T>(T(x / len), T(y / len), T(z / len));
}

template<typename T>
Vector3D_t<T>& Vector3D_t<T>::Normalize()
{
	const T len = GetLength();
	if ((double)len == 0.0) return *this;

	*this = *this / len;

	return *this;
}

typedef Vector3D_t<float>  Vector3;
typedef Vector3D_t<double> Vector3double;
typedef Vector3D_t<int>    Vector3int;
