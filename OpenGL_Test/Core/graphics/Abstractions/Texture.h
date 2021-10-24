#pragma once
#include "Colors.h"
#include <string>

namespace graphics
{
	class Texture
	{
	public:
		Texture(uint32_t width, uint32_t height); // black
		Texture(uint32_t width, uint32_t height, const Color& c);
		Texture(const char* file_name);

		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;

		Texture(Texture&& other);
		Texture& operator=(Texture&& other);

		~Texture();

		inline uint32_t GetWidth() const  { return m_width; }
		inline uint32_t GetHeight() const { return m_height; }
		inline const std::string& GetName() const { return m_name; }

		void Load(const char* file_name);
		void Clear(const Color& c);

		void PutPixel(int x, int y, const Color& c);
		Color GetPixel(int x, int y) const;

		void Bind(uint32_t slot = 0) const;
		void UnBind() const;

		void UpdateGPUData();

	private:
		void UploadToGPU();
	private:
		uint32_t m_width;
		uint32_t m_height;

		uint32_t m_id = 0;
		Color* m_data = nullptr;

		std::string m_name;
	};
}



