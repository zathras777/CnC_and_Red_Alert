#include "function.h"

void *Conquer_Build_Fading_Table(void const *palette, void *dest, int color, int frac)
{
	printf("%s\n", __func__);
	return dest;
}

void Fat_Put_Pixel(int x, int y, int color, int size, GraphicViewPortClass &gpage)
{
	gpage.Fill_Rect(x, y, x + size, y + size, color);
}

// from RA readline.cpp
void strtrim(char * buffer)
{
	if (buffer) {

		/*
		**	Strip leading white space from the string.
		*/
		char * source = buffer;
		while (isspace(*source)) {
			source++;
		}
		if (source != buffer) {
			int len = strlen(source);
			memmove(buffer, source, len + 1);
		}

		/*
		**	Clip trailing white space from the string.
		*/
		for (int index = strlen(buffer)-1; index >= 0; index--) {
			if (isspace(buffer[index])) {
				buffer[index] = '\0';
			} else {
				break;
			}
		}
	}
}
