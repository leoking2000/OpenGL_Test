#include "Shader.h"
#include "OpenGL.h"
#include "Log.h"

#include <malloc.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace graphics;

graphics::Shader::Shader(const char* filename)
{
	m_id = CreateProgramShader(filename);
	glCall(glUseProgram(m_id));
}

graphics::Shader::Shader(Shader&& other)
	:
	m_id(other.m_id)
{
	other.m_id = 0;
}

Shader& graphics::Shader::operator=(Shader&& other)
{
	m_id = other.m_id;
	other.m_id = 0;
	return *this;
}

graphics::Shader::~Shader()
{
	glCall(glDeleteProgram(m_id));
}

void graphics::Shader::Recreate(const char* filename)
{
	glCall(glDeleteProgram(m_id));

	m_id = CreateProgramShader(filename);
	glCall(glUseProgram(m_id));
}

void graphics::Shader::Bind() const
{
	glCall(glUseProgram(m_id));
}

void graphics::Shader::UnBind() const
{
	glCall(glUseProgram(0));
}

bool graphics::Shader::SetUniform(const char* name, float num) const
{
	int32_t location = GetLocation(name);
	if (location != -1)
	{
		glCall(glProgramUniform1f(m_id, location, num));
		return true;
	}
	std::string msg = "uniform error ";
	msg += name;
	Logger::LogError(msg.c_str());
	return false;
}

bool graphics::Shader::SetUniform(const char* name, float x, float y) const
{
	int32_t location = GetLocation(name);
	if (location != -1)
	{
		glCall(glProgramUniform2f(m_id, location, x, y));
		return true;
	}
	std::string msg = "uniform error ";
	msg += name;
	Logger::LogError(msg.c_str());
	return false;
}

bool graphics::Shader::SetUniform(const char* name, float x, float y, float z) const
{
	int32_t location = GetLocation(name);
	if (location != -1)
	{
		glCall(glProgramUniform3f(m_id, location, x, y, z));
		return true;
	}
	std::string msg = "uniform error ";
	msg += name;
	Logger::LogError(msg.c_str());
	return false;
}

bool graphics::Shader::SetUniform(const char* name, float x, float y, float z, float w) const
{
	int32_t location = GetLocation(name);
	if (location != -1)
	{
		glCall(glProgramUniform4f(m_id, location, x, y, z, w));
		return true;
	}
	std::string msg = "uniform error ";
	msg += name;
	Logger::LogError(msg.c_str());
	return false;
}

bool graphics::Shader::SetUniform(const char* name, int i) const
{
	int32_t location = GetLocation(name);
	if (location != -1)
	{
		glCall(glProgramUniform1i(m_id, location, i));
		return true;
	}
	std::string msg = "uniform error ";
	msg += name;
	Logger::LogError(msg.c_str());
	return false;
}

bool graphics::Shader::SetUniform(const char* name, const glm::mat4& mat) const
{
	int32_t location = GetLocation(name);
	if (location != -1)
	{
		glCall(glProgramUniformMatrix4fv(m_id, location, 1, GL_FALSE, glm::value_ptr(mat)));
		return true;
	}
	std::string msg = "uniform error ";
	msg += name;
	Logger::LogError(msg.c_str());
	return false;
}

int32_t graphics::Shader::GetLocation(const char* name) const
{
	int32_t loc;

	glCall(loc = glGetUniformLocation(m_id, name));

	return loc;
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

uint32_t graphics::Shader::CreateProgramShader(const char* filename)
{
	assert(filename != nullptr);

	std::ifstream file(filename);

	assert(file.fail() == false);

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

	std::string msg = "Creation of shader from file ";
	msg += filename;
	msg += " Has completed";
	Logger::LogInfo(msg.c_str());

	return program;
}
