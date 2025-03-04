#include <stdio.h>

#include "dipthong.h"

char *Extract_String(void const *data, int string)
{
	unsigned short int	const *ptr;
	unsigned intoffset;

	if (!data || string < 0) return(NULL);
		
	ptr = (unsigned short int const *)data;
	return (((char*)data) + ptr[string]);
}