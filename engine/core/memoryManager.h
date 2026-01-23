#pragma once
#include <iostream>

struct AllocationsM
{
	int allocated = 0;
	int freed = 0;

	int arrayAlloc = 0;
	int arrayFree = 0;

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
	std::cout << "Memory Freed: " << size << std::endl;
	thisAlloc.freed += size;
	free(memory);
}

inline void* operator new[](std::size_t size)
{
	std::cout << "Array Allocated!" << size << std::endl;
	thisAlloc.arrayAlloc ++;

	if (void* p = std::malloc(size))
		return p;

	throw std::bad_alloc{};
}

// Is called but doesn't do what I need
inline void operator delete[](void* ptr) noexcept
{
	std::cout << "Array Freed!" << std::endl;
	thisAlloc.arrayFree ++;
	free(ptr);
}


class Arena
{
private:
	byte* buffer = nullptr;
	size_t capacity = 0;
	size_t offset = 0;

public:
	explicit Arena(size_t size);
	~Arena() { free(buffer); }

	// Dont allow copying
	Arena(const Arena&) = delete;
	Arena& operator = (const Arena&) = delete;
};


// https://medium.com/@sgn00/high-performance-memory-management-arena-allocators-c685c81ee338