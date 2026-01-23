//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "spacegameapp.h"

int
main(int argc, const char** argv)
{
	// NEW[] and DELETE[] test
	int* arr = new int[1000000];
	delete[] arr; // Doesn't get called

	Game::SpaceGameApp app;
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
	
}