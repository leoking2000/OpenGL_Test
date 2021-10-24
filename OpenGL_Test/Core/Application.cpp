#include "Application.h"

#include "graphics/Renderer.h"

#include "Tests/Light_Test.h"

#include "Log.h"
#include <string>

using namespace graphics;

Core::Application::Application()
{
}

bool Core::Application::Init()
{
	if(!Platform::CreateWindow(1600, 900, "OpenGL Test", true))
	{
		Logger::LogError("Can't open window for some reson\n");
		return false;
	}
	/////////////////////////////////////////////////////////

	tests.push_back(new Light_Test());

	/////////////////////////////////////////////////////////
	Logger::LogInfo("Application has initialized");
    return true;
}

int Core::Application::RunMainLoop()
{
	Logger::LogInfo("Main Loop has started");

	float dt = ft.Mark();

	// Main Loop
	while (Platform::isRunning())
	{	
		Platform::BeginFrame();

		Renderer::Clear();

		tests[current_test_index]->Update(dt);
		tests[current_test_index]->Draw();
		tests[current_test_index]->ImGui();

		if (Platform::KeyIsPress(Platform::KEY_TAB))
		{
			if (tab_press == false)
			{
				current_test_index = (current_test_index + 1) % tests.size();
				tab_press = true;
			}
		}
		else
		{
			tab_press = false;
		}

		if (Platform::KeyIsPress(Platform::KEY_ESCAPE))
		{
			Platform::Stop(); // causes the Platform::isRunning() to retrun false;
		}

		Platform::EndFrame();

		dt = ft.Mark();
	}

	return 0;
}

void Core::Application::TerminateApp()
{

	for (Test* p : tests)
	{
		delete p;
	}

	Renderer::CleanUp();
	Platform::CleanUp();
}

