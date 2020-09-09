#pragma once

#include <string.h>

class Memory
{
public:

	static int MemCpy(void* const destination, unsigned long const destinationSize, void const* const source, unsigned long const sourceSize)
	{
// GCC doesn't have memcpy_s defined, doing some hacky code gymnastics to still be able to use _s version when building testing locally
// but using normal memcpy version when building on linux or in travis ci
#ifdef __GNUC__
		return memcpy(destination, source, sourceSize) != NULL;
#else
		return memcpy_s(destination, destinationSize, source, sourceSize);
#endif
	}

private:

	// No instances
	Memory() {}
	~Memory() {}
};
