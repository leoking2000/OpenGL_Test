#pragma once
#include "Transform.h"

template<class Vertex>
class DefaultVertexShader
{
public:
	typedef typename Vertex Output;
public:
	void BindTransform(graphics::Transform& transform_in)
	{
		transform = &transform_in;
	}
	Output operator()(const Vertex& in) const
	{
		Output out(in.pos, in);
		graphics::Transform::TransformVertex(out, *transform);

		return out;
	}
public:
	graphics::Transform* transform;
};