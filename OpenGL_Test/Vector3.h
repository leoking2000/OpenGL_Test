#pragma once
#include "Vector2.h"

namespace Math
{
	// 3D dimensional mathematical row vector
	class vec3 : public vec2
	{
	public:
		float z;
	public:
		vec3(); // x = 0, y = 0, z = 0
		vec3(float x, float y, float z);
		vec3(const vec2& a, float z);

		// static Methods //

		// (0 , 0, 0)
		static vec3 zero();

		// (0 , 1, 0)
		static vec3 up();

		// (0 ,-1, 0)
		static vec3 down();

		// (1 , 0, 0)
		static vec3 right();

		// (-1, 0, 0)
		static vec3 left();

		// (0, 0, 1)
		static vec3 forward();

		// (0, 0, -1)
		static vec3 back();

		// returns the distance between the 2 vectors
		static float distance(const vec3& a, const vec3& b);

		// returns the dot product of two vectors
		static float dot(const vec3& a, const vec3& b);

		// returns cross Product of two vectors
		static vec3 cross(const vec3& a, const vec3& b);

		// returns the vector reflected by the vector defined by a normal
		static vec3 reflect(const vec3& a, const vec3& normal);

		// const  Methods //

		//returns the magnitude/lenght squared of the vector
		float sqrLength() const;

		// returns the magnitude/lenght of the vector
		float length() const;

		// returns this vector with a magnitude/lenght of 1 
		vec3 normalized() const;

		// vector equality
		bool operator==(const vec3& a) const;

		// returns the distance between this vector and a
		float distance(const vec3& a) const;

		// returns the dot product of this vector and a
		float dot(const vec3& a) const;

		// Methods //

		// makes this vector with a magnitude/lenght of 1 
		void normalize();

		// operators //

		vec3& operator+=(const vec3& a);
		vec3 operator+(const vec3& a) const;

		vec3& operator-=(const vec3& a);
		vec3 operator-(const vec3& a) const;

		vec3 operator-() const;

		vec3& operator*=(float num);
		vec3 operator*(float num) const;

		vec3& operator/=(float num);
		vec3 operator/(float num) const;

		// Access the x, y, z components using [0], [1], [2] respectively
		float& operator[](int i);


	};

	vec3 operator* (float num, const vec3& a);
	vec3 operator/ (float num, const vec3& a);
}


