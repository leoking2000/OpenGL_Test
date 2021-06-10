#pragma once
#include "Canvas.h"
#include "Mesh.h"
#include "math.h"
#include <algorithm>

namespace graphics
{
	/*
	* Draws to canvas using a Mesh as Input
	* it also does z-divide (perspective-divide)
	*
	* 
	* it use a Effect factor in order to draw with style!!!!
	*/
	template<class Effect>
	class Graphics
	{
	private:
		Canvas* canvas;
		const Transform* transform = nullptr;
	public:
		Effect effect;
		typedef typename Effect::Vertex Vertex;
		typedef typename Effect::VertexShader::Output VSout;
		typedef typename Effect::GeometryShader::Output GSout;
		typedef typename Mesh<Vertex> Mesh;
	public:
		// we need a pointer to the canvas in order to Draw
		void Init(Canvas* a)
		{
			canvas = a;
		}

		void DrawMesh(const Mesh& in)
		{
			assert(canvas != nullptr);
			assert(transform != nullptr);

			ProcessVertices(in);
		}

		void DrawLine(const glm::vec3& a, const glm::vec3& b, const Color& c)
		{
			glm::ivec2 t_a = NDC_To_Canvas(a);
			glm::ivec2 t_b = NDC_To_Canvas(b);

			canvas->DrawLine(t_a.x, t_a.y, t_b.x, t_b.y, c);
		}
		void DrawWireframeTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const Color& color)
		{
			glm::ivec2 t_a = NDC_To_Canvas(a);
			glm::ivec2 t_b = NDC_To_Canvas(b);
			glm::ivec2 t_c = NDC_To_Canvas(c);

			canvas->DrawLine(t_a.x, t_a.y, t_b.x, t_b.y, color);
			canvas->DrawLine(t_b.x, t_b.y, t_c.x, t_c.y, color);
			canvas->DrawLine(t_c.x, t_c.y, t_a.x, t_a.y, color);
		}

	private:
		// pipeline
		// model -> world (copy)
		void ProcessVertices(const Mesh& in)
		{
			std::vector<VSout> vartices(in.vartices.size());

			std::transform(in.vartices.begin(), in.vartices.end(), vartices.begin(), effect.vertex_shader);

			AssembleTriangles(vartices, in.indices);
		}
		// assemble triagles using index list and does Backface Culling
		void AssembleTriangles(std::vector<VSout>& vartices, const std::vector<uint64_t>& indices)
		{
			const int end = indices.size() / 3;

			for (int i = 0; i < end; i++)
			{
				const int k = i * 3;

				const glm::vec3& vec0 = vartices[indices[k]].pos;
				const glm::vec3& vec1 = vartices[indices[k + 1]].pos;
				const glm::vec3& vec2 = vartices[indices[k + 2]].pos;

				glm::vec3 lineA = vec1 + vec0;
				glm::vec3 lineB = vec2 + vec0;
				glm::vec3 normal = glm::cross(lineA, lineB);

				normal = glm::normalize(normal);

				if (glm::dot(normal, vec0) > 0.0f) continue;

				ProcessTriangle(vartices[indices[k]], vartices[indices[k + 1]], vartices[indices[k + 2]], i);
			}
		}
		// geometry shader
		void ProcessTriangle(VSout& v0, VSout& v1, VSout& v2, int tri_id)
		{

			std::vector<GSout> tri = effect.geometry_shader(v0, v1, v2, tri_id);

			PostProcessTriangleVertices(tri[0], tri[1], tri[2]);
		}
		// world -> view (perspective)
		void PostProcessTriangleVertices(GSout v0, GSout v1, GSout v2)
		{
			NDC_To_Canvas2(v0);
			NDC_To_Canvas2(v1);
			NDC_To_Canvas2(v2);

			DrawTriangle(v0, v1, v2);
		}
		// wat this do?
		void DrawTriangle(GSout& v0, GSout& v1, GSout& v2)
		{
			// sort by y
			if (v1.pos.y < v0.pos.y) std::swap(v0, v1);
			if (v2.pos.y < v1.pos.y) std::swap(v1, v2);
			if (v1.pos.y < v0.pos.y) std::swap(v0, v1);

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

				const auto vi = Math::Interpolate(v0, v2, alphaSplit);

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
	private:
		void DrawFlatTopTriangle(const GSout& it0, const GSout& it1, const GSout& it2)
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

		void DrawFlatBottomTriangle(const GSout& it0, const GSout& it1, const GSout& it2)
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

		void DrawFlatTriangle(const GSout& it0, const GSout& it1, const GSout& it2, const GSout& dv0, const GSout& dv1, GSout itEdge1)
		{
			auto itEdge0 = it0;

			// calculate start and end scanlines
			const int yStart = (int)ceil(it0.pos.y - 0.5f);
			const int yEnd = (int)ceil(it2.pos.y - 0.5f); // the scanline AFTER the last line drawn

			// do interpolant prestep
			itEdge0 += dv0 * (float(yStart) + 0.5f - it0.pos.y);
			itEdge1 += dv1 * (float(yStart) + 0.5f - it0.pos.y);

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
						// recover interpolated z from interpolated 1/z
						const float z = 1.0f / iLine.pos.z;

						if (canvas->Depth_TestSet(x, y, z))
						{
							// recover interpolated attributes
							// (wasted effort in multiplying pos (x,y,z) here, but
							//  not a huge deal, not worth the code complication to fix) 
							const auto attr = iLine * z;

							// invoke pixel shader with interpolated vertex attributes	
							graphics::Color c = effect.pixel_shader(attr);
							// and use result to set the pixel color on the screen
							canvas->PutPixel(x, y, c);
						}

					}
				}
			}
		}
	private:
		static glm::ivec2 NDC_To_Canvas(const glm::vec3& vec)
		{
			const float xFactor = WIDTH / 2.0f;
			const float yFactor = HEIGHT / 2.0f;
			const float zFactor = 1.0f / vec.z;

			glm::ivec2 out;

			out.x = int((vec.x * zFactor + 1) * xFactor);
			out.y = int((-vec.y * zFactor + 1) * yFactor);

			return out;
		}
		static void NDC_To_Canvas2(GSout& vec)
		{
			const float xFactor = WIDTH / 2.0f;
			const float yFactor = HEIGHT / 2.0f;
			const float zFactor = 1.0f / vec.pos.z;

			// divide all position components and attributes by z
			// (we want to be interpolating our attributes in the
			//  same space where the x,y interpolation is taking
			//  place to prevent distortion)
			vec *= zFactor;

			// adjust position x,y from perspective normalized space
			// to screen dimension space after perspective divide
			float x = ( vec.pos.x + 1.0f)  * xFactor;
			float y = (-vec.pos.y + 1.0f)  * yFactor;

			vec.pos.x = x;
			vec.pos.y = y;

			// store 1/z in z (we will need the interpolated 1/z
			// so that we can recover the attributes after interp.)
			vec.pos.z = zFactor;
		}
	};
}



