#include "Graphics.h"
#include "math.h"

using namespace graphics;

void Graphics::Init(Canvas* a)
{
	canvas = a;
}

glm::ivec2 Graphics::NDC_To_Canvas(const glm::vec3& vec)
{
    const float xFactor = WIDTH / 2.0f;
    const float yFactor = HEIGHT / 2.0f;
    const float zFactor = 1.0f / vec.z;

    glm::ivec2 out;

    out.x = int((vec.x * zFactor + 1) * xFactor);
    out.y = int((-vec.y * zFactor + 1) * yFactor);

    return out;
}

void Graphics::NDC_To_Canvas2(glm::vec3& vec)
{
    const float xFactor = WIDTH / 2.0f;
    const float yFactor = HEIGHT / 2.0f;
    const float zFactor = 1.0f / vec.z;

    float x = (vec.x * zFactor + 1) * xFactor;
    float y = (-vec.y * zFactor + 1) * yFactor;

    vec.x = x;
    vec.y = y;
}

void Graphics::DrawLine(const glm::vec3& a, const glm::vec3& b, const Color& c)
{
	glm::ivec2 t_a = NDC_To_Canvas(a);
	glm::ivec2 t_b = NDC_To_Canvas(b);

	canvas->DrawLine(t_a.x, t_a.y, t_b.x, t_b.y, c);
}

void Graphics::DrawWireframeTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const Color& color)
{
	glm::ivec2 t_a = NDC_To_Canvas(a);
	glm::ivec2 t_b = NDC_To_Canvas(b);
	glm::ivec2 t_c = NDC_To_Canvas(c);

	canvas->DrawLine(t_a.x, t_a.y, t_b.x, t_b.y, color);
	canvas->DrawLine(t_b.x, t_b.y, t_c.x, t_c.y, color);
	canvas->DrawLine(t_c.x, t_c.y, t_a.x, t_a.y, color);
}
////////////////////////////////////////////////////////////////////////////

void graphics::Graphics::BindTransform(const Transform& in_transform)
{
    transform = &in_transform;
}

void graphics::Graphics::BindTexture(const Texture& in_tex)
{
    texture = &in_tex;
}

//////////////////////////////////////////////////

void graphics::Graphics::DrawMesh(const Mesh& in, const Transform& transform, const Texture& tex)
{
    BindTransform(transform);
    BindTexture(tex);
    DrawMesh(in);
}

void graphics::Graphics::DrawMesh(const Mesh& in)
{
    assert(transform != nullptr);
    assert(texture != nullptr);

    ProcessVertices(in);
}

void graphics::Graphics::ProcessVertices(const Mesh& in)
{
    Mesh mesh = in.GetTransformMesh(*transform);
    AssembleTriangles(mesh);
}

void graphics::Graphics::AssembleTriangles(Mesh& mesh)
{
    for (int i = 0; i < mesh.indices.size(); i += 3)
    {
        const glm::vec3& vec0 = mesh.vartices[mesh.indices[i]].pos;
        const glm::vec3& vec1 = mesh.vartices[mesh.indices[i + 1]].pos;
        const glm::vec3& vec2 = mesh.vartices[mesh.indices[i + 2]].pos;

        glm::vec3 lineA = vec1 + vec0;
        glm::vec3 lineB = vec2 + vec0;
        glm::vec3 normal = glm::cross(lineA, lineB);

        normal = glm::normalize(normal);

        if (glm::dot(normal, vec0) > 0.0f) continue;

        ProcessTriangle(mesh.vartices[mesh.indices[i]], mesh.vartices[mesh.indices[i + 1]], mesh.vartices[mesh.indices[i + 2]]);
    }
}

void graphics::Graphics::ProcessTriangle(Vertex& v0, Vertex& v1, Vertex& v2)
{
    PostProcessTriangleVertices(v0, v1, v2);
}

void graphics::Graphics::PostProcessTriangleVertices(Vertex v0, Vertex v1, Vertex v2)
{
    NDC_To_Canvas2(v0.pos);
    NDC_To_Canvas2(v1.pos);
    NDC_To_Canvas2(v2.pos);

    DrawTriangle(v0, v1, v2);
}

