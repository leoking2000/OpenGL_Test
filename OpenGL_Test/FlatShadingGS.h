#pragma once
#include "math.h"
#include <vector>
#include "Colors.h"

template<class Vertex>
class FlatShadingGS
{
public:
    class Output
    {
    public:
        Vertex vec;
        glm::vec3 pos;
        glm::vec3 light;
    public:

        Output(const Vertex& in_vec,const glm::vec3& in_light)
        {
            vec = in_vec;
            light = in_light;
            pos = in_vec.pos;
        }

        Output& operator+=(const Output& rhs)
        {
            vec += rhs.vec;
            light += rhs.light;

            pos = vec.pos;

            return *this;
        }
        Output operator+(const Output& rhs) const
        {
            return Output(*this) += rhs;
        }

        Output& operator-=(const Output& rhs)
        {
            vec -= rhs.vec;
            light -= rhs.light;

            pos = vec.pos;

            return *this;
        }
        Output operator-(const Output& rhs) const
        {
            return Output(*this) -= rhs;
        }

        Output& operator*=(float rhs)
        {
            vec *= rhs;
            light *= rhs;

            pos = vec.pos;

            return *this;
        }
        Output operator*(float rhs) const
        {
            return Output(*this) *= rhs;
        }

        Output& operator/=(float rhs)
        {
            vec /= rhs;
            light /= rhs;

            pos = vec.pos;

            return *this;
        }
        Output operator/(float rhs) const
        {
            Output out(pos / rhs, light / rhs);

            return out;
        }
    };
public:
	std::vector<Output> operator()(const Vertex& in0, const Vertex& in1, const Vertex& in2, size_t triangle_index) const
	{
        glm::vec3 vec0 = in0.pos;
        glm::vec3 vec1 = in1.pos;
        glm::vec3 vec2 = in2.pos;

		glm::vec3 normal = glm::cross(vec1 + vec0, vec2 + vec0);
        normal = glm::normalize(normal);
		
        glm::vec3 light = ( diffuse * std::max(0.0f , -glm::dot(light_dir, normal)) ) + ambient;

        light.x = Math::clamp(light.x, 0.0f, 1.0f);
        light.y = Math::clamp(light.y, 0.0f, 1.0f);
        light.z = Math::clamp(light.z, 0.0f, 1.0f);
		

        Output out0(in0, light);
        Output out1(in1, light);
        Output out2(in2, light);
		
		return{ out0,out1,out2 };
	}
public:
	glm::vec3 light_dir{ 0.0f, 0.0f, 1.0f };

    glm::vec3 diffuse{ 1.0f,1.0f,1.0f };
    glm::vec3 ambient{ 0.1f,0.1f,0.1f };
};