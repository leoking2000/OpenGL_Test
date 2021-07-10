#pragma once
#include <cinttypes>

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

		bool SetUniform(const char* name, float num);
		bool SetUniform(const char* name, float x, float y);
		bool SetUniform(const char* name, float x, float y, float z);

		bool SetUniform(const char* name, int i);

	private:
		uint32_t id = 0;
		// cash uniform location?
	};
}
