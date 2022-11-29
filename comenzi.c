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

void cmd_produs_strassen(int ****mat, int **lin, int **col, int *nr)
{
	int x, y;

	if (!citire_matrice_produs(*col, *lin, *nr, &x, &y))
		return;
	int **rez = prod_strassen((*mat)[x], (*mat)[y], (*lin)[x]);
	// TODO
	if (!rez)
		return;
	inserare_mat(mat, lin, col, (*nr)++, rez, (*lin)[x], (*lin)[x]);
}
