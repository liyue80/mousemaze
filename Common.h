/*
 *
 */
#ifndef _COMMON_H_
#define _COMMON_H_

/* GAME predefined */
#define WIDTH  30
#define HEIGHT 30

#ifdef _MSC_VER
	typedef int bool;
	#define false 0
	#define true 1
#elif defined(__GNUC__)
	#include <stdbool.h>
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef char * LPSTR;
typedef const char * LPCSTR;

void mem_cpy(void *d, const void *s, u32 n);

#endif

