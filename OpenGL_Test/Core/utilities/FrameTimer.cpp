#include "FrameTimer.h"

using namespace std::chrono; // oof

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::Mark()
{
	const steady_clock::time_point old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;

	return frameTime.count();
}

