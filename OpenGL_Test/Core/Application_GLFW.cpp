#include "Application.h"
#include "GLFW/glfw3.h"

#include "graphics/Renderer.h"

#include "utilities/imgui/imgui.h"
#include "utilities/imgui/imgui_impl_glfw.h"
#include "utilities/imgui/imgui_impl_opengl3.h"

#include "Tests/TextureCube_Test.h"
#include "Tests/Light_Test.h"

#include "utilities/Log.h"
#include <string>

using namespace graphics;

Core::Application::Application()
{
}

bool Core::Application::Init()
{
	if(!CreateWindow(1600, 900, "OpenGL Test", true))
	{
		return false;
	}
	Renderer::Init();
	/////////////////////////////////////////////////////////

	tests.push_back(new Light_Test());
	tests.push_back(new TextureCube_Test());


	/////////////////////////////////////////////////////////
	Logger::LogInfo("Application has initialized");
    return true;
}

int Core::Application::RunMainLoop()
{
	Logger::LogInfo("Main Loop has started");

	float dt = ft.Mark();
	GLFWwindow* window = (GLFWwindow*)GetHandle();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		/////////////////////////////////////////////////////////
		Renderer::Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		tests[current_test_index]->Update(dt);
		tests[current_test_index]->Draw();
		tests[current_test_index]->ImGui();

	    ////////////////////////////////////////////////////////

		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
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

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		/////////////////////////////////////////////

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

		dt = ft.Mark();
	}

	return 0;
}

void Core::Application::TerminateApp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	for (Test* p : tests)
	{
		delete p;
	}

	DestroyWindow();
}

