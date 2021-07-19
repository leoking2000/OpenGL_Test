#pragma once
#include "Vector4.h"
#include <string>
#include <cmath>

namespace Math 
{
	// Matrix with size SxS
	template<unsigned int S>
	class mat
	{
	public:
		float data[S][S] = { 0 }; // [row][col]
	public:
		mat() = default;

		// static Methods //

		static mat<S> identity()
		{
			if constexpr (S == 2)
			{
				return {
					1.0f, 0.0f,
					0.0f, 1.0f
				};
			}
			else if constexpr (S == 3)
			{
				return {
					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f
				};
			}
			else if constexpr (S == 4)
			{
				return {
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<S> scale(float s)
		{
			if constexpr (S == 2)
			{
				return {
					   s, 0.0f,
					0.0f,    s
				};
			}
			else if constexpr (S == 3)
			{
				return {
					   s, 0.0f, 0.0f,
					0.0f,    s, 0.0f,
					0.0f, 0.0f,    s
				};
			}
			else if constexpr (S == 4)
			{
				return {
					   s, 0.0f, 0.0f, 0.0f,
					0.0f,    s, 0.0f, 0.0f,
					0.0f, 0.0f,    s, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<2> rotation2D(float theta)
		{
			float sin = sinf(theta);
			float cos = cosf(theta);

			return {
				 cos,  sin,
				-sin,  cos
			};
		}

		static mat<S> rotationX(float theta)
		{
			float sin = sinf(theta);
			float cos = cosf(theta);

			if constexpr (S == 3)
			{
				return {
					1.0f, 0.0f, 0.0f,
					0.0f,  cos,  sin,
					0.0f, -sin,  cos
				};
			}
			else if constexpr (S == 4)
			{
				return {
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f,  cos,  sin, 0.0f,
					0.0f, -sin,  cos, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<S> rotationY(float theta)
		{
			float sin = sinf(theta);
			float cos = cosf(theta);

			if constexpr (S == 3)
			{
				return {
					 cos, 0.0f, -sin,
					0.0f, 1.0f, 0.0f,
					 sin, 0.0f,  cos
				};
			}
			else if constexpr (S == 4)
			{
				return {
					 cos, 0.0f, -sin, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					 sin, 0.0f,  cos, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<S> rotationZ(float theta)
		{
			float sin = sinf(theta);
			float cos = cosf(theta);

			if constexpr (S == 3)
			{
				return {
					 cos, sin,   0.0f,
					-sin, cos,   0.0f,
					 0.0f, 0.0f, 1.0f
				};
			}
			else if constexpr (S == 4)
			{
				return {
					 cos,  sin, 0.0f, 0.0f,
					-sin,  cos, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};
			}
			else
			{
				static_assert(false, "matix with unsupported size");
			}
		}

		static mat<3> Translation2D(float x, float y)
		{
			return {
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				   x,    y, 1.0f
			};
		}

		static mat<4> Translation3D(float x, float y, float z)
		{
			return {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				   x,    y,    z, 1.0f
			};
		}

		// Methods //

		mat<S> transpose() const
		{
			mat<S> r;
			for (int row = 0; row < S; row++)
			{
				for (int col = 0; col < S; col++)
				{
					r[row][col] = data[col][row];
				}
			}

			return r;
		}

		// operators

		mat<S>& operator=(const mat<S>& a)
		{
			std::memcpy(data, a.data, sizeof(data));
			return *this;
		}

		mat<S>& operator*=(float rhs)
		{
			for (auto& row : data)
			{
				for (auto& e : row)
				{
					e *= rhs;
				}
			}
			return *this;
		}
		mat<S> operator*(float rhs) const
		{
			mat<S> result = *this;
			return result *= rhs;
		}


		mat<S>& operator*=(const mat<S>& rhs)
		{
			return *this = *this * rhs;
		}
		mat<S> operator*(const mat<S>& rhs) const
		{
			mat<S> result;
			for (int j = 0; j < S; j++)
			{
				for (int k = 0; k < S; k++)
				{
					float sum = 0.0f;
					for (int i = 0; i < S; i++)
					{
						sum += data[j][i] * rhs.data[i][k];
					}
					result.data[j][k] = sum;
				}
			}
			return result;
		}

	};

	static vec2 operator*(const vec2& lhs, const mat<2>& rhs)
	{
		return {
			lhs.x * rhs.data[0][0] + lhs.y * rhs.data[1][0],
			lhs.x * rhs.data[0][1] + lhs.y * rhs.data[1][1]
		};
	}
	static vec2& operator*=(vec2& lhs, const mat<2>& rhs)
	{
		return lhs = lhs * rhs;
	}

	static vec3 operator*(const vec3& lhs, const mat<3>& rhs)
	{
		return {
			lhs.x * rhs.data[0][0] + lhs.y * rhs.data[1][0] + lhs.z * rhs.data[2][0],
			lhs.x * rhs.data[0][1] + lhs.y * rhs.data[1][1] + lhs.z * rhs.data[2][1],
			lhs.x * rhs.data[0][2] + lhs.y * rhs.data[1][2] + lhs.z * rhs.data[2][2]
		};
	}
	static vec3& operator*=(vec3& lhs, const mat<3>& rhs)
	{
		return lhs = lhs * rhs;
	}


	static vec4 operator*(const vec4& lhs, const mat<4>& rhs)
	{
		return{
			lhs.x * rhs.data[0][0] + lhs.y * rhs.data[1][0] + lhs.z * rhs.data[2][0] + lhs.w * rhs.data[3][0],
			lhs.x * rhs.data[0][1] + lhs.y * rhs.data[1][1] + lhs.z * rhs.data[2][1] + lhs.w * rhs.data[3][1],
			lhs.x * rhs.data[0][2] + lhs.y * rhs.data[1][2] + lhs.z * rhs.data[2][2] + lhs.w * rhs.data[3][2],
			lhs.x * rhs.data[0][3] + lhs.y * rhs.data[1][3] + lhs.z * rhs.data[2][3] + lhs.w * rhs.data[3][3]
		};
	}
	static vec4& operator*=(vec4& lhs, const mat<4>& rhs)
	{
		return lhs = lhs * rhs;
	}

	typedef mat<2> mat2;
	typedef mat<3> mat3;
	typedef mat<4> mat4;
}