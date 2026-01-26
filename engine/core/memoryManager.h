#pragma once

#include <cstddef>
#include <iostream>



struct AllocationsM
{
	int allocated = 0;
	int freed = 0;

	int arrayAlloc = 0;
	int arrayFree = 0;

	int MemoryUsed() { return allocated - freed; }
	int ArraysUSed() { return arrayAlloc - arrayFree; }
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
	std::cout << "Array Allocated!" << std::endl;
	thisAlloc.arrayAlloc++;

	if (void* p = std::malloc(size))
		return p;

	throw std::bad_alloc{};
}

inline void operator delete[](void* ptr) noexcept
{
	std::cout << "Array Freed!" << std::endl;
	thisAlloc.arrayFree++;
	free(ptr);
}



class Arena
{
private:
	std::uint8_t* buffer = nullptr;
	size_t capacity = 0;
	size_t offset = 0;

public:
	Arena(size_t size);
	~Arena() { free(buffer); }


	void* Alloc(std::size_t size, std::size_t align = alignof(std::max_align_t));
	void Reset() { offset = 0; }
};
