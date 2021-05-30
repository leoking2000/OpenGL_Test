#pragma once
#include "math.h"
#include "Texture.h"
#include "Make_Shape.h"

namespace graphics
{
    class TextureEffect
    {
    public:
        class Vertex
        {
        public:
            glm::vec3 pos;
            glm::vec2 texCord;
        public:
            Vertex()
            {
                pos = glm::vec3(0.0f, 0.0f, 0.0f);
                texCord = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            Vertex(const glm::vec3& in_pos)
            {
                pos = in_pos;
                texCord = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            Vertex(glm::vec3 in_pos, glm::vec2 tex)
            {
                pos = in_pos;
                texCord = tex;
            }

            Vertex(const glm::vec3& in_pos, const Vertex& other)
            {
                pos = in_pos;
                texCord = other.texCord;
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

            Vertex& operator*=(float rhs)
            {
                pos *= rhs;
                texCord *= rhs;

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
        class PixelShader
        {
        public:
            Color operator()(const Vertex& vec)
            {
                Color c = texture->GetPixel((int)std::fmod(vec.texCord.x * tex_width + 0.5f, tex_xclamp),
                                            (int)std::fmod(vec.texCord.y * tex_height + 0.5f, tex_yclamp));

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
        PixelShader pixel_shader;
    };

    static Mesh<TextureEffect::Vertex> MakeCube_TextureEffect(float size)
    {
        Mesh<TextureEffect::Vertex> cube;

        const float s = size / 2.0f;

        // Forward
        cube.vartices.emplace_back(glm::vec3(-s, -s, -s), glm::vec2(0.0f, 0.0f));// 0 0 
        cube.vartices.emplace_back(glm::vec3(-s, s, -s), glm::vec2(0.0f, 1.0f));// 1 1
        cube.vartices.emplace_back(glm::vec3(s, s, -s), glm::vec2(1.0f, 1.0f));// 2 2 
        cube.vartices.emplace_back(glm::vec3(s, -s, -s), glm::vec2(1.0f, 0.0f));// 3 3

        cube.indices.emplace_back(0);
        cube.indices.emplace_back(1);
        cube.indices.emplace_back(2);

        cube.indices.emplace_back(0);
        cube.indices.emplace_back(2);
        cube.indices.emplace_back(3);

        // EAST
        cube.vartices.emplace_back(glm::vec3(s, s, -s), glm::vec2(0.0f, 1.0f));// 2 4
        cube.vartices.emplace_back(glm::vec3(s, -s, -s), glm::vec2(0.0f, 0.0f));// 3 5
        cube.vartices.emplace_back(glm::vec3(s, s, s), glm::vec2(1.0f, 1.0f));// 4 6
        cube.vartices.emplace_back(glm::vec3(s, -s, s), glm::vec2(1.0f, 0.0f));// 5 7

        cube.indices.emplace_back(5);
        cube.indices.emplace_back(4);
        cube.indices.emplace_back(6);

        cube.indices.emplace_back(5);
        cube.indices.emplace_back(6);
        cube.indices.emplace_back(7);

        // BACK
        cube.vartices.emplace_back(glm::vec3(s, s, s), glm::vec2{ 0.0f, 1.0f }); // 4 8
        cube.vartices.emplace_back(glm::vec3(s, -s, s), glm::vec2{ 0.0f, 0.0f }); // 5 9
        cube.vartices.emplace_back(glm::vec3(-s, s, s), glm::vec2{ 1.0f, 1.0f }); // 6 10
        cube.vartices.emplace_back(glm::vec3(-s, -s, s), glm::vec2{ 1.0f, 0.0f }); // 7 11

        cube.indices.emplace_back(9);
        cube.indices.emplace_back(8);
        cube.indices.emplace_back(10);

        cube.indices.emplace_back(9);
        cube.indices.emplace_back(10);
        cube.indices.emplace_back(11);

        // WEST
        cube.vartices.emplace_back(glm::vec3(-s, -s, -s), glm::vec2(1.0f, 0.0f)); // 0 12
        cube.vartices.emplace_back(glm::vec3(-s, s, -s), glm::vec2(1.0f, 1.0f)); // 1 13
        cube.vartices.emplace_back(glm::vec3(-s, s, s), glm::vec2(0.0f, 1.0f)); // 6 14
        cube.vartices.emplace_back(glm::vec3(-s, -s, s), glm::vec2(0.0f, 0.0f)); // 7 15

        cube.indices.emplace_back(15);
        cube.indices.emplace_back(14);
        cube.indices.emplace_back(13);

        cube.indices.emplace_back(15);
        cube.indices.emplace_back(13);
        cube.indices.emplace_back(12);

        // NORTH
        cube.vartices.emplace_back(glm::vec3(-s, s, -s), glm::vec2{ 0.0f, 0.0f });// 1 16
        cube.vartices.emplace_back(glm::vec3(s, s, -s), glm::vec2{ 0.0f, 1.0f });// 2 17
        cube.vartices.emplace_back(glm::vec3(s, s, s), glm::vec2{ 1.0f, 1.0f });// 4 18
        cube.vartices.emplace_back(glm::vec3(-s, s, s), glm::vec2{ 1.0f, 0.0f });// 6 19


        cube.indices.emplace_back(16);
        cube.indices.emplace_back(19);
        cube.indices.emplace_back(18);

        cube.indices.emplace_back(16);
        cube.indices.emplace_back(18);
        cube.indices.emplace_back(17);

        // SOUTH
        cube.vartices.emplace_back(glm::vec3(-s, -s, -s), glm::vec2{ 0.0f, 0.0f });// 0 20
        cube.vartices.emplace_back(glm::vec3(s, -s, -s), glm::vec2{ 1.0f, 0.0f });// 3 21
        cube.vartices.emplace_back(glm::vec3(s, -s, s), glm::vec2{ 1.0f, 1.0f });// 5 22
        cube.vartices.emplace_back(glm::vec3(-s, -s, s), glm::vec2{ 0.0f, 1.0f });// 7 23

        cube.indices.emplace_back(22);
        cube.indices.emplace_back(23);
        cube.indices.emplace_back(20);

        cube.indices.emplace_back(22);
        cube.indices.emplace_back(20);
        cube.indices.emplace_back(21);

        return cube;
    }
}
