/*
 *
 */
#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef _MSC_VER
typedef int bool;
#elif defined(__GNUC__)
#include <stdbool.h>
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef char * LPSTR;
typedef const char * LPCSTR;

typedef struct Position_t
{
    u32 x;
    u32 y;
} Position;

typedef struct Size_t
{
    u32 width;
    u32 height;
} Size;


#endif

