// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>

#include "alocari.h"
#include "utilitare.h"

void interschimba(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int modulo(long x)
{
	x %= NR_MOD;
	if (x < 0)
		return (int)(x + NR_MOD);
	return (int)x;
}
