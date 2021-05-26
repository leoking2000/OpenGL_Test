#include "Graphics.h"
#include "math.h"

void graphics::Graphics::Init(Canvas* a)
{
	canvas = a;
}

void graphics::Graphics::DrawLine(const glm::vec3& a, const glm::vec3& b, const Color& c)
{
	glm::ivec2 t_a = NDC_To_Canvas(a);
	glm::ivec2 t_b = NDC_To_Canvas(b);

	canvas->DrawLine(t_a.x, t_a.y, t_b.x, t_b.y, c);
}

void graphics::Graphics::DrawWireframeTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const Color& color)
{
	glm::ivec2 t_a = NDC_To_Canvas(a);
	glm::ivec2 t_b = NDC_To_Canvas(b);
	glm::ivec2 t_c = NDC_To_Canvas(c);

	canvas->DrawLine(t_a.x, t_a.y, t_b.x, t_b.y, color);
	canvas->DrawLine(t_b.x, t_b.y, t_c.x, t_c.y, color);
	canvas->DrawLine(t_c.x, t_c.y, t_a.x, t_a.y, color);
}

void graphics::Graphics::DrawMesh(Mesh<Vertex> a)
{
	for (int i = 0; i < a.indices.size(); i += 3)
	{
		glm::vec3& vec0 = a.vartices[a.indices[i]].pos;
		glm::vec3& vec1 = a.vartices[a.indices[i+1]].pos;
		glm::vec3& vec2 = a.vartices[a.indices[i+2]].pos;

		glm::vec3 lineA = vec1 + vec0;
		glm::vec3 lineB = vec2 + vec0;
		glm::vec3 normal = glm::cross(lineA, lineB);
		
		normal = glm::normalize(normal);

		if (glm::dot(normal, vec0) > 0.0f) continue;

        DrawTriangle(vec0, vec1, vec2, a.vartices[a.indices[i]].color);
	}
}

void graphics::Graphics::DrawMeshTex(Mesh<TexVertex> a)
{
    for (int i = 0; i < a.indices.size(); i += 3)
    {
        glm::vec3 vec0 = a.vartices[a.indices[i]].pos;
        glm::vec3 vec1 = a.vartices[a.indices[i + 1]].pos;
        glm::vec3 vec2 = a.vartices[a.indices[i + 2]].pos;

        glm::vec3 lineA = vec1 + vec0;
        glm::vec3 lineB = vec2 + vec0;
        glm::vec3 normal = glm::cross(lineA, lineB);

        normal = glm::normalize(normal);

        if (glm::dot(normal, vec0) > 0.0f) continue;

        DrawTriangle(a.vartices[a.indices[i]], a.vartices[a.indices[i+1]], a.vartices[a.indices[i+2]]);
    }
}

glm::ivec2 graphics::Graphics::NDC_To_Canvas(const glm::vec3& vec)
{
	const float xFactor = WIDTH  / 2.0f;
	const float yFactor = HEIGHT / 2.0f;
	const float zFactor = 1.0f / vec.z;

	glm::ivec2 out;

	out.x = int(  (vec.x * zFactor + 1) * xFactor  );
	out.y = int( (-vec.y * zFactor + 1) * yFactor  );

	return out;
}

void NDC_To_Canvas2(glm::vec3& vec)
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
void topFlatTri(graphics::Canvas* canvas, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const graphics::Color& c)
{
    float m0 = (p2.x - p0.x) / (p2.y - p0.y);
    float m1 = (p2.x - p1.x) / (p2.y - p1.y);

    int ystart = (int)ceil(p0.y - 0.5);
    int yend = (int)ceil(p2.y - 0.5);

    for (int y = ystart; y < yend; ++y)
    {
        float px0 = m0 * ((float)y + 0.5f - p0.y) + p0.x;
        float px1 = m1 * ((float)y + 0.5f - p1.y) + p1.x;
        int xstart = (int)ceil(px0 - 0.5f);
        int xend = (int)ceil(px1 - 0.5f);

        for (int x = xstart; x < xend; ++x)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < WIDTH)
            {
                canvas->PutPixel(x, y, c);
            }         
        }

    }
}

void bottomFlatTri(graphics::Canvas* canvas, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const graphics::Color& c)
{
    float m0 = (p1.x - p0.x) / (p1.y - p0.y);
    float m1 = (p2.x - p0.x) / (p2.y - p0.y);

    int ystart = (int)ceil(p0.y - 0.5);
    int yend = (int)ceil(p2.y - 0.5);

    for (int y = ystart; y < yend; ++y)
    {
        float px0 = m0 * ((float)y + 0.5f - p0.y) + p0.x;
        float px1 = m1 * ((float)y + 0.5f - p0.y) + p0.x;
        int xstart = (int)ceil(px0 - 0.5f);
        int xend = (int)ceil(px1 - 0.5f);

        for (int x = xstart; x < xend; ++x)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < WIDTH)
            {
                canvas->PutPixel(x, y, c);
            }
        }

    }
}

