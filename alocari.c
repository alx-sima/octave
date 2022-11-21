// Copyright Sima Alexandru 312CA 2022-2023

#include <stdlib.h>

#include "alocari.h"
#include "comenzi.h"
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

void eliberare_matrice(int **mat, int n)
{
	for (int i = 0; i < n; ++i) {
		free(mat[i]);
	}
	free(mat);
}

void redimensionare_matrice(int ***mat, int n_vechi, int n, int m)
{
	// Se elibereaza liniile in plus (daca se micsoreaza numarul de linii).
	for (int i = n; i < n_vechi; ++i) {
		free((*mat)[i]);
	}

	*mat = (int **)realloc(*mat, n * sizeof(int *));
	if (*mat == NULL) {
		eliberare_matrice(*mat, n);
		return;
	}

	// Se aloca liniile noi (daca exista).
	for (int i = n_vechi; i < n; ++i) {
		//(*mat)[i] = (int *)malloc(m * sizeof(int));
		// if ((*mat)[i] == NULL) {
		//	eliberare_matrice(*mat, i);
		//*mat = NULL;
		// return;
		//}
		(*mat)[i] = NULL; // pt ca realocul sa functioneze ca un malloc
	}

	// Se scurteaza/prelungesc/aloca liniile
	// astfel incat sa aiba `m` coloane.
	for (int i = 0; i < n; ++i) {
		(*mat)[i] = (int *)realloc((*mat)[i], m * sizeof(int));

		if ((*mat)[i] == NULL) {
			eliberare_matrice(*mat, i);
			*mat = NULL;
			return;
		}
	}
}

void modif_nr_matrice(int ****mat, struct dimensiune **dim, int nr_vechi,
					  int nr)
{
	// Se elibereaza matricele in plus (daca exista).
	for (int i = nr; i < nr_vechi; ++i) {
		printare_matrice((*mat)[i], (*dim)[i].lin, (*dim)[i].col);
		eliberare_matrice((*mat)[i], (*dim)[i].lin);
	}

	// struct dimensiune *dimensiuni_vechi = *dim;
	*dim = (struct dimensiune *)realloc(*dim, nr * sizeof(struct dimensiune));
	if (*dim == NULL) {} // TODO

	// int ***mat_vechi = *mat;
	(*mat) = (int ***)realloc(*mat, nr * sizeof(int **));
	if (*mat == NULL) {} // TODO
}

void inserare_mat(int ****mat, struct dimensiune **dim, int nr, int **a, int n,
				  int m)
{
	modif_nr_matrice(mat, dim, nr, nr + 1);
	if (*mat != NULL) {
		(*dim)[nr].lin = n;
		(*dim)[nr].col = m;
		(*mat)[nr] = a;
	}
}
void mutare_matrice(int **dest, int **src, int n, int m)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			dest[i][j] = src[i][j];
		}
	}

	eliberare_matrice(src, n);
}
