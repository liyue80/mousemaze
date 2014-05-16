/*
 *
 */
#include <string.h>
#include "StandardSpace.h"

void GStandardSpace_Initialize(GStandardSpace * This)
{
	memset(This, 0xFF, sizeof(GStandardSpace));
}

bool GStandardSpace_SetDistance(GStandardSpace * This, u32 x, u32 y, u32 distance)
{
	if (This->distanceMap[y][x] <= distance)
		return false;

	This->distanceMap[y][x] = distance;

	return true;
}
