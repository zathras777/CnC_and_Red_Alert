#include <stdio.h>
#include "iff.h"

unsigned long Uncompress_Data(void const *src, void *dst)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

extern "C" int LCW_Comp(void const *source, void *dest, int length)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

unsigned long LCW_Uncompress(void *source, void *dest, unsigned long length)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}