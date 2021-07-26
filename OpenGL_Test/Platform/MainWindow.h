#pragma once
#include <cinttypes>

namespace Core
{
	enum KEY
	{
		KEY_W,
		KEY_S,
		KEY_A,
		KEY_D,
		KEY_X,

		KEY_TAB,
		KEY_ESCAPE
	};

	/*
	*  if the function is called a second time, assert(false) is called.
	*/
	bool CreateWindow(uint32_t width, uint32_t height, const char* win_name, bool resizable);

	void DestroyWindow();

	uint32_t GetWidth();
	uint32_t GetHeight();

	void SetMouseVisibility(bool visible);

	double GetMouseX();
	double GetMouseY();

	bool KeyIsPress(KEY key);

	void Resize(uint32_t width, uint32_t height);


	void* GetHandle();
}


