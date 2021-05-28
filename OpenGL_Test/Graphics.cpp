#include "Graphics.h"
#include "math.h"

using namespace graphics;

void Graphics::Init(Canvas* a)
{
	canvas = a;
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

void graphics::Graphics::DrawMesh(const Mesh& in, const Transform& transform, const Texture& tex)
{
    Mesh mesh = in.GetTransformMesh(transform);

    for (int i = 0; i < mesh.indices.size(); i += 3)
    {
        glm::vec3& vec0 = mesh.vartices[mesh.indices[i]].pos;
        glm::vec3& vec1 = mesh.vartices[mesh.indices[i + 1]].pos;
        glm::vec3& vec2 = mesh.vartices[mesh.indices[i + 2]].pos;

        glm::vec3 lineA = vec1 + vec0;
        glm::vec3 lineB = vec2 + vec0;
        glm::vec3 normal = glm::cross(lineA, lineB);

        normal = glm::normalize(normal);

        if (glm::dot(normal, vec0) > 0.0f) continue;

        DrawTriangle(mesh.vartices[mesh.indices[i]], mesh.vartices[mesh.indices[i+1]], mesh.vartices[mesh.indices[i+2]], tex);
    }
}

glm::ivec2 Graphics::NDC_To_Canvas(const glm::vec3& vec)
{
	const float xFactor = WIDTH  / 2.0f;
	const float yFactor = HEIGHT / 2.0f;
	const float zFactor = 1.0f / vec.z;

	glm::ivec2 out;

	out.x = int(  (vec.x * zFactor + 1) * xFactor  );
	out.y = int( (-vec.y * zFactor + 1) * yFactor  );

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

//////////////////////////////////////////////////

void topFlatTriTex(graphics::Canvas* canvas, Vertex& p0, Vertex& p1, Vertex& p2, const Texture& t)
{
    float m0 = (p2.pos.x - p0.pos.x) / (p2.pos.y - p0.pos.y);
    float m1 = (p2.pos.x - p1.pos.x) / (p2.pos.y - p1.pos.y);

    int ystart = (int)ceil(p0.pos.y - 0.5);
    int yend = (int)ceil(p2.pos.y - 0.5);

    glm::vec2 tcEdgeL = p0.texCord;
    glm::vec2 tcEdgeR = p1.texCord;
    const glm::vec2 tcBottom = p2.texCord;

    const glm::vec2 tcEdgeStepL = (tcBottom - tcEdgeL) / (p2.pos.y - p0.pos.y);
    const glm::vec2 tcEdgeStepR = (tcBottom - tcEdgeR) / (p2.pos.y - p1.pos.y);

    tcEdgeL += tcEdgeStepL * (float(ystart) + 0.5f - p1.pos.y);
    tcEdgeR += tcEdgeStepR * (float(ystart) + 0.5f - p1.pos.y);

    const float tex_width = float(t.GetWidth());
    const float tex_height = float(t.GetHeight());
    const float tex_clamp_x = tex_width - 1.0f;
    const float tex_clamp_y = tex_height - 1.0f;

    for (int y = ystart; y < yend; ++y, tcEdgeL += tcEdgeStepL, tcEdgeR += tcEdgeStepR)
    {
        float px0 = m0 * ((float)y + 0.5f - p0.pos.y) + p0.pos.x;
        float px1 = m1 * ((float)y + 0.5f - p1.pos.y) + p1.pos.x;
        int xstart = (int)ceil(px0 - 0.5f);
        int xend = (int)ceil(px1 - 0.5f);

        const glm::vec2 tcScanStep = (tcEdgeR - tcEdgeL) / (px1 - px0);
        glm::vec2 tc = tcEdgeL + tcScanStep * (float(xstart) + 0.5f - px0);

        for (int x = xstart; x < xend; ++x, tc += tcScanStep)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < WIDTH)
            {
                graphics::Color c = t.GetPixel(
                    int(std::fmod(tc.x * tex_width, tex_clamp_x)),
                    int(std::fmod(tc.y * tex_height, tex_clamp_y)
                        ));
                canvas->PutPixel(x, y, c);
            }
        }

    }
}

