#pragma once
#include <GL/glew.h>
#include <cinttypes>
#include <assert.h>

void glClearError();
bool glCheckError();

#ifdef _DEBUG
#define glCall(x) glClearError(); x; assert(glCheckError() == false)
#else
#define glCall(x) x
#endif


uint32_t CompileShader(const char* source, uint32_t type);
uint32_t CreateProgramShader(const char* vertexS, const char* fragS);
uint32_t CreateProgramShader(const char* filename);
