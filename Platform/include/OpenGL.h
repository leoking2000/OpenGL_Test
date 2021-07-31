#pragma once
#include <GL/glew.h>
#include <assert.h>

/*
*  Initialize GLEW 
*  
*  returns true only if glewInit() retruns GLEW_OK.
*/
bool InitOpenGL();

void glClearError(); // if we don't have valid opengl contex it will loop forever.
bool glCheckError(); // if we don't have valid opengl contex it will loop forever.

#ifdef _DEBUG
#define glCall(x) glClearError(); x; assert(glCheckError() == false)
#else
#define glCall(x) x
#endif