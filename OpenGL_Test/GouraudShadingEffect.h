#pragma once
#include "math.h"
#include "Mesh.h"

#include "DefaultGeometryShader.h"
#include "GouraudShadingVS.h"


namespace graphics
{
    class GouraudShadingEffect
    {
    public:
        class Vertex
        {
        public:
            glm::vec3 pos;
            glm::vec3 n;
        public:
            Vertex()
            {
                pos = glm::vec3(0.0f, 0.0f, 0.0f);
                n = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            Vertex(const glm::vec3& in_pos)
            {
                pos = in_pos;
                n = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            Vertex(glm::vec3 in_pos, glm::vec3 tex)
            {
                pos = in_pos;
                n = tex;
            }

            Vertex(const glm::vec3& in_pos, const Vertex& other)
            {
                pos = in_pos;
                n = other.n;
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

            Vertex& operator*=(float rhs)
            {
                pos *= rhs;

                return *this;
            }
            Vertex& operator*=(const glm::mat3x3& mat)
            {
                pos = pos * mat;
                n = n * mat;


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
        typedef typename GouraudShadingVS<Vertex> VertexShader;
        typedef typename DefaultGeometryShader<VertexShader::Output> GeometryShader;
        class PixelShader
        {
        public:
            Color operator()(const VertexShader::Output& vec)
            {
                Color c = color;

                c.r = (uint8_t)Math::clamp(vec.color.x * (float)c.r, 0.0f, 255.0f);
                c.g = (uint8_t)Math::clamp(vec.color.y * (float)c.g, 0.0f, 255.0f);
                c.b = (uint8_t)Math::clamp(vec.color.z * (float)c.b, 0.0f, 255.0f);

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