#pragma once
#include "Colors.h"

namespace graphics
{
	class Texture
	{
	public:
		Texture(uint32_t width, uint32_t height); // black
		Texture(uint32_t width, uint32_t height, const Color& c);
		Texture(const char* file_name);
		~Texture();

		int GetWidth() const;
		int GetHeight() const;

		void Load(const char* file_name);
		void Clear(const Color& c);

		void PutPixel(int x, int y, const graphics::Color& c);
		graphics::Color GetPixel(int x, int y) const;

		void Bind(uint32_t slot = 0) const;
		void UnBind() const;

		void UpdateGPUData();

	private:
		void UploadToGPU();
	private:
		int m_width;
		int m_height;

		uint32_t m_id;
		Color* m_data;
	};
}



