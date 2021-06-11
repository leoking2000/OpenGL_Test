#pragma once
#include "math.h"
#include "Texture.h"
#include "Make_Shape.h"

#include "DefaultVertexShader.h"
#include "FlatShadingGS.h"

namespace graphics
{
    class TextureEffect
    {
    public:
        class Vertex
        {
        public:
            glm::vec3 pos;
            glm::vec3 n;
            glm::vec2 texCord;
            glm::vec3 light{0.0f,0.0f,0.0f};
        public:
            Vertex()
            {

            }

            Vertex(const glm::vec3& in_pos)
            {
                pos = in_pos;
                texCord = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            Vertex(glm::vec3 in_pos,glm::vec2 tex,glm::vec3 normal)
            {
                pos = in_pos;
                texCord = tex;
                n = normal;
            }

            Vertex(const glm::vec3& in_pos, const Vertex& other)
            {
                pos = in_pos;
                texCord = other.texCord;
                n = other.n;
            }

            Vertex& operator+=(const Vertex& rhs)
            {
                pos += rhs.pos;
                texCord += rhs.texCord;
                

                return *this;
            }
            Vertex operator+(const Vertex& rhs) const
            {
                return Vertex(*this) += rhs;
            }

            Vertex& operator-=(const Vertex& rhs)
            {
                pos -= rhs.pos;
                texCord -= rhs.texCord;

                return *this;
            }
            Vertex operator-(const Vertex& rhs) const
            {
                return Vertex(*this) -= rhs;
            }
            Vertex& operator*=(const glm::mat3x3& mat)
            {
                pos = pos * mat;
                n = n * mat;
                glm::normalize(n);

                return *this;
            }
            Vertex& operator*=(float rhs)
            {
                pos *= rhs;
                texCord *= rhs;
                n *= rhs;
                glm::normalize(n);

                return *this;
            }
            Vertex operator*(float rhs) const
            {
                return Vertex(*this) *= rhs;
            }

            Vertex& operator/=(float rhs)
            {
                pos /= rhs;
                texCord /= rhs;
                n /= rhs;
                glm::normalize(n);

                return *this;
            }
            Vertex operator/(float rhs) const
            {
                Vertex out(pos / rhs);
                out.texCord = texCord / rhs;

                return out;
            }
        };
    public:
        typedef typename DefaultVertexShader<Vertex> VertexShader;
    public:
        class GeometryShader
        {
        public:
            typedef typename Vertex Output;
        public:
            std::vector<Output> operator()(Vertex& in0, Vertex& in1, Vertex& in2, size_t triangle_index) const
            {

                glm::vec3 light = diffuse * std::max(0.0f, -glm::dot(light_dir, in0.n));

            
                light.x = Math::clamp(light.x + ambient.x, 0.0f, 1.0f);
                light.y = Math::clamp(light.y + ambient.y, 0.0f, 1.0f);
                light.z = Math::clamp(light.z + ambient.z, 0.0f, 1.0f);
        
                in0.light = light;
                in1.light = light;
                in2.light = light;

                return{ in0,in1,in2 };
            }
        public:
            glm::vec3 light_dir{ 0.0f, 0.0f, 1.0f };

            glm::vec3 diffuse{ 1.0f,1.0f,1.0f };
            glm::vec3 ambient{ 0.1f,0.1f,0.1f };
        };
    public:
        class PixelShader
        {
        public:
            template<class input>
            Color operator()(const input& vec)
            {
                Color c = texture->GetPixel((int)std::fmod(vec.texCord.x * tex_width + 0.5f, tex_xclamp),
                                            (int)std::fmod(vec.texCord.y * tex_height + 0.5f, tex_yclamp));

                c.r = (uint8_t)Math::clamp(vec.light.x * (float)c.r, 0.0f , 255.0f);
                c.g = (uint8_t)Math::clamp(vec.light.y * (float)c.g, 0.0f , 255.0f);
                c.b = (uint8_t)Math::clamp(vec.light.z * (float)c.b, 0.0f , 255.0f);

                return c;

            }

            void BindTexture(const Texture& tex)
            {
                texture = &tex;
                tex_width = float(texture->GetWidth());
                tex_height = float(texture->GetHeight());
                tex_xclamp = tex_width - 1.0f;
                tex_yclamp = tex_height - 1.0f;

            }
        private:
            const Texture* texture;
            float tex_width;
            float tex_height;
            float tex_xclamp;
            float tex_yclamp;
        };
    public:
        VertexShader vertex_shader;
        GeometryShader geometry_shader;
        PixelShader pixel_shader;
    };

