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

GParallelSpace * GParallelSpace_Create(u32 width, u32 height)
{
    GParallelSpace * ptr = (GParallelSpace*)malloc(sizeof(GParallelSpace) + width * height);
	ptr->mapSize.width = width;
	ptr->mapSize.height = height;
	ptr->roadmap = (void*)((u8*)&ptr->roadmap + sizeof(ptr->roadmap));
	return ptr;
}

void GFastDeque_Destory(GParallelSpace * This)
{
	free(This);
}

void GParallelSpace_InitializeTable(GParallelSpace * This, LPCSTR mapInitStr)
{
	u32 allocSize = This->mapSize.width * This->mapSize.height;
	This->roadmap = (LPSTR)malloc(allocSize);
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
            if (This->currentPos.x + 1 >= This->mapSize.width)
                return NULL;
            test.x++;
            break;
        case DOWN:
            if (This->currentPos.y + 1 >= This->mapSize.height)
                return NULL;
            test.y++;
            break;
        default: assert(0);
    }

	offset = GParallelSpace_Offset(This, test.x, test.y);
	if (This->roadmap[offset] != '1')
        return NULL;

	dupSpace = GParallelSpace_Duplicate(This);
	dupSpace->roadmap[offset] = '2';
	dupSpace->currentPos = test;
    return dupSpace;
    
}

bool GParallelSpace_TestGoal(const GParallelSpace * This, u32 x, u32 y)
{
    return (This->currentPos.x == x) && (This->currentPos.y == y);
}

LPCSTR GParallelSpace_Output(const GParallelSpace * This)
{
#ifdef _DEBUG
	static char staticstring[4096] = {0};

	u32 i = 0;
	char * ptr = staticstring;

	for (i=0; i<This->mapSize.height; i++)
	{
		memcpy(ptr, &This->roadmap[GParallelSpace_Offset(This, 0, i)], This->mapSize.width);
		ptr += This->mapSize.width;
		*ptr++ = 0x0D;
		*ptr++ = 0x0A;
	}

	*ptr = '\0';

	return staticstring;
#else
	return This->roadmap;
#endif
}

static u32 GParallelSpace_Offset(const GParallelSpace * This, u32 x, u32 y)
{
    return (This->mapSize.width * y + x);
}

static GParallelSpace * GParallelSpace_Duplicate(const GParallelSpace * This)
{
	GParallelSpace * ptr = GParallelSpace_Create(This->mapSize.width, This->mapSize.height);
	ptr->currentPos = This->currentPos;
	ptr->mapSize = This->mapSize;
	memcpy(ptr->roadmap, This->roadmap, This->mapSize.width * This->mapSize.height);
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

