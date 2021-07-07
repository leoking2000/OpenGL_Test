#pragma once
#include <cinttypes>

namespace graphics
{
	uint32_t CreateProgramShader(const char* filename);

	class Shader
	{
	public:
		Shader(const char* filename);
		~Shader();

		void Bind() const;
		void UnBind() const;

		bool SetUniform(const char* name, float num);
		bool SetUniform(const char* name, float x, float y);
		bool SetUniform(const char* name, float x, float y, float z);

	private:
		uint32_t id;
		// cash uniform location?
	};
}
