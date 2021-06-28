#pragma once
#include "math.h"
#include "Mesh.h"

#include "DefaultGeometryShader.h"
#include "GouraudPointVS.h"
#include "VertexPN.h"


namespace graphics
{
    class GouraudPointEffect
    {
    public:
        typedef VertexPN Vertex;
    public:
        typedef typename GouraudPointVS<Vertex> VertexShader;
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
