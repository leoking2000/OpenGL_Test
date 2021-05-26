#pragma once
#include "Colors.h"

class Texture
{
public:
	Texture(const char* file_name );
	~Texture();

	int GetWidth() const;
	int GetHeight() const;

	void Load(const char* file_name);

	//void PutPixel(int x, int y, const graphics::Color& c);
	graphics::Color GetPixel(int x, int y) const;

	graphics::Color* __GetData();
private:
	int m_width;
	int m_height;
	int m_bpp;

	unsigned char* m_data = nullptr;
};

