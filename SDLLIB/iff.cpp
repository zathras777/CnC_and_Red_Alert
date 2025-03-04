#include <stdio.h>
#include "iff.h"

unsigned long Uncompress_Data(void const *src, void *dst)
{
	unsigned int skip;			// Number of leading data to skip.
	CompressionType method;		// Compression method used.
	unsigned long uncomp_size;

	if (!src || !dst) return 0;

    auto head = (CompHeaderType*)src;

	/*
	**	Interpret the data block header structure to determine
	**	compression method, size, and skip data amount.
	*/
	uncomp_size = ((CompHeaderType*)src)->Size;
	skip = ((CompHeaderType*)src)->Skip;

	method = (CompressionType) ((CompHeaderType*)src)->Method;
	src = Add_Long_To_Pointer((void *)src, (long)sizeof(CompHeaderType) + (long)skip);


	switch (method) {

		default:
		case NOCOMPRESS:
			Mem_Copy((void *) src, dst, uncomp_size);
			break;

		case HORIZONTAL:
			break;

		case LCW:
			LCW_Uncompress((void *) src, (void *) dst, (unsigned long) uncomp_size);
			break;
	}

	return 0;
}

extern "C" int LCW_Comp(void const *source, void *dest, int length)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}