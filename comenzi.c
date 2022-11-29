// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocari.h"
#include "comenzi.h"
#include "operatii.h"
#include "utils.h"

static int validare_index(int i, int n)
{
	return i >= 0 && i < n;
}

static int citire_index(int n)
{
	int index;
	scanf("%d", &index);

	if (!validare_index(index, n)) {
		printf("No matrix with the given index\n");
		return -1;
	}
	return index;
}

static int citire_matrice_produs(int *col, int *lin, int n, int *a, int *b)
{
	scanf("%d%d", a, b);
	if (!(validare_index(*a, n) && validare_index(*b, n))) {
		printf("No matrix with the given index\n");
		return 0;
	}

	if (col[*a] != lin[*b]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}

	return 1;
}

void cmd_adaugare_matrice(int ****mat, int **lin, int **col, int *nr)
{
	int n, m;
	scanf("%d%d", &n, &m);

	int **a = citire_matrice(n, m);
	// TODO
	// if (!a) {}

	inserare_mat(mat, lin, col, (*nr)++, a, n, m);
}

void cmd_afisare_dimensiuni(int *lin, int *col, int nr)
{
	int index = citire_index(nr);
	if (index != -1)
		printf("%d %d\n", lin[index], col[index]);
}

void cmd_afisare_matrice(int ***mat, int *lin, int *col, int nr)
{
	int index = citire_index(nr);
	if (index != -1)
		printare_matrice(mat[index], lin[index], col[index]);
}

void cmd_redimensionare_matrice(int ***matrice, int *lin, int *col, int nr)
{
	int l, c;
	int index;
	index = citire_index(nr);

	scanf("%d", &l);
	int *linii = (int *)malloc(l * sizeof(int));
	// TODO:
	if (!linii)
		return;

	for (int i = 0; i < l; ++i)
		scanf("%d", &linii[i]);

	scanf("%d", &c);
	int *coloane = (int *)malloc(c * sizeof(int));
	// TODO:
	if (!coloane) {
		free(linii);
		return;
	}

	for (int i = 0; i < c; ++i)
		scanf("%d", &coloane[i]);

	if (index == -1) {
		// TODO:
		free(linii);
		free(coloane);
		return;
	}
	int **aux = partitionare_matrice(matrice[index], linii, coloane, l, c);
	// TODO
	// if (!aux) {}
	eliberare_matrice(matrice[index], lin[index]);
	matrice[index] = aux;
	lin[index] = l;
	col[index] = c;
	free(linii);
	free(coloane);
}

void cmd_inmultire_matrice(int ****mat, int **lin, int **col, int *nr)
{
	int x, y;
	if (!citire_matrice_produs(*col, *lin, *nr, &x, &y))
		return;

	int **c =
		prod_matrice((*mat)[x], (*mat)[y], (*lin)[x], (*col)[x], (*col)[y]);
	// TODO:
	// if (!c) {}
	inserare_mat(mat, lin, col, (*nr)++, c, (*lin)[x], (*col)[y]);
}

void cmd_sortare_matrice(int ***mat, int *lin, int *col, int nr)
{
	int *sume = (int *)calloc(nr, sizeof(int));
	// TODO:
	if (!sume)
		return;

	for (int i = 0; i < nr; ++i)
		sume[i] = insumare_elemente(mat[i], lin[i], col[i]);

	for (int i = 0; i < nr - 1; ++i) {
		for (int j = i + 1; j < nr; ++j) {
			if (sume[i] > sume[j]) {
				interschimba(&lin[i], &lin[j]);
				interschimba(&col[i], &col[j]);
				interschimba(&sume[i], &sume[j]);
				int **aux = mat[i];
				mat[i] = mat[j];
				mat[j] = aux;
			}
		}
	}

	free(sume);
}

void cmd_transpunere_matrice(int ***mat, int *lin, int *col, int nr)
{
	int index = citire_index(nr);
	if (index == -1)
		return;

	int n = lin[index];
	int m = col[index];

	int **transpusa = alocare_matrice(m, n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			transpusa[j][i] = mat[index][i][j];
	}
	eliberare_matrice(mat[index], n);
	// TODO:
	// if (!mat) {}
	mat[index] = transpusa;
	interschimba(&lin[index], &col[index]);
}

void cmd_exp_matrice(int ***mat, int *lin, int *col, int nr)
{
	int index, exp;
	index = citire_index(nr);
	scanf("%d", &exp);

	if (index == -1)
		return;

	if (exp < 0) {
		printf("Power should be positive\n");
		return;
	}

	if (lin[index] != col[index]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	int **rez = exp_matrice(mat[index], lin[index], exp);
	mat[index] = rez;
}

void cmd_stergere_matrice(int ****mat, int **lin, int **col, int *nr)
{
	int index = citire_index(*nr);
	if (index == -1)
		return;

	eliberare_matrice((*mat)[index], (*lin)[index]);

	for (int i = index; i < *nr - 1; ++i) {
		(*mat)[i] = (*mat)[i + 1];
		(*lin)[i] = (*lin)[i + 1];
		(*col)[i] = (*col)[i + 1];
	}
	modif_nr_matrice(mat, lin, col, --(*nr));
}

void cmd_eliberare_resurse(int ***mat, int *lin, int *col, int nr)
{
	for (int i = 0; i < nr; ++i)
		eliberare_matrice(mat[i], lin[i]);

	free(mat);
	free(lin);
	free(col);
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

int **alg_strassen(int **a, int **b, int n)
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
		alg_strassen(sume_part_a[0], sume_part_b[0],
					 n), // M0 = (A1 + A4)(B1 + B4) = S_A0 * S_B0
		alg_strassen(sume_part_a[1], part_b[0],
					 n), // M1 = (A3 + A4)B1 = S_A1 * B1
		alg_strassen(part_a[0], sume_part_b[1],
					 n), // M2 = A1(B2 - B4) = A1 * S_B1
		alg_strassen(part_a[3], sume_part_b[2],
					 n), // M3 = A4(B3 - B1) = A4 * S_B2
		alg_strassen(sume_part_a[2], part_b[3],
					 n), // M4 = (A1+A2)B4 = S_A2 * B4
		alg_strassen(sume_part_a[3], sume_part_b[3],
					 n), // M5 = (A3 - A1)(B1 + B2) = S_A3 * S_B3
		alg_strassen(sume_part_a[4], sume_part_b[4],
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

void cmd_produs_strassen(int ****mat, int **lin, int **col, int *nr)
{
	int x, y;

	if (!citire_matrice_produs(*col, *lin, *nr, &x, &y))
		return;
	int **rez = alg_strassen((*mat)[x], (*mat)[y], (*lin)[x]);
	// TODO
	if (!rez)
		return;
	inserare_mat(mat, lin, col, (*nr)++, rez, (*lin)[x], (*lin)[x]);
}
