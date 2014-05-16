/*
 *
 */

#include "FixedMemPool.h"

GFixedMemPool * GFixedMemPool_Create(u32 blockSize, u32 blockMaxCount)
{
    GFixedMemPool * This = (GFixedMemPool *)mem_alloc(sizeof(GFixedMemPool));
    This->blockSize = blockSize;
    This->blockMaxCount = blockMaxCount;
    return This;
}

void * GFixedMemPool_Allocate(GFixedMemPool *This)
{
    return mem_alloc(This->blockSize);
}

void GFixedMemPool_Free(GFixedMemPool *This, void * ptr)
{
    mem_free(ptr);
}

