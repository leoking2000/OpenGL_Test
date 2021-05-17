#include "Application.h"
#include "FrameTimer.h"
#include <string>

Application::Application()
	:
	m_canvas(WIDTH, HEIGHT, { 0, 0, 0 })
{
}

bool Application::Init()
{
	// Set GLFW error callback
	glfwSetErrorCallback(Logger::LogGLFW_Error);

	// Initialize GLFW
	if (!glfwInit())
	{
		Logger::LogError("GLFW could not Initialize.");
		return false;
	}

	// Hits
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Creating a Window.
	m_window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL test", NULL, NULL);
	if (!m_window)
	{
		Logger::LogError("Window creation failed.");
		glfwTerminate();
		return false;
	}

	//Making the OpenGL context current
	glfwMakeContextCurrent(m_window);
	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("GLEW could not Initialize.");
		return false;
	}

	// print OpenGL version
	Logger::LogInfo((const char*)glGetString(GL_VERSION));

	glfwSwapInterval(1);

	// Tell OpenGL how big is the window
	glCall(glViewport(0, 0, WIDTH, HEIGHT));

	game.Init(&m_canvas, m_window);

	InitCanvas();

    return true;
}

int Application::RunMainLoop()
{
	float dt = ft.Mark();

	// Main Loop
	while (!glfwWindowShouldClose(m_window))
	{
		m_canvas.Clear();

		// Update Game
		game.Update(dt);

		// RENDER
		game.Draw();
		RenderCanvas();

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
	// game
	glCall(glDeleteProgram(m_CanvasShader));
	glCall(glDeleteVertexArrays(1, &m_VAO_Canvas));
	glCall(glDeleteBuffers(1, &m_IndixBuffer_Canavas));
	glCall(glDeleteTextures(1, &m_CanvasTexture));

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Application::InitCanvas()
{
	m_CanvasShader = CreateProgramShader("canvas.shader");

	glCall(glGenTextures(1, &m_CanvasTexture));
	glCall(glBindTexture(GL_TEXTURE_2D, m_CanvasTexture));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, m_canvas.__GetData()));

	// VERTEX ARRAY OBJECT
	glCall(glGenVertexArrays(1, &m_VAO_Canvas));
	glCall(glBindVertexArray(m_VAO_Canvas));

	// VERTEX BUFFER
	float VertexBuffer[16] = {
		-1.0f,  1.0f, 0.0f, 0.0f, // top left     0
		 1.0f,  1.0f, 1.0f, 0.0f, // top right    1
		-1.0f, -1.0f, 0.0f, 1.0f, // bottom left  2
		 1.0f, -1.0f, 1.0f, 1.0f   // bottom right 3
	};
	// data
	uint32_t m_VertexBufferID;
	glCall(glGenBuffers(1, &m_VertexBufferID));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
	glCall(glBufferData(GL_ARRAY_BUFFER, 4 * (4 * sizeof(float)), VertexBuffer, GL_STATIC_DRAW));
	// attribouts
	glCall(glEnableVertexAttribArray(0));
	glCall(glEnableVertexAttribArray(1));
	glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
	glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float))  ));

	// INDIX BUFFER
	unsigned int indices[6] = {
			0, 1, 2,
			3, 2, 1
	};
	// data

	glCall(glGenBuffers(1, &m_IndixBuffer_Canavas));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndixBuffer_Canavas));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW));

	// SHADER
	glCall(glUseProgram(m_CanvasShader));

	// uniform
	glCall(int location = glGetUniformLocation(m_CanvasShader, "u_Tex"));
	if (location != -1)
	{
		glCall(glUniform1i(location, 0));
	}
}

void Application::RenderCanvas()
{
	// Update canvas texture
	glCall(glBindTexture(GL_TEXTURE_2D, m_CanvasTexture));
	glCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, m_canvas.__GetData()));

	glCall(int location = glGetUniformLocation(m_CanvasShader, "u_Tex"));
	if (location != -1)
	{
		glCall(glUniform1i(location, 0));
	}

	glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

}