void bottomFlatTriTex(graphics::Canvas* canvas, Vertex& p0, Vertex& p1, Vertex& p2, const Texture& t)
{
    float m0 = (p1.pos.x - p0.pos.x) / (p1.pos.y - p0.pos.y);
    float m1 = (p2.pos.x - p0.pos.x) / (p2.pos.y - p0.pos.y);

    int ystart = (int)ceil(p0.pos.y - 0.5);
    int yend = (int)ceil(p2.pos.y - 0.5);

    glm::vec2 tcEdgeL = p0.texCord;
    glm::vec2 tcEdgeR = p0.texCord;
    const glm::vec2 tcBottomL = p1.texCord;
    const glm::vec2 tcBottomR = p2.texCord;

    const glm::vec2 tcEdgeStepL = (tcBottomL - tcEdgeL) / (p1.pos.y - p0.pos.y);
    const glm::vec2 tcEdgeStepR = (tcBottomR - tcEdgeR) / (p2.pos.y - p0.pos.y);

    tcEdgeL += tcEdgeStepL * (float(ystart) + 0.5f - p0.pos.y);
    tcEdgeR += tcEdgeStepR * (float(ystart) + 0.5f - p0.pos.y);

    const float tex_width = float(t.GetWidth());
    const float tex_height = float(t.GetHeight());
    const float tex_clamp_x = tex_width - 1.0f;
    const float tex_clamp_y = tex_height - 1.0f;

    for (int y = ystart; y < yend; ++y, tcEdgeL += tcEdgeStepL, tcEdgeR += tcEdgeStepR)
    {
        float px0 = m0 * ((float)y + 0.5f - p0.pos.y) + p0.pos.x;
        float px1 = m1 * ((float)y + 0.5f - p0.pos.y) + p0.pos.x;
        int xstart = (int)ceil(px0 - 0.5f);
        int xend = (int)ceil(px1 - 0.5f);

        const glm::vec2 tcScanStep = (tcEdgeR - tcEdgeL) / (px1 - px0);
        glm::vec2 tc = tcEdgeL + tcScanStep * (float(xstart) + 0.5f - px0);

        for (int x = xstart; x < xend; ++x, tc += tcScanStep)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < WIDTH)
            {
                graphics::Color c = t.GetPixel(
                    int(std::fmod(tc.x * tex_width, tex_clamp_x)),
                    int(std::fmod(tc.y * tex_height, tex_clamp_y)
                        ));
                canvas->PutPixel(x, y, c);
            }
        }

    }
}

void graphics::Graphics::DrawTriangle(Vertex p0, Vertex p1, Vertex p2, const Texture& tex)
{
    NDC_To_Canvas2(p0.pos);
    NDC_To_Canvas2(p1.pos);
    NDC_To_Canvas2(p2.pos);

    if (p1.pos.y < p0.pos.y) { std::swap(p0, p1); }
    if (p2.pos.y < p0.pos.y) { std::swap(p2, p0); }
    if (p2.pos.y < p1.pos.y) { std::swap(p2, p1); }

    if (p0.pos.y == p1.pos.y) // top flat
    {
        if (p1.pos.x < p0.pos.x) { std::swap(p0, p1); }
        topFlatTriTex(canvas, p0, p1, p2, tex);
    }
    else if (p1.pos.y == p2.pos.y) // botton flat
    {
        if (p2.pos.x < p1.pos.x) { std::swap(p2, p1); }
        bottomFlatTriTex(canvas, p0, p1, p2, tex);
    }
    else // generic
    {
        float alphaSplit =
            (p1.pos.y - p0.pos.y) /
            (p2.pos.y - p0.pos.y);

        Vertex vi = Math::Interpolate(p0, p2, alphaSplit);

        if (p1.pos.x < vi.pos.x) // major right
        {
            bottomFlatTriTex(canvas, p0, p1, vi, tex);
            topFlatTriTex(canvas, p1, vi, p2, tex);
        }
        else // major left
        {
            bottomFlatTriTex(canvas, p0, vi, p1, tex);
            topFlatTriTex(canvas, vi, p1, p2, tex);
        }
    }
}
