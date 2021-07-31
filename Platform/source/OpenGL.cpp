#include "OpenGL.h"
#include <string>
#include "Log.h"

bool InitOpenGL()
{
	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("GLEW could not Initialize.");
		return false;
	}

	return true;
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