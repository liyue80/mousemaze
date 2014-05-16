/*
 *
 */
#include <string.h>
#include "StandardSpace.h"

GStandardSpace * GStandardSpace_Create(u32 width, u32 height)
{
	GStandardSpace * ptr = (GStandardSpace *)mem_alloc(sizeof(GStandardSpace) + width * height * sizeof(u32));

	ptr->mapSize.width = width;
	ptr->mapSize.height = height;

	ptr->distanceMap = ptr->extData;

	memset(ptr->distanceMap, 0xFF, width * height * sizeof(u32));

	return ptr;
}

void GStandardSpace_GetSpaceSize(const GStandardSpace * This, u32 * width, u32 * height)
{
	*width = This->mapSize.width;
	*height = This->mapSize.height;
}

bool GStandardSpace_SetDistance(GStandardSpace * This, u32 x, u32 y, u32 distance)
{
	u32 offset = This->mapSize.width * y + x;

	if (This->distanceMap[offset] <= distance)
		return false;

	This->distanceMap[offset] = distance;

	return true;
}
