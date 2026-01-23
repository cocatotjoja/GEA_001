#include "config.h"
#include "memoryManager.h"

AllocationsM thisAlloc = AllocationsM();
/*
Arena::Arena(size_t size)
{
	capacity = size;
	buffer = static_cast<byte*>(malloc(capacity));
	assert(buffer && "Failed to allocate Arena");
}
*/

template<typename TYPE>
void Allocate()
{
	static_assert(std::is_trivial(TYPE));

	size_t size = sizeof(TYPE);
	size_t align = alignof(TYPE);
}


|iiii----dddddddd------------------|
 ^
 offset
 ^
 buffer