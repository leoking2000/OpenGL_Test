#include "utilities.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cinttypes>
#include <assert.h>

#include <malloc.h>
#include <fstream>
#include <string>
#include <sstream>

#include "Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

uint32_t CompileShader(const char* source, uint32_t type)
{
	glClearError();
	uint32_t id = glCreateShader(type);

	glCall(glShaderSource(id, 1, &source, nullptr));
	glCall(glCompileShader(id));

	int resalt;
	glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &resalt));
	if (resalt == GL_FALSE)
	{
		Logger::LogError(type == GL_VERTEX_SHADER ? "VERTEX SHADER COMPILE ERROR" : "FRAGMENT SHADER COMPILE ERROR");
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

uint32_t CreateProgramShader(const char* vertexS, const char* fragS)
{
	glClearError();
	uint32_t programid = glCreateProgram();

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

uint32_t CreateProgramShader(const char* filename)
{
	std::ifstream file(filename);

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

	return CreateProgramShader(ss[0].str().c_str(), ss[1].str().c_str());
}

void glClearError()
{
	while (glGetError());
}

bool glCheckError()
{
	bool haserror = false;
	while (GLenum error = glGetError())
	{
		Logger::LogError(std::to_string(error).c_str());
		haserror = true;
	}

	return haserror;
}
