#pragma once
#include <vector>

template<class Vertex>
class DefaultGeometryShader
{
public:
	typedef Vertex Output;
public:
	std::vector<Output> operator()(const Vertex& in0, const Vertex& in1, const Vertex& in2, size_t triangle_index) const
	{
		return{ in0,in1,in2 };
	}
};