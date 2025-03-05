#include "shape.h"

char  *_ShapeBuffer;
long _ShapeBufferSize;

int Extract_Shape_Count(void const *buffer)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return 0;
}

void * Extract_Shape(void const *buffer, int shape)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    return NULL;
}

void Set_Shape_Buffer(void *buffer, int size)
{
   _ShapeBuffer = (char *)buffer;
   _ShapeBufferSize = size;
}