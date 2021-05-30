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
        Mesh<TextureEffect::Vertex> mesh = MakeCube<TextureEffect::Vertex>(size);

        for (int i = 0; i < mesh.vartices.size(); i += 4)
        {
            mesh.vartices[i].texCord   = glm::vec2(0.0f, 0.0f);
            mesh.vartices[i+1].texCord = glm::vec2(0.0f, 1.0f);
            mesh.vartices[i+2].texCord = glm::vec2(1.0f, 0.0f);
            mesh.vartices[i+3].texCord = glm::vec2(1.0f, 1.0f);
        }

        return mesh;
    }
}
