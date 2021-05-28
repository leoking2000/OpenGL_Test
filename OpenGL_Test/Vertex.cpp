#include "Vertex.h"

graphics::Vertex::Vertex()
{
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    texCord = glm::vec3(0.0f, 0.0f, 0.0f);
}

graphics::Vertex::Vertex(const graphics::Vertex& other)
{
    pos = other.pos;
    texCord = other.texCord;
}

graphics::Vertex::Vertex(const glm::vec3& in_pos, const glm::vec2& in_texCord)
{
    pos = in_pos;
    texCord = in_texCord;
}

graphics::Vertex& graphics::Vertex::operator+=(const graphics::Vertex& rhs)
{
    pos += rhs.pos;
    texCord += rhs.texCord;

    return *this;
}

graphics::Vertex graphics::Vertex::operator+(const graphics::Vertex& rhs) const
{
    return Vertex(*this) += rhs;
}

graphics::Vertex& graphics::Vertex::operator-=(const graphics::Vertex& rhs)
{
    pos -= rhs.pos;
    texCord -= rhs.texCord;

    return *this;
}

graphics::Vertex graphics::Vertex::operator-(const graphics::Vertex& rhs) const
{
    return Vertex(*this) -= rhs;
}

graphics::Vertex& graphics::Vertex::operator*=(float rhs)
{
    pos *= rhs;
    texCord *= rhs;

    return *this;
}

graphics::Vertex graphics::Vertex::operator*(float rhs) const
{
    return Vertex(*this) *= rhs;
}

graphics::Vertex& graphics::Vertex::operator/=(const graphics::Vertex& rhs)
{
    pos /= rhs.pos;
    texCord /= rhs.texCord;

    return *this;
}

graphics::Vertex graphics::Vertex::operator/(const graphics::Vertex& rhs) const
{
    return Vertex(*this) /= rhs;
}
