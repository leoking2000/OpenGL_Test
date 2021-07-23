#pragma once

namespace Core
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void Update(float dt) {}
		virtual void Draw() {}
		virtual void ImGui() {}
	};
}