void graphics::Graphics::DrawTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, const Color& c)
{
    NDC_To_Canvas2(p0);
    NDC_To_Canvas2(p1);
    NDC_To_Canvas2(p2);

    if (p1.y < p0.y) { std::swap(p0, p1); }
    if (p2.y < p0.y) { std::swap(p2, p0); }
    if (p2.y < p1.y) { std::swap(p2, p1); }

    if (p0.y == p1.y) // top flat
    {
        if (p1.x < p0.x) { std::swap(p0, p1); }
        topFlatTri(canvas, p0, p1, p2, c);
    }
    else if (p1.y == p2.y) // botton flat
    {
        if (p2.x < p1.x) { std::swap(p2, p1); }
        bottomFlatTri(canvas, p0, p1, p2, c);
    }
    else // generic
    {
        float alphaSplit =
            (p1.y - p0.y) /
            (p2.y - p0.y);
        glm::vec3 vi;
        vi.x = p0.x + (p2.x - p0.x) * alphaSplit;
        vi.y = p0.y + (p2.y - p0.y) * alphaSplit;

        if (p1.x < vi.x) // major right
        {
            bottomFlatTri(canvas, p0, p1, vi, c);
            topFlatTri(canvas, p1, vi, p2, c);
        }
        else // major left
        {
            bottomFlatTri(canvas, p0, vi, p1, c);
            topFlatTri(canvas, vi, p1, p2, c);
        }
    }
}
//////////////////////////////////////////////////
void topFlatTriTex(graphics::Canvas* canvas, TexVertex& p0, TexVertex& p1, TexVertex& p2, const Texture& t)
{
    float m0 = (p2.pos.x - p0.pos.x) / (p2.pos.y - p0.pos.y);
    float m1 = (p2.pos.x - p1.pos.x) / (p2.pos.y - p1.pos.y);

    int ystart = (int)ceil(p0.pos.y - 0.5);
    int yend = (int)ceil(p2.pos.y - 0.5);

    glm::vec2 tcEdgeL = p0.TexCord;
    glm::vec2 tcEdgeR = p1.TexCord;
    const glm::vec2 tcBottom = p2.TexCord;

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

void bottomFlatTriTex(graphics::Canvas* canvas, TexVertex& p0, TexVertex& p1, TexVertex& p2, const Texture& t)
{
    float m0 = (p1.pos.x - p0.pos.x) / (p1.pos.y - p0.pos.y);
    float m1 = (p2.pos.x - p0.pos.x) / (p2.pos.y - p0.pos.y);

    int ystart = (int)ceil(p0.pos.y - 0.5);
    int yend = (int)ceil(p2.pos.y - 0.5);

    glm::vec2 tcEdgeL = p0.TexCord;
    glm::vec2 tcEdgeR = p0.TexCord;
    const glm::vec2 tcBottomL = p1.TexCord;
    const glm::vec2 tcBottomR = p2.TexCord;

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

void graphics::Graphics::DrawTriangle(TexVertex p0, TexVertex p1, TexVertex p2)
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
        topFlatTriTex(canvas, p0, p1, p2, *p0.tex);
    }
    else if (p1.pos.y == p2.pos.y) // botton flat
    {
        if (p2.pos.x < p1.pos.x) { std::swap(p2, p1); }
        bottomFlatTriTex(canvas, p0, p1, p2, *p0.tex);
    }
    else // generic
    {
        float alphaSplit =
            (p1.pos.y - p0.pos.y) /
            (p2.pos.y - p0.pos.y);
        TexVertex vi(p0.pos, p0.TexCord, nullptr);
        vi.pos = Interpolate(p0.pos, p2.pos, alphaSplit);
        vi.TexCord = Interpolate(p0.TexCord, p2.TexCord, alphaSplit);

        if (p1.pos.x < vi.pos.x) // major right
        {
            bottomFlatTriTex(canvas, p0, p1, vi, *p0.tex);
            topFlatTriTex(canvas, p1, vi, p2, *p0.tex);
        }
        else // major left
        {
            bottomFlatTriTex(canvas, p0, vi, p1, *p0.tex);
            topFlatTriTex(canvas, vi, p1, p2, *p0.tex);
        }
    }
}
