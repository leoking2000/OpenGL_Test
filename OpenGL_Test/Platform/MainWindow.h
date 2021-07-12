#pragma once
#include <cinttypes>

namespace Core
{
	struct MainWindow;

	/*
	*  if the function is called a second time, assert(true) is called.
	*/
	bool CreateWindow(uint32_t width, uint32_t height, const char* win_name, bool resizable);

	void DestroyWindow();

	uint32_t GetWidth();
	uint32_t GetHeight();

	void* GetHandle();

	void Resize(uint32_t width, uint32_t height);
}


