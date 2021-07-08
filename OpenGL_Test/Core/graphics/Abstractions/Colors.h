#pragma once
#include <cinttypes>

namespace graphics
{
	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
}

namespace Colors
{
	static constexpr graphics::Color MakeRGB(uint8_t r, uint8_t g, uint8_t b)
	{
		return { r, g, b, 1 };
	}
	static constexpr graphics::Color White = MakeRGB(255u, 255u, 255u);
	static constexpr graphics::Color Black = MakeRGB(0u, 0u, 0u);
	static constexpr graphics::Color Gray = MakeRGB(0x80u, 0x80u, 0x80u);
	static constexpr graphics::Color LightGray = MakeRGB(0xD3u, 0xD3u, 0xD3u);
	static constexpr graphics::Color Red = MakeRGB(255u, 0u, 0u);
	static constexpr graphics::Color Green = MakeRGB(0u, 255u, 0u);
	static constexpr graphics::Color Blue = MakeRGB(0u, 0u, 255u);
	static constexpr graphics::Color Yellow = MakeRGB(255u, 255u, 0u);
	static constexpr graphics::Color Cyan = MakeRGB(0u, 255u, 255u);
	static constexpr graphics::Color Magenta = MakeRGB(255u, 0u, 255u);
}

