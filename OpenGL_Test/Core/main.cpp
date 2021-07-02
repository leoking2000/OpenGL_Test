#include "Application.h"

int main() 
{
	Application app;
	int return_code = -1;

	if (app.Init())
	{
		return_code = app.RunMainLoop();
	}

	app.TerminateApp();
	
	return return_code;
}

