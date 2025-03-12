#include <stdlib.h>

#include "tile.h"

void *Get_Icon_Set_Map(void const *iconset)
{
	if(iconset)
		return (char *)iconset + ((IControl_Type *)iconset)->Map;
	return NULL;
}