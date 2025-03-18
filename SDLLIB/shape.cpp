#include "shape.h"

char  *_ShapeBuffer;
long _ShapeBufferSize;

int Extract_Shape_Count(void const *buffer)
{
	ShapeBlock_Type *block = (ShapeBlock_Type *)buffer;
	return block->NumShapes;
}

void * Extract_Shape(void const *buffer, int shape)
{
	ShapeBlock_Type *block = (ShapeBlock_Type*) buffer;
	int numshapes; // Number of shapes
	long offset; // Offset of shape data, from start of block
	char *bytebuf = (char*) buffer;

	/*
	----------------------- Return if invalid argument -----------------------
	*/
	if (!buffer || shape < 0 || shape >= block->NumShapes)
		return NULL;

	offset = block->Offsets[shape];

	return bytebuf + 2 + offset;
}

void Set_Shape_Buffer(void *buffer, int size)
{
   _ShapeBuffer = (char *)buffer;
   _ShapeBufferSize = size;
}