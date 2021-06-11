#pragma once
#include "math.h"
#include "Mesh.h"
#include "Colors.h"
#include "DefaultVertexShader.h"
#include "DefaultGeometryShader.h"

namespace graphics
{
    class InterColorEffect
    {
    public:
        class Vertex
        {
        public:
            glm::vec3 pos;
            glm::vec3 color;
        public:
            Vertex()
            {
                pos = glm::vec3(0.0f, 0.0f, 0.0f);
                color = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            Vertex(const glm::vec3& in_pos)
            {
                pos = in_pos;
                color = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            Vertex(glm::vec3 in_pos, glm::vec3 tex)
            {
                pos = in_pos;
                color = tex;
            }

            Vertex(const glm::vec3& in_pos, const Vertex& other)
            {
                pos = in_pos;
                color = other.color;
            }

            Vertex& operator+=(const Vertex& rhs)
            {
                pos += rhs.pos;
                color += rhs.color;

                return *this;
            }
            Vertex operator+(const Vertex& rhs) const
            {
                return Vertex(*this) += rhs;
            }

            Vertex& operator-=(const Vertex& rhs)
            {
                pos -= rhs.pos;
                color -= rhs.color;

                return *this;
            }
            Vertex operator-(const Vertex& rhs) const
            {
                return Vertex(*this) -= rhs;
            }

            Vertex& operator*=(float rhs)
            {
                pos *= rhs;
                color *= rhs;

                return *this;
            }
            Vertex& operator*=(const glm::mat3x3& mat)
            {
                pos = pos * mat;

                return *this;
            }
            Vertex operator*(float rhs) const
            {
                return Vertex(*this) *= rhs;
            }

            Vertex& operator/=(float rhs)
            {
                pos /= rhs;
                color /= rhs;

                return *this;
            }
            Vertex operator/(float rhs) const
            {
                Vertex out(pos / rhs);
                out.color = color / rhs;

                return out;
            }
        };
    public:
        typedef typename DefaultVertexShader<Vertex> VertexShader;
        typedef typename DefaultGeometryShader<Vertex> GeometryShader;
        class PixelShader
        {
        public:
            template<class input>
            Color operator()(const input& vec)
            {
                Color c = { uint8_t(vec.color.x * 255.0f), uint8_t(vec.color.y * 255.0f), uint8_t(vec.color.z * 255.0f) };

                return c;
            }
        };
    public:
        VertexShader vertex_shader;
        GeometryShader geometry_shader;
        PixelShader pixel_shader;
    };

    static Mesh<InterColorEffect::Vertex> MakeCube_InterColorEffect(float size)
    {
        Mesh<InterColorEffect::Vertex> cube;

        const float s = size / 2.0f;

        cube.vartices.emplace_back(InterColorEffect::Vertex{ { -s, -s, -s},{0.0f, 0.0f, 0.0f} });
        cube.vartices.emplace_back(InterColorEffect::Vertex{ { -s,  s, -s},{0.0f, 1.0f, 0.0f} });
        cube.vartices.emplace_back(InterColorEffect::Vertex{ {  s,  s, -s},{1.0f, 1.0f, 0.0f} });
        cube.vartices.emplace_back(InterColorEffect::Vertex{ {  s, -s, -s},{1.0f, 0.0f, 0.0f} });
        cube.vartices.emplace_back(InterColorEffect::Vertex{ {  s,  s,  s},{1.0f, 1.0f, 1.0f} });
        cube.vartices.emplace_back(InterColorEffect::Vertex{ {  s, -s,  s},{1.0f, 0.0f, 1.0f} });
        cube.vartices.emplace_back(InterColorEffect::Vertex{ { -s,  s,  s},{0.0f, 1.0f, 1.0f} });
        cube.vartices.emplace_back(InterColorEffect::Vertex{ { -s, -s,  s},{0.0f, 0.0f, 1.0f} });

        // Forward
        cube.indices.emplace_back(0);
        cube.indices.emplace_back(1);
        cube.indices.emplace_back(2);

        cube.indices.emplace_back(0);
        cube.indices.emplace_back(2);
        cube.indices.emplace_back(3);

        // EAST
        cube.indices.emplace_back(3);
        cube.indices.emplace_back(2);
        cube.indices.emplace_back(4);

        cube.indices.emplace_back(3);
        cube.indices.emplace_back(4);
        cube.indices.emplace_back(5);

        // BACK
        cube.indices.emplace_back(5);
        cube.indices.emplace_back(4);
        cube.indices.emplace_back(6);

        cube.indices.emplace_back(5);
        cube.indices.emplace_back(6);
        cube.indices.emplace_back(7);

        // WEST
        cube.indices.emplace_back(7);
        cube.indices.emplace_back(6);
        cube.indices.emplace_back(1);

        cube.indices.emplace_back(7);
        cube.indices.emplace_back(1);
        cube.indices.emplace_back(0);

        // NORTH
        cube.indices.emplace_back(1);
        cube.indices.emplace_back(6);
        cube.indices.emplace_back(4);

        cube.indices.emplace_back(1);
        cube.indices.emplace_back(4);
        cube.indices.emplace_back(2);

        // SOUTH
        cube.indices.emplace_back(5);
        cube.indices.emplace_back(7);
        cube.indices.emplace_back(0);

        cube.indices.emplace_back(5);
        cube.indices.emplace_back(0);
        cube.indices.emplace_back(3);

        return cube;
    }
}