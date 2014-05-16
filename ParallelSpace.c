/*
 *
 */
#include <string.h>
#include <assert.h>
#include "ParallelSpace.h"

void GParallelSpace_Initialize(GParallelSpace * This, GStandardSpace * pStandardSpace)
{
	memset(This, 0, sizeof(GParallelSpace));
    This->standardSpace = pStandardSpace;
}

void GParallelSpace_InitializeTable(GParallelSpace * This, LPCSTR mapInitStr)
{
	memcpy(This->roadmap, mapInitStr, WIDTH * HEIGHT);
}

void GParallelSpace_InitializeEntry(GParallelSpace * This, u32 x, u32 y)
{
    This->x = x;
    This->y = y;
	This->roadmap[y][x] = '2';
}

bool GParallelSpace_Move(const GParallelSpace * This, Direction dir, GParallelSpace * pNextSpace)
{
	u32 xx, yy;

	xx = This->x;
	yy = This->y;

	switch (dir)
    {
        case LEFT:
			if (xx == 0) return false;
			xx--;
            break;
        case UP:
			if (yy == 0) return false;
			yy--;
			break;
        case RIGHT:
            if (xx + 1 >= WIDTH) return false;
            xx++;
            break;
        case DOWN:
            if (yy + 1 >= HEIGHT) return false;
            yy++;
            break;
        default:
			assert(0);
    }

	if (This->roadmap[yy][xx] != '1')
        return false;

	if (!GStandardSpace_SetDistance(This->standardSpace, xx, yy, This->distance + 1))
		return false;

	memcpy(pNextSpace, This, sizeof(GParallelSpace));
	pNextSpace->roadmap[yy][xx] = '2';
	pNextSpace->x = xx;
	pNextSpace->y = yy;
	pNextSpace->distance++;
    return true;
    
}

bool GParallelSpace_TestGoal(const GParallelSpace * This, u32 x, u32 y)
{
    return (This->x == x) && (This->y == y);
}

LPCSTR GParallelSpace_Output(const GParallelSpace * This)
{
	static char staticstring[4096] = {0};
#ifdef _DEBUG
	u32 i = 0;
	char * ptr = staticstring;
#endif

#ifdef _DEBUG
	for (i = 0; i < HEIGHT; i++)
	{
		memcpy(ptr, &This->roadmap[i][0], WIDTH);
		ptr += WIDTH;
		*ptr++ = 0x0D;
		*ptr++ = 0x0A;
	}

	*ptr++ = 0x0D;
	*ptr++ = 0x0A;
	*ptr = '\0';
#else
	memcpy(staticstring, This->roadmap, WIDTH * HEIGHT);
	staticstring[WIDTH * HEIGHT] = '\0';
#endif

	return staticstring;
}
