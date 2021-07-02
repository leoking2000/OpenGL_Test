#pragma once

namespace Logger
{
	void LogInfo(const char* msg);
	void LogError(const char* msg);
	void LogGLFW_Error(int error, const char* msg);
}
