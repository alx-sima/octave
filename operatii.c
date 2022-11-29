// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocari.h"
#include "operatii.h"
#include "utils.h"

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

int **identitate(int n)
{
	int **a = alocare_matrice(n, n);
	if (!a)
		return NULL;

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
	long s = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			s = modulo(s + a[i][j]);
	}
	return (int)s;
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
				x = modulo(x + modulo((long)a[i][k] * b[k][j]));
			c[i][j] = modulo(x);
		}
	}

	return c;
}

int **exp_matrice(int **x, int n, int k)
{
	if (k == 0)
		return x;

	int **y, **aux;
	y = identitate(n);
	while (k > 1) {
		if (k % 2 == 0) {
			aux = prod_matrice(x, x, n, n, n);
			eliberare_matrice(x, n);
			x = aux;
			k /= 2;
		} else {
			aux = prod_matrice(x, y, n, n, n);
			eliberare_matrice(y, n);
			y = aux;

			aux = prod_matrice(x, x, n, n, n);
			eliberare_matrice(x, n);
			x = aux;
			k = (k - 1) / 2;
		}
	}

	aux = prod_matrice(x, y, n, n, n);
	eliberare_matrice(x, n);
	eliberare_matrice(y, n);

	return aux;
}

int **sum(int **a, int **b, int n)
{
	int **c = alocare_matrice(n, n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			c[i][j] = modulo((long)a[i][j] + b[i][j]);
	}
	return c;
}

int **diff(int **a, int **b, int n)
{
	int **c = alocare_matrice(n, n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			c[i][j] = modulo(a[i][j] - b[i][j]);
	}
	return c;
}

int **reconstituire_matrice(int **c[4], int n)
{
	int **a = alocare_matrice(n * 2, n * 2);
	if (!a) {
		eliberare_vector_matrice(c, 4, n);
		return NULL;
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k)
				a[j + n * (i >> 1 & 1)][k + n * (i & 1)] = c[i][j][k];
		}
	}

	eliberare_vector_matrice(c, 4, n);
	return a;
}

int **prod_strassen(int **a, int **b, int n)
{
	// TODO
	if (n == 1) {
		int **rez = alocare_matrice(1, 1);
		rez[0][0] = a[0][0] * b[0][0];
		return rez;
	}
	int *temp = (int *)malloc(n * sizeof(int));
	if (!temp)
		return NULL;

	for (int i = 0; i < n; ++i)
		temp[i] = i;
	n /= 2;
	int **part_a[4];
	int **part_b[4];

	for (int i = 0; i < 4; ++i) {
		// !!! Doamne-ajuta !!!
		// ? Codul nu are nevoie de documentatie, codul este documentatia
		// ? Daca merge, merge
		part_a[i] = partitionare_matrice(a, temp + (i >> 1 & 1) * n,
										 temp + (i & 1) * n, n, n);
		part_b[i] = partitionare_matrice(b, temp + (i >> 1 & 1) * n,
										 temp + (i & 1) * n, n, n);
	}
	free(temp);

	int **sume_part_a[5] = {
		sum(part_a[0], part_a[3], n), sum(part_a[2], part_a[3], n),
		sum(part_a[0], part_a[1], n), diff(part_a[2], part_a[0], n),
		diff(part_a[1], part_a[3], n)};

	int **sume_part_b[5] = {
		sum(part_b[0], part_b[3], n), diff(part_b[1], part_b[3], n),
		diff(part_b[2], part_b[0], n), sum(part_b[0], part_b[1], n),
		sum(part_b[2], part_b[3], n)};

	// Se calculeaza cele 7 matrice ajutatoare,
	// conform formulelor algoritmului
	int **m[7] = {
		prod_strassen(sume_part_a[0], sume_part_b[0],
					  n), // M0 = (A1 + A4)(B1 + B4) = S_A0 * S_B0
		prod_strassen(sume_part_a[1], part_b[0],
					  n), // M1 = (A3 + A4)B1 = S_A1 * B1
		prod_strassen(part_a[0], sume_part_b[1],
					  n), // M2 = A1(B2 - B4) = A1 * S_B1
		prod_strassen(part_a[3], sume_part_b[2],
					  n), // M3 = A4(B3 - B1) = A4 * S_B2
		prod_strassen(sume_part_a[2], part_b[3],
					  n), // M4 = (A1+A2)B4 = S_A2 * B4
		prod_strassen(sume_part_a[3], sume_part_b[3],
					  n), // M5 = (A3 - A1)(B1 + B2) = S_A3 * S_B3
		prod_strassen(sume_part_a[4], sume_part_b[4],
					  n), // M6 = (A2 - A4)(B3 + B4) = S_A4 * S_B4
	};
	eliberare_vector_matrice(part_a, 4, n);
	eliberare_vector_matrice(part_b, 4, n);
	eliberare_vector_matrice(sume_part_a, 5, n);
	eliberare_vector_matrice(sume_part_b, 5, n);

	int **c_part[4] = {sum(m[0], m[3], n), diff(m[6], m[4], n),
					   diff(m[0], m[1], n), sum(m[2], m[5], n)};

	int **c[4] = {
		sum(c_part[0], c_part[1], n),
		sum(m[2], m[4], n),
		sum(m[1], m[3], n),
		sum(c_part[2], c_part[3], n),
	};

	eliberare_vector_matrice(m, 7, n);
	eliberare_vector_matrice(c_part, 4, n);

	return reconstituire_matrice(c, n);
}
