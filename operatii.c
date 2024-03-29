// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocari.h"
#include "operatii.h"

#define NR_MOD 10007

// Aloca si intoarce matricea identitate `In`.
static int **identitate(int n);

static int modulo(long x);

int **citire_matrice(int n, int m)
{
	int **a = alocare_matrice(n, m);
	if (!a)
		return NULL;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			scanf("%d", &a[i][j]);
	}

	return a;
}

void printare_matrice(int **mat, int n, int m)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

int **partitionare_matrice(int **mat, int *lin, int *col, int nrlin, int nrcol)
{
	int **rez = alocare_matrice(nrlin, nrcol);
	if (!rez)
		return NULL;

	for (int i = 0; i < nrlin; ++i) {
		for (int j = 0; j < nrcol; ++j)
			rez[i][j] = mat[lin[i]][col[j]];
	}

	return rez;
}

int insumare_elemente(int **a, int n, int m)
{
	long s = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			s = modulo(s + a[i][j]);
	}
	return (int)s;
}

int **adunare_matrice(int **a, int **b, int n, int semn)
{
	int **c = alocare_matrice(n, n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			c[i][j] = modulo((long)a[i][j] + semn * b[i][j]);
	}
	return c;
}

int **prod_matrice(int **a, int **b, int n, int m, int o)
{
	int **c = alocare_matrice(n, o);
	if (!c)
		return NULL;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < o; ++j) {
			long x = 0;
			for (int k = 0; k < m; ++k)
				x = modulo(x + a[i][k] * b[k][j]);
			c[i][j] = modulo(x);
		}
	}

	return c;
}

int **putere_matrice(int **baza, int n, int k)
{
	int **x, **y, **aux;

	if (k == 0)
		return baza;

	// Se copiaza matricea originala, astfel incat, in
	// caz de eroare, aceasta sa ramana nemodificata, pentru
	// a fi eliberata corespunzator odata cu celelalte.
	x = copiere_matrice(baza, n, n);
	if (!x)
		return NULL;
	y = identitate(n);
	if (!y) {
		eliberare_matrice(x, n);
		return NULL;
	}

	while (k > 1) {
		if (k % 2 == 1) {
			aux = prod_matrice(x, y, n, n, n);
			eliberare_matrice(y, n);
			y = aux;
			if (!aux) {
				eliberare_matrice(x, n);
				return NULL;
			}
			--k;
		}
		aux = prod_matrice(x, x, n, n, n);
		eliberare_matrice(x, n);
		x = aux;
		if (!aux) {
			eliberare_matrice(y, n);
			return NULL;
		}

		k /= 2;
	}

	aux = prod_matrice(x, y, n, n, n);
	eliberare_matrice(x, n);
	eliberare_matrice(y, n);
	if (aux)
		eliberare_matrice(baza, n);
	return aux;
}

static int **identitate(int n)
{
	int **a = alocare_matrice(n, n);
	if (!a)
		return NULL;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// A[i,j] = 1; i = j
			// A[i,j] = 0; i != j
			a[i][j] = (i == j);
		}
	}

	return a;
}

static int modulo(long x)
{
	x %= NR_MOD;
	if (x < 0)
		return (int)(x + NR_MOD);
	return (int)x;
}
