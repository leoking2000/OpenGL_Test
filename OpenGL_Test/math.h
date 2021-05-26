#pragma once

template<class T>
T Interpolate(const T& a, const T& b, float alpha)
{
	return a + (b - a) * alpha;
}


