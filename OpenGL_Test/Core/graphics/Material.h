#pragma once
#include "Core/graphics/Abstractions/Shader.h"
#include "Core/graphics/Abstractions/Texture.h"

namespace graphics
{
	class Matirial
	{
	public:
		graphics::Shader shader;
		graphics::Texture tex;

	public:
		Matirial(const char* shader, const char* tex)
			:
			shader(shader),
			tex(tex)
		{
		}
		Matirial(const char* shader, const graphics::Color color)
			:
			shader(shader),
			tex(1, 1, color)
		{
		}
		Matirial(const char* shader)
			:
			shader(shader),
			tex(0, 0)
		{

		}

		void Bind() const
		{
			shader.Bind();
			tex.Bind();
		}
	};

}