#pragma once
#include <iostream>

struct AllocationsM
{
	int allocated = 0;
	int freed = 0;

	int current() { return allocated - freed; }
};

extern AllocationsM thisAlloc;

inline void* operator new(size_t size)
{
	//std::cout << "Memory Allocated: " << size << std::endl;
	thisAlloc.allocated += size;
	void* memory = malloc(size);
	return memory;
}

inline void operator delete(void* memory, size_t size)
{
	//std::cout << "Memory Freed: " << size << std::endl;
	thisAlloc.freed += size;
	free(memory);
}

inline void* operator new[](std::size_t size)
{
	//std::cout << "Memory Allocated: " << size << std::endl;
	thisAlloc.allocated += size;

	if (void* p = std::malloc(size))
		return p;

	throw std::bad_alloc{};
}

inline void operator delete[](void* ptr, size_t size) noexcept
{
	//std::cout << "Memory Freed: " << size << std::endl;
	thisAlloc.freed += size;
	free(ptr);
}

