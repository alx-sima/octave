// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocare.h"
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
		for (int j = 0; j < m; ++j) {
			scanf("%d", &a[i][j]);
		}
	}

	return a;
}

void micsorare_matrice(int ***mat, int n_vechi, int n, int m)
{
	// Scurteaza liniile care raman pana la m coloane.
	for (int i = 0; i < n; ++i) {
		(*mat)[i] = (int *)realloc((*mat)[i], m * sizeof(int));
		// TODO:
		if (*mat == NULL) {
			printf("????");
			return;
		}
	}

	// Elibereaza liniile in plus.
	for (int i = n; i < n_vechi; ++i) {
		free((*mat)[i]);
	}
	*mat = (int **)realloc(*mat, n * sizeof(int *));
	// TODO:
	if (*mat == NULL) {
		return;
	}
}

// Inmulteste matricea a (nxm) cu b (mxo) in
// matricea c (nxo), pe care o aloca.
int **prod_matrice(int **a, int **b, int n, int m, int o)
{
	int **c = alocare_matrice(n, o);
	if (c == NULL) {
		// TODO:
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < o; ++j) {
			c[i][j] = 0;
			for (int k = 0; k < m; ++k) {
				c[i][j] += modulo((long)a[i][k] * b[k][j]);
			}
		}
	}

	return c;
}

int modulo(long x)
{
	x %= NR_MOD;
	if (x < 0) {
		return x + NR_MOD;
	}
	return x;
}