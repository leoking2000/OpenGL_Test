#pragma once
#include <cinttypes>
#include "Math/math.h"

namespace graphics
{
	uint32_t CreateProgramShader(const char* filename);

	class Shader
	{
	public:
		Shader();
		Shader(const char* filename);
		~Shader();

		void Recreate(const char* filename);

		void Bind() const;
		void UnBind() const;

		bool SetUniform(const char* name, float num) const;
		bool SetUniform(const char* name, float x, float y) const;
		bool SetUniform(const char* name, float x, float y, float z) const;
		bool SetUniform(const char* name, float x, float y, float z, float w) const;

		bool SetUniform(const char* name, int i) const;

		bool SetUniform(const char* name, const glm::mat4& mat) const;

	private:
		uint32_t id = 0;
		// cash uniform location?
	};
}
