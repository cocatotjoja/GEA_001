//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "spacegameapp.h"

int
main(int argc, const char** argv)
{
	//Memory Leak Tests
	int* x = new int;
	delete x;
	int* array = new int[1000000];
	delete[] array;

	std::cout << std::endl;

	//Arena Allocator Test
	Arena arena(1024);

	std::cout << std::endl;

	// Test normal alloc
	void* a = arena.Alloc(16, 8);
	if (reinterpret_cast<std::uintptr_t>(a) % 8 == 0)
	{
		std::cout << "Alloc succeded!" << std::endl;
	}
	else
	{
		std::cout << "Alloc failed :(" << std::endl;
	}

	std::cout << std::endl;

	// Test another alloc with larger size and alignment
	void* b = arena.Alloc(32, 16);
	if (reinterpret_cast<std::uintptr_t>(b) % 16 == 0)
	{
		std::cout << "Alloc succeded!" << std::endl;
	}
	else
	{
		std::cout << "Alloc failed :(" << std::endl;
	}

	std::cout << std::endl;

	// Test loop of multiple allocs
	for (size_t i = 0; i < 12; i++)
	{
		void* c = arena.Alloc(7, 4);
		if (reinterpret_cast<std::uintptr_t>(c) % 4 == 0)
		{
			std::cout << "Alloc " << i << " succeded!" << std::endl;
		}
		else
		{
			std::cout << "Alloc " << i << " failed :(" << std::endl;
		}
	}

	std::cout << std::endl;

	// Test alloc that should fail
	void* d = arena.Alloc(1500, 4);
	if (d == nullptr)
	{
		std::cout << "Alloc failed correctly" << std::endl;
	}
	else
	{
		std::cout << "Alloc failed to fail 0.0" << std::endl;
	}

	std::cout << std::endl;

	// Test alloc for int ptr
	int* e = (int*)arena.Alloc(sizeof(int), alignof(int));
	if (reinterpret_cast<std::uintptr_t>(e) % 4 == 0)
	{
		std::cout << "Alloc succeded!" << std::endl;
	}
	else
	{
		std::cout << "Alloc failed :(" << std::endl;
	}

	std::cout << std::endl;

	std::cout << std::endl;





	// Game loop
	Game::SpaceGameApp app;
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
	
}