#include <stdint.h>

#include "buffer.h"

BufferClass::BufferClass(long size) : Buffer(new uint8_t[size]), Size(size), Allocated(true)
{
}

BufferClass::BufferClass() : Buffer(NULL), Size(0), Allocated(false)
{
}

BufferClass::~BufferClass()
{
    if(Allocated)
		delete[] (uint8_t *)Buffer;
}