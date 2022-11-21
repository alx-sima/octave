// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocari.h"
#include "operatii.h"
#include "utils.h"

void printare_matrice(int **mat, int n, int m)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

int **identitate(int n)
{
	int **a = alocare_matrice(n, n);
	if (a == NULL) {
		return NULL;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// A(i,j) = 1 <=> i = j
			a[i][j] = (i == j);
		}
	}

	return a;
}

int insumare_elemente(int **a, int n, int m)
{
	int s = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			s = modulo(s + a[i][j]);
		}
	}
	return s;
}

// Inmulteste matricea a (nxm) cu b (mxo) in
// matricea c (nxo), pe care o aloca.
int **prod_matrice(int **a, int **b, int n, int m, int o)
{
	int **c = alocare_matrice(n, o);
	if (c == NULL) {
		return NULL;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < o; ++j) {
			long x = 0;
			for (int k = 0; k < m; ++k) {
				x = modulo(x + modulo((long)a[i][k] * b[k][j]));
			}
			c[i][j] = modulo(x);
		}
	}

	return c;
}

int **exp_matrice(int **x, int n, int k)
{
	if (k == 0) {
		return x;
	}

	int **y, **aux;
	y = identitate(n);
	while (k > 1) {
		if (k % 2 == 0) {
			aux = prod_matrice(x, x, n, n, n);
			eliberare_matrice(x, n);
			x = aux;
			// mutare_matrice(x, aux, n, n);
			k /= 2;
		} else {
			aux = prod_matrice(x, y, n, n, n);
			eliberare_matrice(y, n);
			y = aux;
			// mutare_matrice(y, aux, n, n);

			aux = prod_matrice(x, x, n, n, n);
			eliberare_matrice(x, n);
			x = aux;
			// mutare_matrice(x, aux, n, n);
			k = (k - 1) / 2;
		}
	}

	aux = prod_matrice(x, y, n, n, n);
	eliberare_matrice(x, n);
	eliberare_matrice(y, n);

	return aux;
}
