#include "Application.h"
#include <iostream>

int main() 
{
	Application app;
	int return_code = -1;

	if (app.Init())
	{
		return_code = app.RunMainLoop();
	}

	app.TerminateApp();

	std::cin.get();
	
	return return_code;
}

