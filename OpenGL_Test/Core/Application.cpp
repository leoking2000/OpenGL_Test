#include <GL/glew.h>

#include "Application.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Log.h"
#include <string>

Application::Application(GLFWwindow* window)
	:
	m_window(window)
{
}

bool Application::Init()
{
	glCall(glClearColor(0.0, 0.0, 0.5, 1.0f));
	glCall(glClear(GL_COLOR_BUFFER_BIT));

	// Vertex Array
	glCall(glGenVertexArrays(1, &VertexArray));
	glCall(glBindVertexArray(VertexArray));

	// shader
	ShaderProgram = CreateProgramShader("Shaders/Test.shader");
	glCall(glUseProgram(ShaderProgram));

	Logger::LogInfo("Application has initialized");
    return true;
}

int Application::RunMainLoop()
{
	Logger::LogInfo("Main Loop has started");

	// vertex buffer
	float vertexs[] = {
		0.0f,   0.25f,
	   -0.25f, -0.25f,
		0.25f, -0.25f
	};

	VertexBuffer vb(vertexs, sizeof(vertexs));

	glCall(glEnableVertexAttribArray(0));
	glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

	// index buffer
	uint32_t indices[] = { 0 , 1 , 2 };
	IndexBuffer ib(indices, 3);

	float dt = ft.Mark();
	float dir = 1.0f;
	float offset = 0.0f;

	// Main Loop
	while (!glfwWindowShouldClose(m_window))
	{
		/////////////////////////////////////////////////////////
		glCall(glClear(GL_COLOR_BUFFER_BIT));

		glCall(int location = glGetUniformLocation(ShaderProgram, "u_offset"));
		if (location != -1)
		{
			glCall(glProgramUniform1f(ShaderProgram, location, offset));
		}

		glCall(glDrawElements(GL_TRIANGLES, ib.GetCount() ,GL_UNSIGNED_INT, nullptr));

		if (offset > 0.75f)
		{
			dir = -1.0f;
			offset = 0.75f;
		}
		else if (offset < -0.75)
		{
			dir = 1.0f;
			offset = -0.75f;
		}
		
		offset += dir * dt * 2.0f;

		/////////////////////////////////////////////////////////

		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_window, true);
		}

		if (glfwGetKey(m_window, GLFW_KEY_K) == GLFW_PRESS)
		{
			Logger::LogInfo(std::to_string(1.0f / ft.Mark()).c_str());
		}

		glfwSwapBuffers(m_window);
		glfwPollEvents();

		dt = ft.Mark();
	}

	return 0;
}

void Application::TerminateApp()
{

}

