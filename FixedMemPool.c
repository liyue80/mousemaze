/*
 *
 */

#include "FixedMemPool.h"
#include <stdlib.h>

GFixedMemPool * GFixedMemPool_Create(u32 blockSize, u32 blockMaxCount)
{
    GFixedMemPool * This = (GFixedMemPool *)malloc(sizeof(GFixedMemPool));
    This->blockSize = blockSize;
    This->blockMaxCount = blockMaxCount;
    return This;
}

void * GFixedMemPool_Allocate(GFixedMemPool *This)
{
    return malloc(This->blockSize);
}

void GFixedMemPool_Free(GFixedMemPool *This, void * ptr)
{
    free(ptr);
}

