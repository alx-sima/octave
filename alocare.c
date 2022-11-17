// Copyright Sima Alexandru 312CA 2022-2023

#include <stdlib.h>

#include "alocare.h"
#include "operatii.h"

int **alocare_matrice(int n, int m)
{
	int **a = (int **)malloc(n * sizeof(int *));
	if (a == NULL) {
		return NULL;
	}

	for (int i = 0; i < n; ++i) {
		a[i] = (int *)malloc(m * sizeof(int));

		if (a[i] == NULL) {
			// Dealocam toate randurile
			// alocate pana acum.
			for (int j = 0; j < i; ++j) {
				free(a[j]);
			}
			free(a);
			return NULL;
		}
	}

	return a;
}

void inserare_mat(int ****mat, struct dimensiune **dim, int *nr, int **a, int n,
				  int m)
{
	struct dimensiune *dimensiuni_vechi = *dim;
	*dim = (struct dimensiune *)realloc(*dim,
										(*nr + 1) * sizeof(struct dimensiune));
	if (*dim == NULL) {
		free(dimensiuni_vechi);
		return;
	}

	int ***matrice_vechi = *mat;
	*mat = (int ***)realloc(*mat, (*nr + 1) * sizeof(int **));
	if (*mat == NULL) {
		// Sterge toate matricele
		for (int i = 0; i < *nr; ++i) {
			eliberare_matrice(matrice_vechi[i], (*dim)[i].lin);
		}
		free(matrice_vechi);
		return;
	}
	(*dim)[*nr].lin = n;
	(*dim)[*nr].col = m;
	(*mat)[(*nr)++] = a;
}

void eliberare_matrice(int **mat, int n)
{
	for (int i = 0; i < n; ++i) {
		free(mat[i]);
	}
	free(mat);
}