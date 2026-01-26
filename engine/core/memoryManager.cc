#include "config.h"
#include "memoryManager.h"


AllocationsM thisAlloc = AllocationsM();

Arena::Arena(size_t size)
{
	capacity = size;
	buffer = static_cast<std::uint8_t*>(malloc(capacity));
	std::cout << "Arena Created!" << std::endl;
}

void* Arena::Alloc(std::size_t size, std::size_t align)
{
	// Prevent division(modulus) by zero
	if (align == 0)
	{
		align = alignof(std::max_align_t);
	}

	// Assure alignment
	std::size_t newOffset = offset + (align - (offset % align)) % align;

	// Chcek if enough space
	if (newOffset + size > capacity)
	{
		return nullptr;
	}

	// Create return address
	void* returnPTR = buffer + newOffset;

	// Update offset
	offset = newOffset + size;

	return returnPTR;
}