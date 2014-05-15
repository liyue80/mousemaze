/*
 *
 */
#ifndef _STANDARD_SPACE_H_
#define _STANDARD_SPACE_H_

#include "Common.h"

typedef struct GStandardSpace_t
{
	Size mapSize;
    u32 * distanceMap;
	u32 extData[1];
} GStandardSpace;

GStandardSpace * GStandardSpace_Create(u32 width, u32 height);

void GStandardSpace_GetSpaceSize(const GStandardSpace * This, u32 * width, u32 * height);

/*
 * ���ܣ�  ��λ��(x,y)�����������ڵľ��루��������
 * ����ֵ��������λ���Ѿ��������˸�С�ľ��룬�����޸ģ�����false��
 */
bool GStandardSpace_SetDistance(GStandardSpace * This, u32 x, u32 y, u32 distance);

#endif
