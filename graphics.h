#pragma once
#include "main.h"
#include "Canvas.h"

/*
namespace graphics
{
	class Sprite
	{
	public:
		Sprite(uint32_t width, uint32_t height)
		{
			m_data = new Color[width * height];
			m_width = width;
			m_height = height;

			float r = 0.0f;

			for (uint32_t y = 0; y < height; y++)
			{
				r += 1.0f / float(height);
				if (r >= 1.0f) r = 1.0f;

				for (uint32_t x = 0; x < width; x++)
				{
					Color c = { 0.0f, float(x) / float(width), float(y) / float(height) };
					PutPixel(x, y, c);
				}
			}

			glCall(glGenTextures(1, &gl_ID));
			glCall(glBindTexture(GL_TEXTURE_2D, gl_ID));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, m_width, m_height, 0, GL_RGB, GL_FLOAT, m_data));

		}
		~Sprite()
		{
			delete m_data;
			glCall(glDeleteTextures(1, &gl_ID));
		}

		void Update()
		{
			glCall(glBindTexture(GL_TEXTURE_2D, gl_ID));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, m_width, m_height, 0, GL_RGB, GL_FLOAT, m_data));

			glCall(glBindTexture(GL_TEXTURE_2D, 0));
		}

		void PutPixel(uint32_t x, uint32_t y, const Color& c)
		{
			m_data[y * m_width + x] = c;
		}

		Color GetPixel(uint32_t x, uint32_t y)
		{
			return m_data[y * m_width + x];
		}

		void Bind() const
		{
			glCall(glActiveTexture(GL_TEXTURE0));
			glCall(glBindTexture(GL_TEXTURE_2D, gl_ID));
		}

		void UnBind() const
		{
			glCall(glBindTexture(GL_TEXTURE_2D, 0));
		}

		uint32_t GetWidth()
		{
			return m_width;
		}
		uint32_t GetHeight()
		{
			return m_height;
		}

	private:
		Color* m_data = nullptr;
		uint32_t m_width; 
		uint32_t m_height;

		uint32_t gl_ID;
	};

	class GameObject
	{
	public:
		GameObject(const Vec2& in_pos)
		{
			m_pos = in_pos;
			m_color = {0.0f, 0.0f, 0.0f};
			m_ShaderProgram = CreateProgramShader("Tex1.shader");

			s = new Sprite(100, 100);
			Init();

		}
		GameObject(const Vec2& in_pos, const Color& in_color, uint32_t in_ShaderProgram)
		{
			m_pos = in_pos;
			m_color = in_color;
			m_ShaderProgram = in_ShaderProgram;

			Init();
		}
		~GameObject()
		{
			//glCall(glDeleteProgram(m_ShaderProgram));
			glCall(glDeleteVertexArrays(1, &m_VAO));
			glCall(glDeleteBuffers(1, &m_IndixBufferID));

			delete s;
		}

		void Translate_X(float dx) {
			m_pos.x += dx;
		}
		void Translate_Y(float dy) {
			m_pos.y += dy;
		}

		void Update()
		{

			if (m_color.r >= 1.0f)
			{
				dir_R_color = dir_R_color > 0.0f ? -dir_R_color : dir_R_color;
			}
			else if (m_color.r <= 0.0f)
			{
				dir_R_color = dir_R_color < 0.0f ? -dir_R_color : dir_R_color;
			}

			m_color.r += dir_R_color;

			if (s != nullptr)
			{
				for (uint32_t y = 0; y < s->GetHeight(); y++)
				{
					for (uint32_t x = 0; x < s->GetWidth(); x++)
					{
						Color c = s->GetPixel(x,y);
						c.r = m_color.r;
						s->PutPixel(x, y, c);
					}
				}
				s->Update();
			}

		}

		void Draw()
		{
			glCall(glUseProgram(m_ShaderProgram));
			glCall(glBindVertexArray(m_VAO));
			glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndixBufferID));

			int location;

			glCall(location = glGetUniformLocation(m_ShaderProgram, "u_offset"));
			if (location != -1)
			{
				glCall(glUniform4f(location, m_pos.x, m_pos.y, 0.0f, 0.0f));
			}

			if (s == nullptr)
			{
				glCall(location = glGetUniformLocation(m_ShaderProgram, "u_color"));
				if (location != -1)
				{
					glCall(glUniform4f(location, m_color.r, m_color.g, m_color.b, 0.0f));
				}
			}
			else
			{
				s->Bind();
				glCall(location = glGetUniformLocation(m_ShaderProgram, "u_Tex"));
				if (location != -1)
				{
					glCall(glUniform1i(location, 0));
				}
			}

			// Draw
			glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
		}


	private:
		float dir_R_color = 0.01f;
		Color m_color;
		Sprite* s = nullptr;
		Vec2 m_pos;

		uint32_t m_VAO;
		uint32_t m_IndixBufferID;
		uint32_t m_ShaderProgram;
	private:
		void Init()
		{
			// VERTEX ARRAY OBJECT
			glCall(glGenVertexArrays(1, &m_VAO));
			glCall(glBindVertexArray(m_VAO));

			// VERTEX BUFFER
			graphics::Vertex VertexBuffer[4] = {
				{-0.25f,  0.25f, 1.0f, m_color, {0.0f, 0.0f}}, // top left     0
				{ 0.25f,  0.25f, 1.0f, m_color, {1.0f, 0.0f}}, // top right    1
				{-0.25f, -0.25f, 1.0f, m_color, {0.0f, 1.0f}}, // bottom left  2
				{ 0.25f, -0.25f, 1.0f, m_color, {1.0f, 1.0f}}  // bottom right 3
			};
			// data
			uint32_t m_VertexBufferID;
			glCall(glGenBuffers(1, &m_VertexBufferID));
			glCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
			glCall(glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(graphics::Vertex), VertexBuffer, GL_STATIC_DRAW));
			// attribouts
			glCall(glEnableVertexAttribArray(0));
			glCall(glEnableVertexAttribArray(1));
			glCall(glEnableVertexAttribArray(2));
			glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(graphics::Vertex), 0));
			glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(graphics::Vertex), (const void*)offsetof(graphics::Vertex, color)));
			glCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(graphics::Vertex), (const void*)offsetof(graphics::Vertex, Tex_cord)));

			// INDIX BUFFER
			unsigned int indices[6] = {
					0, 1, 2,
					3, 2, 1
			};
			// data

			glCall(glGenBuffers(1, &m_IndixBufferID));
			glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndixBufferID));
			glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

			// SHADER
			glCall(glUseProgram(m_ShaderProgram));

			// uniform
			int location;
			if (s == nullptr)
			{
				glCall(location = glGetUniformLocation(m_ShaderProgram, "u_color"));
				if (location != -1)
				{
					glCall(glUniform4f(location, m_color.r, m_color.g, m_color.b, 0.0f));
				}
			}
			else
			{
				s->Bind();
				glCall(location = glGetUniformLocation(m_ShaderProgram, "u_Tex"));
				if (location != -1)
				{
					glCall(glUniform1i(location, 0));
				}
			}

			glCall(location = glGetUniformLocation(m_ShaderProgram, "u_offset"));
			if (location != -1)
			{
				glCall(glUniform4f(location, m_pos.x, m_pos.y, 0.0f, 0.0f));
			}

			glCall(glBindVertexArray(0));
			glCall(glUseProgram(0));
			glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}
	};
}
*/
