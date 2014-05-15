/*
 *
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ParallelSpace.h"

/* Convert (x,y) to offset in _roadmap */
static u32 GParallelSpace_Offset(const GParallelSpace * This, u32 x, u32 y);
static Position GParallelSpace_Coords(const GParallelSpace * This, u32 offset);
static GParallelSpace * GParallelSpace_Duplicate(const GParallelSpace * This);

GParallelSpace * GParallelSpace_Create(GStandardSpace * pStandardSpace)
{
	u32 width = 0;
	u32 height = 0;
	GParallelSpace * ptr = NULL;

	GStandardSpace_GetSpaceSize(pStandardSpace, &width, &height);

	ptr = (GParallelSpace*)malloc(sizeof(GParallelSpace) + width * height);

	ptr->standardSpace = pStandardSpace;
	ptr->roadmap = ptr->extData;
	ptr->distance = 0;

	return ptr;
}

void GFastDeque_Destory(GParallelSpace * This)
{
	free(This);
}

void GParallelSpace_InitializeTable(GParallelSpace * This, LPCSTR mapInitStr)
{
	u32 width = 0;
	u32 height = 0;
	u32 allocSize = 0;

	GStandardSpace_GetSpaceSize(This->standardSpace, &width, &height);
	allocSize = width * height;
    memcpy(This->roadmap, mapInitStr, allocSize);
}

void GParallelSpace_InitializeEntry(GParallelSpace * This, u32 x, u32 y)
{
    This->currentPos.x = x;
    This->currentPos.y = y;
	This->roadmap[GParallelSpace_Offset(This, This->currentPos.x, This->currentPos.y)] = '2';
}

GParallelSpace * GParallelSpace_Move(const GParallelSpace * This, Direction dir)
{
	GParallelSpace * dupSpace;
    Position test = This->currentPos;
	u32 offset;
	u32 width;
	u32 height;

	GStandardSpace_GetSpaceSize(This->standardSpace, &width, &height);

	switch (dir)
    {
        case LEFT:
            if (This->currentPos.x == 0)
                return NULL;
            test.x--;
            break;
        case UP:
            if (This->currentPos.y == 0)
                return NULL;
            test.y--;
			break;
        case RIGHT:
            if (This->currentPos.x + 1 >= width)
                return NULL;
            test.x++;
            break;
        case DOWN:
            if (This->currentPos.y + 1 >= height)
                return NULL;
            test.y++;
            break;
        default: assert(0);
    }

	offset = GParallelSpace_Offset(This, test.x, test.y);
	if (This->roadmap[offset] != '1')
        return NULL;

	if (!GStandardSpace_SetDistance(This->standardSpace, test.x, test.y, This->distance+1))
		return NULL;

	dupSpace = GParallelSpace_Duplicate(This);
	dupSpace->roadmap[offset] = '2';
	dupSpace->currentPos = test;
	dupSpace->distance ++;
    return dupSpace;
    
}

bool GParallelSpace_TestGoal(const GParallelSpace * This, u32 x, u32 y)
{
    return (This->currentPos.x == x) && (This->currentPos.y == y);
}

LPCSTR GParallelSpace_Output(const GParallelSpace * This)
{
	static char staticstring[4096] = {0};
	u32 width;
	u32 height;
#ifdef _DEBUG
	u32 i = 0;
	char * ptr = staticstring;
#endif

	GStandardSpace_GetSpaceSize(This->standardSpace, &width, &height);

#ifdef _DEBUG
	for (i=0; i<height; i++)
	{
		memcpy(ptr, &This->roadmap[GParallelSpace_Offset(This, 0, i)], width);
		ptr += width;
		*ptr++ = 0x0D;
		*ptr++ = 0x0A;
	}

	*ptr = '\0';
#else
	memcpy(staticstring, This->roadmap, width * height);
	staticstring[width * height] = '\0';
#endif

	return staticstring;
}

static u32 GParallelSpace_Offset(const GParallelSpace * This, u32 x, u32 y)
{
	u32 width, height;
	GStandardSpace_GetSpaceSize(This->standardSpace, &width, &height);
	return (width * y + x);
}

static GParallelSpace * GParallelSpace_Duplicate(const GParallelSpace * This)
{
	u32 width, height;
	GParallelSpace * ptr = GParallelSpace_Create(This->standardSpace);
	ptr->currentPos = This->currentPos;
	ptr->distance = This->distance;
	ptr->standardSpace = This->standardSpace;
	GStandardSpace_GetSpaceSize(This->standardSpace, &width, &height);
	memcpy(ptr->roadmap, This->roadmap, width * height);
	return ptr;
}

#if 0
static Position GParallelSpace_Coords(const GParallelSpace * This, u32 offset)
{
    Position pos;

    pos.x = offset % This->mapSize.width;
    pos.y = offset / This->mapSize.width;

    return pos;
}
#endif

