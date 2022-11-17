#include <stdio.h>
#include <stdlib.h>

#include "alocare.h"
#include "operatii.h"
#include "utils.h"

void op_adaugare_matrice(int ****mat, struct dimensiune **dim, int *nr)
{
	int n, m;
	scanf("%d%d", &n, &m);

	int **a = citire_matrice(n, m);
	if (a == NULL) {
		// TODO
	}
	inserare_mat(mat, dim, nr, a, n, m);
}

void op_afisare_dimensiuni(struct dimensiune *dim, int nr)
{
	int index;
	scanf("%d", &index);
	if (index >= nr) {
		printf("No matrix with the given index\n");
		return;
	}

	printf("%d %d\n", dim[index].lin, dim[index].col);
}

void op_afisare_matrice(int ***mat, struct dimensiune *dim, int nr)
{
	int index;
	scanf("%d", &index);

	if (index >= nr) {
		printf("No matrix with the given index\n");
		return;
	}

	for (int i = 0; i < dim[index].lin; ++i) {
		for (int j = 0; j < dim[index].col; ++j) {
			printf("%d ", mat[index][i][j]);
		}
		printf("\n");
	}
}

void op_redimensionare_matrice(int ***matrice, struct dimensiune *dim, int nr)
{
	int index, l, c;
	scanf("%d", &index);
	if (index >= nr) {
		printf("No matrix with the given index\n");
	}

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

	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < c; ++j) {

			int srci = linii[i];
			int srcj = coloane[j];

			// TODO: while?
			if (srci < i || (srci == srcj && srcj < j)) {
				srci = linii[srci];
				srcj = coloane[srcj];
			}
			interschimba(&matrice[index][i][j], &matrice[index][srci][srcj]);
		}
	}
	micsorare_matrice(&matrice[index], dim[index].lin, l, c);
	dim[index].lin = l;
	dim[index].col = c;
	free(linii);
	free(coloane);
}

void op_inmultire_matrice(int ****mat, struct dimensiune **dim, int *nr)
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
	inserare_mat(mat, dim, nr, c, (*dim)[x].lin, (*dim)[y].col);
}

void op_sortare_matrice(int ***mat, struct dimensiune *dim, int nr) {}

void op_eliberare_resurse(int ***mat, struct dimensiune *dim, int nr)
{
	for (int i = 0; i < nr; ++i) {
		eliberare_matrice(mat[i], dim[i].lin);
	}
	free(mat);
	free(dim);
}