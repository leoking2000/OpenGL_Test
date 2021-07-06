#include "Platform/MainWindow.h"
#include "utilities/FrameTimer.h"

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
	};
}



