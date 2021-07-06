#include "Log.h"
#include <stdio.h>

// #define print(...) printf(__VA_ARGS__);

namespace Logger
{
	void LogInfo(const char* msg)
	{
		printf("[INFO] %s \n", msg);
	}
	void LogError(const char* msg)
	{
		printf("[ERROR] %s \n", msg);
	}
	void LogGLFW_Error(int error, const char* msg)
	{
		printf("[ERROR]  GLFW Error code: %i %s \n", error, msg);
	}
}
