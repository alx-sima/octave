// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocari.h"
#include "comenzi.h"
#include "operatii.h"
#include "utils.h"

static int citire_index(int n)
{
	int index;
	scanf("%d", &index);

	if (index >= n) {
		printf("No matrix with the given index\n");
		return -1;
	}
	return index;
}

void cmd_adaugare_matrice(int ****mat, struct dimensiune **dim, int *nr)
{
	int n, m;
	scanf("%d%d", &n, &m);

	int **a = citire_matrice(n, m);
	if (a == NULL) {
		// TODO
	}
	inserare_mat(mat, dim, *nr, a, n, m);
	++(*nr);
}

void cmd_afisare_dimensiuni(struct dimensiune *dim, int nr)
{
	int index = citire_index(nr);
	if (index != -1) {
		printf("%d %d\n", dim[index].lin, dim[index].col);
	}
}

void cmd_afisare_matrice(int ***mat, struct dimensiune *dim, int nr)
{
	int index = citire_index(nr);
	if (index != -1) {
		printare_matrice(mat[index], dim[index].lin, dim[index].col);
	}
}

void cmd_redimensionare_matrice(int ***matrice, struct dimensiune *dim, int nr)
{
	int index = citire_index(nr);
	if (index == -1) {
		return;
	}

	int l, c;
	scanf("%d", &l);
	int *linii = (int *)malloc(l * sizeof(int));
	if (linii == NULL) {
		// TODO:
		return;
	}
	for (int i = 0; i < l; ++i) {
		scanf("%d", &linii[i]);
	}
	scanf("%d", &c);
	int *coloane = (int *)malloc(c * sizeof(int));
	if (coloane == NULL) {
		// TODO:
		free(linii);
		return;
	}

	for (int i = 0; i < c; ++i) {
		scanf("%d", &coloane[i]);
	}

	int **aux = alocare_matrice(l, c);
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < c; ++j) {
			int srci = linii[i];
			int srcj = coloane[j];

			aux[i][j] = matrice[index][srci][srcj];
		}
	}
	eliberare_matrice(matrice[index], dim[index].lin);
	matrice[index] = aux;
	dim[index].lin = l;
	dim[index].col = c;
	free(linii);
	free(coloane);
}

void cmd_inmultire_matrice(int ****mat, struct dimensiune **dim, int *nr)
{
	int x, y;
	scanf("%d%d", &x, &y);
	if (x >= *nr || y >= *nr) {
		printf("No matrix with the given index\n");
		return;
	}

	if ((*dim)[x].col != (*dim)[y].lin) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	int **c = prod_matrice((*mat)[x], (*mat)[y], (*dim)[x].lin, (*dim)[x].col,
						   (*dim)[y].col);
	if (c == NULL) {} // TODO:
	inserare_mat(mat, dim, *nr, c, (*dim)[x].lin, (*dim)[y].col);
	++(*nr);
}

void cmd_sortare_matrice(int ***mat, struct dimensiune *dim, int nr)
{
	int *sume = (int *)calloc(nr, sizeof(int));
	if (sume == NULL) {
		// TODO:
		return;
	}

	for (int i = 0; i < nr; ++i) {
		sume[i] = insumare_elemente(mat[i], dim[i].lin, dim[i].col);
	}

	int schimbare;
	do {
		schimbare = 0;
		for (int i = 0; i < nr - 1; ++i) {
			if (sume[i] > sume[i + 1]) {
				interschimba(&dim[i].lin, &dim[i + 1].lin);
				interschimba(&dim[i].col, &dim[i + 1].col);
				interschimba(&sume[i], &sume[i + 1]);
				int **aux = mat[i];
				mat[i] = mat[i + 1];
				mat[i + 1] = aux;
				schimbare = 1;
			}
		}
	} while (schimbare);

	free(sume);
}

void cmd_transpunere_matrice(int ***mat, struct dimensiune *dim, int nr)
{
	int index = citire_index(nr);
	if (index == -1) {
		return;
	}

	int n = dim[index].lin;
	int m = dim[index].col;

	int **tA = alocare_matrice(m, n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			tA[j][i] = mat[index][i][j];
		}
	}
	eliberare_matrice(mat[index], n);
	mat[index] = tA;
	if (mat == NULL) {} // TODO:
	interschimba(&dim[index].lin, &dim[index].col);
}

void cmd_exp_matrice(int ***mat, struct dimensiune *dim, int nr)
{
	int index = citire_index(nr);
	if (index == -1) {
		return;
	}

	int exp;
	scanf("%d", &exp);
	if (exp < 0) {
		printf("Power should pe positive\n");
		return;
	}

	int **rez = exp_matrice(mat[index], dim[index].lin, exp);
	mat[index] = rez;
}

void cmd_stergere_matrice(int ****mat, struct dimensiune **dim, int *nr)
{
	int index = citire_index(*nr);
	if (index == -1) {
		return;
	}

	for (int i = index; i < *nr - 1; ++i) {
		(*mat)[i] = (*mat)[i + 1];
	}

	modif_nr_matrice(mat, dim, *nr, *nr - 1);
	--(*nr);
}

void cmd_eliberare_resurse(int ***mat, struct dimensiune *dim, int nr)
{
	for (int i = 0; i < nr; ++i) {
		eliberare_matrice(mat[i], dim[i].lin);
	}
	free(mat);
	free(dim);
}
