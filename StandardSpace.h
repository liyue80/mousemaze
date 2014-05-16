/*
 *
 */
#ifndef _STANDARD_SPACE_H_
#define _STANDARD_SPACE_H_

#include "Common.h"

typedef struct GStandardSpace_t
{
    u32 distanceMap[HEIGHT][WIDTH];
} GStandardSpace;

void GStandardSpace_Initialize(GStandardSpace * This);

/*
 * ���ܣ�  ��λ��(x,y)�����������ڵľ��루��������
 * ����ֵ��������λ���Ѿ��������˸�С�ľ��룬�����޸ģ�����false��
 */
bool GStandardSpace_SetDistance(GStandardSpace * This, u32 x, u32 y, u32 distance);

#endif
