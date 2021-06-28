#pragma once
#include "math.h"
#include "Mesh.h"

#include "DefaultVertexShader.h"
#include "DefaultGeometryShader.h"
#include "Colors.h"
#include "VertexP.h"

namespace graphics
{
    class OneColorEffect
    {
    public:
        typedef VertexP Vertex;
    public:
        typedef typename DefaultVertexShader<Vertex> VertexShader;
        typedef typename DefaultGeometryShader<Vertex> GeometryShader;
    public:
        class PixelShader
        {
        public:
            Color operator()(const Vertex& vec)
            {
                Color c = color;

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