// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>

#include "alocari.h"
#include "utils.h"

void interschimba(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int **citire_matrice(int n, int m)
{
	int **a = alocare_matrice(n, m);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			scanf("%d", &a[i][j]);
	}

	return a;
}

int modulo(long x)
{
	x %= NR_MOD;
	if (x < 0)
		return (int)(x + NR_MOD);
	return (int)x;
}