    static Mesh<TextureEffect::Vertex> MakeCube_TextureEffect(float size)
    {
        Mesh<TextureEffect::Vertex> cube;

        const float s = size / 2.0f;

        // Forward
        cube.vartices.push_back({ glm::vec3(-s, -s, -s), glm::vec2(0.0f, 0.0f), glm::vec3{0.0f, 0.0f, -1.0f} });// 0 0 
        cube.vartices.push_back({ glm::vec3(-s, s, -s), glm::vec2(0.0f, 1.0f), glm::vec3{0.0f, 0.0f, -1.0f} });// 1 1
        cube.vartices.push_back({ glm::vec3(s, s, -s), glm::vec2(1.0f, 1.0f), glm::vec3{0.0f, 0.0f, -1.0f} });// 2 2 
        cube.vartices.push_back({ glm::vec3(s, -s, -s), glm::vec2(1.0f, 0.0f), glm::vec3{0.0f, 0.0f, -1.0f} });// 3 3

        cube.indices.emplace_back(0);
        cube.indices.emplace_back(1);
        cube.indices.emplace_back(2);

        cube.indices.emplace_back(0);
        cube.indices.emplace_back(2);
        cube.indices.emplace_back(3);

        // EAST
        cube.vartices.push_back({glm::vec3(s, s, -s), glm::vec2(0.0f, 1.0f), glm::vec3{1.0f, 0.0f, 0.0f}});// 2 4
        cube.vartices.push_back({glm::vec3(s, -s, -s),glm::vec2(0.0f, 0.0f), glm::vec3{1.0f, 0.0f, 0.0f}});// 3 5
        cube.vartices.push_back({glm::vec3(s, s, s),  glm::vec2(1.0f, 1.0f), glm::vec3{1.0f, 0.0f, 0.0f}});// 4 6
        cube.vartices.push_back({glm::vec3(s, -s, s), glm::vec2(1.0f, 0.0f), glm::vec3{1.0f, 0.0f, 0.0f}});// 5 7

        cube.indices.emplace_back(5);
        cube.indices.emplace_back(4);
        cube.indices.emplace_back(6);

        cube.indices.emplace_back(5);
        cube.indices.emplace_back(6);
        cube.indices.emplace_back(7);

        // BACK
        cube.vartices.push_back({glm::vec3(s, s, s), glm::vec2{ 0.0f, 1.0f  }, glm::vec3{ 0.0f, 0.0f, 1.0f }}); // 4 8
        cube.vartices.push_back({glm::vec3(s, -s, s), glm::vec2{ 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }}); // 5 9
        cube.vartices.push_back({glm::vec3(-s, s, s), glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }}); // 6 10
        cube.vartices.push_back({glm::vec3(-s, -s, s), glm::vec2{ 1.0f, 0.0f },glm::vec3{ 0.0f, 0.0f, 1.0f }}); // 7 11

        cube.indices.emplace_back(9);
        cube.indices.emplace_back(8);
        cube.indices.emplace_back(10);

        cube.indices.emplace_back(9);
        cube.indices.emplace_back(10);
        cube.indices.emplace_back(11);

        // WEST
        cube.vartices.push_back({ glm::vec3(-s, -s, -s), glm::vec2(1.0f, 0.0f), glm::vec3{ -1.0f, 0.0f, 0.0f } }); // 0 12
        cube.vartices.push_back({ glm::vec3(-s, s, -s), glm::vec2(1.0f, 1.0f), glm::vec3{ -1.0f, 0.0f, 0.0f } }); // 1 13
        cube.vartices.push_back({ glm::vec3(-s, s, s), glm::vec2(0.0f, 1.0f), glm::vec3{ -1.0f, 0.0f, 0.0f } }); // 6 14
        cube.vartices.push_back({ glm::vec3(-s, -s, s), glm::vec2(0.0f, 0.0f), glm::vec3{ -1.0f, 0.0f, 0.0f } }); // 7 15

        cube.indices.emplace_back(15);
        cube.indices.emplace_back(14);
        cube.indices.emplace_back(13);

        cube.indices.emplace_back(15);
        cube.indices.emplace_back(13);
        cube.indices.emplace_back(12);

        // NORTH
        cube.vartices.push_back({ glm::vec3(-s, s, -s), glm::vec2{ 0.0f, 0.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f } });// 1 16
        cube.vartices.push_back({ glm::vec3(s, s, -s), glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } });// 2 17
        cube.vartices.push_back({ glm::vec3(s, s, s), glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } });// 4 18
        cube.vartices.push_back({ glm::vec3(-s, s, s), glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f } });// 6 19


        cube.indices.emplace_back(16);
        cube.indices.emplace_back(19);
        cube.indices.emplace_back(18);

        cube.indices.emplace_back(16);
        cube.indices.emplace_back(18);
        cube.indices.emplace_back(17);

        // SOUTH
        cube.vartices.push_back({ glm::vec3(-s, -s, -s), glm::vec2{ 0.0f, 0.0f}, glm::vec3{ 0.0f, -1.0f, 0.0f } });// 0 20
        cube.vartices.push_back({ glm::vec3(s, -s, -s), glm::vec2{ 1.0f, 0.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f } });// 3 21
        cube.vartices.push_back({ glm::vec3(s, -s, s), glm::vec2{ 1.0f, 1.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f } });// 5 22
        cube.vartices.push_back({ glm::vec3(-s, -s, s), glm::vec2{ 0.0f, 1.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f } });// 7 23

        cube.indices.emplace_back(22);
        cube.indices.emplace_back(23);
        cube.indices.emplace_back(20);

        cube.indices.emplace_back(22);
        cube.indices.emplace_back(20);
        cube.indices.emplace_back(21);

        return cube;
    }
}
