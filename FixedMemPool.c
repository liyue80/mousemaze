/*
 *
 */

#include "FixedMemPool.h"
#include <stdlib.h>

typedef struct
{
    GFixedMemPool _publicMembers;

    // Private members below
    unsigned int _blockSize;
    unsigned int _blockMaxCount;
} GFixedMemPoolIntl;

GFixedMemPool * GFixedMemPool_Create(unsigned int blockSize, unsigned int blockMaxCount)
{
    GFixedMemPoolIntl * This = (GFixedMemPoolIntl *)malloc(sizeof(GFixedMemPool));
    This->_publicMembers._instanceId = rand();
    This->_blockSize = blockSize;
    This->_blockMaxCount = blockMaxCount;
    return (GFixedMemPool *)This;
}

void * GFixedMemPool_Allocate(GFixedMemPool *This)
{
    GFixedMemPoolIntl * thisIntl = (GFixedMemPoolIntl *)This;
    void * ptr = malloc(thisIntl->_blockSize);
}

void   GFixedMemPool_Free(GFixedMemPool *This, void * ptr)
{
    free(ptr);
}