void graphics::Graphics::DrawTriangle(Vertex& v0, Vertex& v1, Vertex& v2)
{
    // sort by y
    if( v1.pos.y < v0.pos.y ) std::swap( v0,v1 );
    if( v2.pos.y < v1.pos.y ) std::swap( v1,v2 );
    if( v1.pos.y < v0.pos.y ) std::swap( v0,v1 );

    if (v0.pos.y == v1.pos.y) // natural flat top
    {
        // sorting top vertices by x
        if (v1.pos.x < v0.pos.x) std::swap(v0, v1);

        DrawFlatTopTriangle(v0, v1, v2);
    }
    else if (v1.pos.y == v2.pos.y) // natural flat bottom
    {
        // sorting bottom vertices by x
        if (v2.pos.x < v1.pos.x) std::swap(v1, v2);

        DrawFlatBottomTriangle(v0, v1, v2);
    }
    else // general triangle
    {
        // find splitting vertex interpolant
        const float alphaSplit =
            (v1.pos.y - v0.pos.y) /
            (v2.pos.y - v0.pos.y);

        const Vertex vi = Math::Interpolate(v0, v2, alphaSplit);

        if (v1.pos.x < vi.pos.x) // major right
        {
            DrawFlatBottomTriangle(v0, v1, vi);
            DrawFlatTopTriangle(v1, vi, v2);
        }
        else // major left
        {
            DrawFlatBottomTriangle(v0, vi, v1);
            DrawFlatTopTriangle(vi, v1, v2);
        }
    }
}

void graphics::Graphics::DrawFlatTopTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2)
{
    // calulcate dVertex / dy
    // change in interpolant for every 1 change in y
    const float delta_y = it2.pos.y - it0.pos.y;
    const auto dit0 = (it2 - it0) / delta_y;
    const auto dit1 = (it2 - it1) / delta_y;

    // create right edge interpolant
    auto itEdge1 = it1;

    // call the flat triangle render routine
    DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1);
}

void graphics::Graphics::DrawFlatBottomTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2)
{
    // calulcate dVertex / dy
    // change in interpolant for every 1 change in y
    const float delta_y = it2.pos.y - it0.pos.y;
    const auto dit0 = (it1 - it0) / delta_y;
    const auto dit1 = (it2 - it0) / delta_y;

    // create right edge interpolant
    auto itEdge1 = it0;

    // call the flat triangle render routine
    DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1);
}

void graphics::Graphics::DrawFlatTriangle(const Vertex& it0, const Vertex& it1, const Vertex& it2, const Vertex& dv0, const Vertex& dv1, Vertex itEdge1)
{
    auto itEdge0 = it0;

    // calculate start and end scanlines
    const int yStart = (int)ceil(it0.pos.y - 0.5f);
    const int yEnd = (int)ceil(it2.pos.y - 0.5f); // the scanline AFTER the last line drawn

    // do interpolant prestep
    itEdge0 += dv0 * (float(yStart) + 0.5f - it0.pos.y);
    itEdge1 += dv1 * (float(yStart) + 0.5f - it0.pos.y);

    // prepare clamping constants
    const float tex_width = float(texture->GetWidth());
    const float tex_height = float(texture->GetHeight());
    const float tex_xclamp = tex_width - 1.0f;
    const float tex_yclamp = tex_height - 1.0f;

    for (int y = yStart; y < yEnd; y++, itEdge0 += dv0, itEdge1 += dv1)
    {
        // calculate start and end pixels
        const int xStart = (int)ceil(itEdge0.pos.x - 0.5f);
        const int xEnd = (int)ceil(itEdge1.pos.x - 0.5f); // the pixel AFTER the last pixel drawn

        // create scanline interpolant startpoint
        // (some waste for interpolating x,y,z, but makes life easier not having
        //  to split them off, and z will be needed in the future anyways...)
        auto iLine = itEdge0;

        // calculate delta scanline interpolant / dx
        const float dx = itEdge1.pos.x - itEdge0.pos.x;
        const auto diLine = (itEdge1 - iLine) / dx;

        // prestep scanline interpolant
        iLine += diLine * (float(xStart) + 0.5f - itEdge0.pos.x);

        for (int x = xStart; x < xEnd; x++, iLine += diLine)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            {
                // perform texture lookup, clamp, and write pixel
                graphics::Color c = texture->GetPixel(
                    (uint8_t)std::min(iLine.texCord.x * tex_width + 0.5f, tex_xclamp),
                    (uint8_t)std::min(iLine.texCord.y * tex_height + 0.5f, tex_yclamp)
                );

                canvas->PutPixel(x, y, c);
            }
        }
    }
}



