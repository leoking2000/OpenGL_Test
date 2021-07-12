#include "Shader.h"
#include "Platform/OpenGL.h"
#include "Core/utilities/Log.h"

#include <malloc.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace graphics;

graphics::Shader::Shader()
{
}

graphics::Shader::Shader(const char* filename)
{
	id = CreateProgramShader(filename);
	glCall(glUseProgram(id));
}

graphics::Shader::~Shader()
{
	glCall(glDeleteProgram(id));
}

void graphics::Shader::Recreate(const char* filename)
{
	glCall(glDeleteProgram(id));

	id = CreateProgramShader(filename);
	glCall(glUseProgram(id));
}

void graphics::Shader::Bind() const
{
	glCall(glUseProgram(id));
}

void graphics::Shader::UnBind() const
{
	glCall(glUseProgram(0));
}

bool graphics::Shader::SetUniform(const char* name, float num)
{
	glCall(int location = glGetUniformLocation(id, name));
	if (location != -1)
	{
		glCall(glProgramUniform1f(id, location, num));
		return true;
	}
	Logger::LogError("uniform error");
	return false;
}

bool graphics::Shader::SetUniform(const char* name, float x, float y)
{
	glCall(int location = glGetUniformLocation(id, name));
	if (location != -1)
	{
		glCall(glProgramUniform2f(id, location, x, y));
		return true;
	}
	Logger::LogError("uniform error");
	return false;
}

bool graphics::Shader::SetUniform(const char* name, float x, float y, float z)
{
	glCall(int location = glGetUniformLocation(id, name));
	if (location != -1)
	{
		glCall(glProgramUniform3f(id, location, x, y, z));
		return true;
	}
	Logger::LogError("uniform error");
	return false;
}

bool graphics::Shader::SetUniform(const char* name, int i)
{
	glCall(int location = glGetUniformLocation(id, name));
	if (location != -1)
	{
		glCall(glProgramUniform1i(id, location, i));
		return true;
	}
	Logger::LogError("uniform error");
	return false;
}

bool graphics::Shader::SetUniform(const char* name, const glm::mat4& mat)
{
	glCall(int location = glGetUniformLocation(id, name));
	if (location != -1)
	{
		glCall(glProgramUniformMatrix4fv(id, location, 1, GL_FALSE, glm::value_ptr(mat)));
		return true;
	}
	Logger::LogError("uniform error");
	return false;
}

uint32_t CompileShader(const char* source, uint32_t type)
{
	glCall(uint32_t id = glCreateShader(type));

	glCall(glShaderSource(id, 1, &source, nullptr));
	glCall(glCompileShader(id));

	int resalt;
	glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &resalt));
	if (resalt == GL_FALSE)
	{
		Logger::LogError(type == GL_VERTEX_SHADER ? "<VERTEX SHADER COMPILE ERROR>" : "<FRAGMENT SHADER COMPILE ERROR>");
		int len;
		glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
		char* msg = (char*)alloca(len * sizeof(char));
		glCall(glGetShaderInfoLog(id, len, &len, msg));
		Logger::LogError(msg);
		glCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

uint32_t CreateProgramShaderVF(const char* vertexS, const char* fragS)
{
	glCall(uint32_t programid = glCreateProgram());

	uint32_t vs = CompileShader(vertexS, GL_VERTEX_SHADER);
	uint32_t fs = CompileShader(fragS, GL_FRAGMENT_SHADER);

	assert(vs != 0);
	assert(fs != 0);

	glCall(glAttachShader(programid, vs));
	glCall(glAttachShader(programid, fs));
	glCall(glLinkProgram(programid));
	glCall(glValidateProgram(programid));

	glCall(glDeleteShader(vs));
	glCall(glDeleteShader(fs));

	return programid;
}

uint32_t graphics::CreateProgramShader(const char* filename)
{
	assert(filename != nullptr);

	std::ifstream file(filename);

	assert(file.fail() == false);

	std::string msg = "Creating shader from file ";
	msg += filename;
	Logger::LogInfo(msg.c_str());

	enum ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	uint32_t program = CreateProgramShaderVF(ss[0].str().c_str(), ss[1].str().c_str());

	msg = "Creation of shader from file ";
	msg += filename;
	msg += " Has completed";
	Logger::LogInfo(msg.c_str());

	return program;
}
