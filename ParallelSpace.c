/*
 *
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ParallelSpace.h"

/* Convert (x,y) to offset in _roadmap */
static u32 GParallelSpace_Offset(const GParallelSpace * This, const Position * pos);
static Position GParallelSpace_Coords(const GParallelSpace * This, u32 offset);

GParallelSpace * GParallelSpace_Create()
{
    return (GParallelSpace*)malloc(sizeof(GParallelSpace));
}

void GParallelSpace_InitializeTable(GParallelSpace * This, u32 width, u32 height, LPCSTR mapInitStr)
{
    This->mapSize.width = width;
    This->mapSize.height = height;
    This->roadmap = (LPSTR)malloc(width * height);
    memcpy(This->roadmap, mapInitStr, width * height);
}

void GParallelSpace_InitializeEntry(GParallelSpace * This, u32 x, u32 y)
{
    This->currentPos.x = x;
    This->currentPos.y = y;
    This->roadmap[GParallelSpace_Offset(This, &This->currentPos)] = '2';
}

GParallelSpace * GParallelSpace_Move(const GParallelSpace * This, Direction dir)
{
	GParallelSpace * dupSpace;
    Position test = This->currentPos;

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

    if (This->roadmap[GParallelSpace_Offset(This, &test)] != '1')
        return NULL;

    dupSpace = (GParallelSpace *)malloc(sizeof(GParallelSpace));
    memcpy(dupSpace, This, sizeof(GParallelSpace));
    dupSpace->roadmap[GParallelSpace_Offset(This, &test)] = '2';
    return dupSpace;
    
}

bool GParallelSpace_TestGoal(const GParallelSpace * This, u32 x, u32 y)
{
    return (This->currentPos.x == x) && (This->currentPos.y == y);
}

static u32 GParallelSpace_Offset(const GParallelSpace * This, const Position * pos)
{
    return (This->mapSize.width * pos->y + pos->x);
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

