/*
 *
 */
#ifndef _FIXED_MEM_POOL_H_
#define _FIXED_MEM_POOL_H_

#include "common.h"

typedef struct
{
    // Private members below
    u32 blockSize;
    u32 blockMaxCount;
} GFixedMemPool;

GFixedMemPool * GFixedMemPool_Create(u32 blockSize, u32 blockMaxCount);
void * GFixedMemPool_Allocate(GFixedMemPool *This);
void GFixedMemPool_Free(GFixedMemPool *This, void * ptr);
     
#endif

