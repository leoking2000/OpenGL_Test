#pragma once
#include <cinttypes>
#include "leo_math.h"

namespace graphics
{
	class Shader
	{
	public:
		Shader(const char* filename);

		Shader(const Shader& other) = delete;
		Shader& operator=(const Shader& other) = delete;

		Shader(Shader&& other);
		Shader& operator=(Shader&& other);

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
		static uint32_t CreateProgramShader(const char* filename);
		int32_t GetLocation(const char* name) const;
	private:
		uint32_t m_id;
		//TODO: cash uniform location?
	};
}
