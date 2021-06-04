#pragma once
#include "Scene.h"

#include "TextureEffect.h"

class CubeWithTexture : public Scene
{
public:
	CubeWithTexture(const char* path_texture);
	void Init(graphics::Canvas* in_canvas, GLFWwindow* in_window) override;

	void Update(float dt) override;
	void Draw() override;
private:
	graphics::Texture tex;
	graphics::Mesh<graphics::TextureEffect::Vertex> cube;
	graphics::Transform cubetransform;
	graphics::Graphics<graphics::TextureEffect> gfx;

	GLFWwindow* window;
};

