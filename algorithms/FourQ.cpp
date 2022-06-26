#include "FourQ.h"

#ifdef __GNUC__

unsigned long long _umul128(unsigned long long a, unsigned long long b,
						 unsigned long long* c)
{
	unsigned __int128 result{(unsigned __int128)(a) * (unsigned __int128)(b)};
	*c = result >> 64;
	return result;
}

uint64_t __shiftright128(uint64_t LowPart,
   uint64_t HighPart,
   uint64_t Shift)
{
	unsigned __int128 res{(unsigned __int128)(HighPart) << 64 | LowPart};
	return res >> (Shift % 64);
}

uint64_t __shiftleft128(uint64_t LowPart, uint64_t HighPart, uint64_t Shift)
{
	unsigned __int128 res{(unsigned __int128)(HighPart) << 64 | LowPart};
	return (res << (Shift % 64)) >> 64;
}
#endif
