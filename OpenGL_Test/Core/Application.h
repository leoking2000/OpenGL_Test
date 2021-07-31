#include "MainWindow.h"
#include "FrameTimer.h"
#include "Tests/Test.h"
#include <vector>

namespace Core
{
	class Application
	{
	public:
		Application();
		bool Init();
		int RunMainLoop();
		void TerminateApp();

	private:
		FrameTimer ft;

		std::vector<Test*> tests;
		int current_test_index = 0;

		bool tab_press = false;
	};
}



