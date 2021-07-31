#include "Application.h"

int main() 
{
	
	int return_code = -1;

	Core::Application app;

	if (app.Init())
	{
		return_code = app.RunMainLoop();
	}

	app.TerminateApp();


	return return_code;
}

