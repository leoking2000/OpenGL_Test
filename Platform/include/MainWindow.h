#pragma once
#include <cinttypes>

namespace Platform
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

	bool CreateWindow(uint32_t width, uint32_t height, const char* win_name, bool resizable);

	bool isRunning();
	void BeginFrame();
	void EndFrame();

	void Stop(); // causes the isRunning() to retrun false;

	void CleanUp();

	uint32_t GetWidth();
	uint32_t GetHeight();

	void SetMouseVisibility(bool visible);

	double GetMouseX();
	double GetMouseY();

	bool KeyIsPress(KEY key);

	void Resize(uint32_t width, uint32_t height);

}


