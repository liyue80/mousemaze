/*
 *
 */
#ifndef _PARALLEL_SPACE_H_
#define _PARALLEL_SPACE_H_
     
    #define TABLE_WIDTH  30
    #define TABLE_HEIGHT 30
          
    typedef struct
    {
        unsigned long _instanceId;
    } GParallelSpace;

    GParallelSpace * GParallelSpace_Create();

    GParallelSpare_InitializeTable(GParallelSpace * This,
    unsigned int tableWidth, unsigned int tableHeight,
    const char * tableInitStr);

    GParallelSpare_InitializeEntry(GParallelSpace * This,
    unsigned int x, unsigned int y);
     
#endif

