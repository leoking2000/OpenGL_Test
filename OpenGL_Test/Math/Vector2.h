#pragma once

namespace Math
{
	// 2D dimensional mathematical row vector
	class vec2
	{
	public:
		float x;
		float y;
	public:
		vec2(); // x = 0, y = 0
		vec2(float x, float y);

		// static Methods //

		// (0 , 0)
		static vec2 zero();

		// (0 , 1)
		static vec2 up();

		// (0 ,-1)
		static vec2 down();

		// (1 , 0)
		static vec2 right();

		// (-1, 0)
		static vec2 left();

		// returns the distance between the 2 vectors
		static float distance(const vec2& a, const vec2& b);

		// returns the dot product of two vectors
		static float dot(const vec2& a, const vec2& b);

		// returns the vector reflected by the vector defined by a normal
		static vec2 reflect(const vec2& a, const vec2& normal);

		// const  Methods //

		//returns the magnitude/lenght squared of the vector
		float sqrLength() const;

		// returns the magnitude/lenght of the vector
		float length() const;

		// returns this vector with a magnitude/lenght of 1 
		vec2 normalized() const;

		// vector equality
		bool operator==(const vec2& a) const;

		// returns the distance between this vector and a
		float distance(const vec2& a) const;

		// returns the dot product of this vector and a
		float dot(const vec2& a) const;

		// Methods //

		// makes this vector with a magnitude/lenght of 1 
		void normalize();

		// operators //

		vec2& operator+=(const vec2& a);
		vec2 operator+(const vec2& a) const;

		vec2& operator-=(const vec2& a);
		vec2 operator-(const vec2& a) const;

		vec2& operator*=(float num);
		vec2 operator*(float num) const;

		vec2& operator/=(float num);
		vec2 operator/(float num) const;

		// access the x or y component using [0] or [1] respectively
		float& operator[](int i);


	};

	vec2 operator* (float num,  const vec2& a);
	vec2 operator/ (float num,  const vec2& a);
}

