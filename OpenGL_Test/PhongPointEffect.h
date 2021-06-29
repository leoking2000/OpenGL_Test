#pragma once
#include "math.h"
#include "Transform.h"
#include "Colors.h"
#include "DefaultGeometryShader.h"
#include "VertexPN.h"

namespace graphics
{
    class PhongPointEffect
    {
    public:
        typedef VertexPN Vertex;
    public:
        class VertexShader
        {
        public:
            class Output
            {
            public:
                glm::vec3 pos;
                glm::vec3 n;
                glm::vec3 worldPos;
            public:
                Output()
                {
                    pos = glm::vec3(0.0f, 0.0f, 0.0f);
                    n = glm::vec3(0.0f, 0.0f, 0.0f);
                    worldPos = glm::vec3(0.0f, 0.0f, 0.0f);
                }

                Output(const glm::vec3& in_pos)
                {
                    pos = in_pos;
                    worldPos = in_pos;
                    n = glm::vec3(0.0f, 0.0f, 0.0f);
                }

                Output(glm::vec3 in_pos, glm::vec3 norm, glm::vec3 world)
                {
                    pos = in_pos;
                    n = norm;
                    worldPos = world;
                }

                Output(const glm::vec3& in_pos, const Output& other)
                {
                    pos = in_pos;
                    n = other.n;
                    worldPos = other.worldPos;
                }

                Output& operator+=(const Output& rhs)
                {
                    pos += rhs.pos;
                    n += rhs.n;
                    worldPos += rhs.worldPos;

                    return *this;
                }
                Output operator+(const Output& rhs) const
                {
                    return Output(*this) += rhs;
                }

                Output& operator-=(const Output& rhs)
                {
                    pos -= rhs.pos;
                    n -= rhs.n;
                    worldPos -= rhs.worldPos;

                    return *this;
                }
                Output operator-(const Output& rhs) const
                {
                    return Output(*this) -= rhs;
                }

                Output& operator*=(float rhs)
                {
                    pos *= rhs;
                    n *= rhs;
                    worldPos *= rhs;

                    return *this;
                }
                Output& operator*=(const glm::mat3x3& mat)
                {
                    pos = pos * mat;
                    n = n * mat;
                    worldPos = worldPos * mat;

                    return *this;
                }
                Output operator*(float rhs) const
                {
                    return Output(*this) *= rhs;
                }

                Output& operator/=(float rhs)
                {
                    pos /= rhs;
                    n /= rhs;
                    worldPos /= rhs;

                    return *this;
                }
                Output operator/(float rhs) const
                {
                    Output out(pos / rhs, n / rhs, worldPos / rhs);

                    return out;
                }
            };
        public:
            void BindTransform(graphics::Transform& transform_in)
            {
                transform = &transform_in;
            }
            Output operator()(const Vertex& in) const
            {
                Output out(in.pos, in.n, in.pos);
                graphics::Transform::TransformVertex(out, *transform);

                return out;
            }
        private:
            graphics::Transform* transform;
        };
    public:
        typedef typename DefaultGeometryShader<VertexShader::Output> GeometryShader;
    public:
        class PixelShader
        {
        public:
            Color operator()(const VertexShader::Output& vec)
            {
                Color c = color;

                const glm::vec3 delta = light_Pos - vec.worldPos;
                const float     dist = glm::length(delta);
                const glm::vec3 dir = glm::normalize(delta);

                const float i = 1.0f / (A * dist * dist + B * dist + C);

                glm::vec3 light = diffuse * i * std::max(0.0f, glm::dot(dir, glm::normalize(vec.n)));
                light.x = Math::clamp(light.x + ambient.x, 0.0f, 1.0f);
                light.y = Math::clamp(light.y + ambient.y, 0.0f, 1.0f);
                light.z = Math::clamp(light.z + ambient.z, 0.0f, 1.0f);

                c.r = (uint8_t)Math::clamp(light.x * (float)c.r, 0.0f, 255.0f);
                c.g = (uint8_t)Math::clamp(light.y * (float)c.g, 0.0f, 255.0f);
                c.b = (uint8_t)Math::clamp(light.z * (float)c.b, 0.0f, 255.0f);

                return c;
            }
            void BindColor(const Color& in_color)
            {
                color = in_color;
            }
        public:
            glm::vec3 light_Pos{ 0.0f, 0.0f, 1.0f };
            glm::vec3 diffuse{ 1.0f,1.0f,1.0f };
            glm::vec3 ambient{ 0.1f,0.1f,0.1f };
            float A = 0.44f;
            float B = 0.35f;
            float C = 1.0f;
        private:
            Color color;
        };
    public:
        VertexShader vertex_shader;
        GeometryShader geometry_shader;
        PixelShader pixel_shader;
    };
}
