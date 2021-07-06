#include "Application.h"

#include "utilities/utilities.h"
#include "utilities/Log.h"

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

