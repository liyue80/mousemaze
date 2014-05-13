/*
 *
 */
#ifndef _FIXED_MEM_POOL_H_
#define _FIXED_MEM_POOL_H_
     
    typedef struct
    {
        unsigned long _instanceId;
    } GFixedMemPool;

    GFixedMemPool * GFixedMemPool_Create(unsigned int blockSize, unsigned int blockMaxCount);
    void * GFixedMemPool_Allocate(GFixedMemPool *This);
    void   GFixedMemPool_Free(GFixedMemPool *This, void * ptr);
     
#endif

