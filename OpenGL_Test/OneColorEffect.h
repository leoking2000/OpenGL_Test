#pragma once
#include "math.h"
#include "Mesh.h"

#include "DefaultVertexShader.h"
#include "FlatShadingGS.h"

namespace graphics
{
    class OneColorEffect
    {
    public:
        class Vertex
        {
        public:
            glm::vec3 pos;
            glm::vec3 light{ 0.0f,0.0f,0.0f };
        public:
            Vertex()
            {

            }

            Vertex(const glm::vec3& in_pos)
            {
                pos = in_pos;
            }

            Vertex(glm::vec3 in_pos, glm::vec2 tex, glm::vec3 normal)
            {
                pos = in_pos;
            }

            Vertex(const glm::vec3& in_pos, const Vertex& other)
            {
                pos = in_pos;
            }

            Vertex& operator+=(const Vertex& rhs)
            {
                pos += rhs.pos;

                return *this;
            }
            Vertex operator+(const Vertex& rhs) const
            {
                return Vertex(*this) += rhs;
            }

            Vertex& operator-=(const Vertex& rhs)
            {
                pos -= rhs.pos;

                return *this;
            }
            Vertex operator-(const Vertex& rhs) const
            {
                return Vertex(*this) -= rhs;
            }
            Vertex& operator*=(const glm::mat3x3& mat)
            {
                pos = pos * mat;

                return *this;
            }
            Vertex& operator*=(float rhs)
            {
                pos *= rhs;

                return *this;
            }
            Vertex operator*(float rhs) const
            {
                return Vertex(*this) *= rhs;
            }

            Vertex& operator/=(float rhs)
            {
                pos /= rhs;

                return *this;
            }
            Vertex operator/(float rhs) const
            {
                Vertex out(pos / rhs);

                return out;
            }
        };
    public:
        typedef typename DefaultVertexShader<Vertex> VertexShader;
        typedef typename FlatShadingGS<Vertex> GeometryShader;
    public:
        class PixelShader
        {
        public:
            template<class input>
            Color operator()(const input& vec)
            {
                Color c = color;

                c.r = (uint8_t)Math::clamp(vec.light.x * (float)c.r, 0.0f, 255.0f);
                c.g = (uint8_t)Math::clamp(vec.light.y * (float)c.g, 0.0f, 255.0f);
                c.b = (uint8_t)Math::clamp(vec.light.z * (float)c.b, 0.0f, 255.0f);

                return c;

            }

            void BindColor(const Color& in_color)
            {
                color = in_color;
            }
        private:
            Color color;
        };
    public:
        VertexShader vertex_shader;
        GeometryShader geometry_shader;
        PixelShader pixel_shader;
    };
}