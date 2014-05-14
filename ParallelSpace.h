/*
 *
 */
#ifndef _PARALLEL_SPACE_H_
#define _PARALLEL_SPACE_H_

typedef struct
{
    // Following members are private.
    unsigned int _width;
    unsigned int _height;
} GParallelSpace;

typedef enum Direction
{
    UP, RIGHT, DOWN, LEFT
} Direction;

GParallelSpace * GParallelSpace_Create();

void GParallelSpace_InitializeTable(GParallelSpace * This, unsigned int tableWidth, unsigned int tableHeight, const char * tableInitStr);

void GParallelSpace_InitializeEntry(GParallelSpace * This, unsigned int x, unsigned int y);

GParallelSpace * GParallelSpace_Move(const GParallelSpace * This, Direction dir);

#endif

