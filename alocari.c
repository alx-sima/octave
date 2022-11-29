// Copyright Sima Alexandru 312CA 2022-2023

#include <stdlib.h>

#include "alocari.h"

int **alocare_matrice(int n, int m)
{
	int **a = (int **)malloc(n * sizeof(int *));
	if (!a)
		return NULL;

	for (int i = 0; i < n; ++i) {
		a[i] = (int *)malloc(m * sizeof(int));

		if (!a[i]) {
			// Se dealoca toate randurile
			// alocate pana acum.
			eliberare_matrice(a, i);
			return NULL;
		}
	}

	return a;
}

void eliberare_vector_matrice(int **mat[], int nr, int n)
{
	for (int i = 0; i < nr; ++i)
		eliberare_matrice(mat[i], n);
}

void eliberare_matrice(int **mat, int n)
{
	for (int i = 0; i < n; ++i)
		free(mat[i]);
	free(mat);
}

void redimensionare_matrice(int ***mat, int n_vechi, int n, int m)
{
	// Se elibereaza liniile in plus (daca se micsoreaza numarul de linii).
	for (int i = n; i < n_vechi; ++i)
		free((*mat)[i]);

	*mat = (int **)realloc(*mat, n * sizeof(int *));
	if (!*mat) {
		eliberare_matrice(*mat, n);
		return;
	}

	// TODO: fixme
	// Se aloca liniile noi (daca exista).
	for (int i = n_vechi; i < n; ++i)
		(*mat)[i] = NULL; // pt ca realocul sa functioneze ca un malloc

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

void modif_nr_matrice(int ****mat, int **lin, int **col, int nr_vechi, int nr)
{
	// Se elibereaza matricele in plus (daca exista).
	for (int i = nr; i < nr_vechi; ++i)
		eliberare_matrice((*mat)[i], (*lin)[i]);

	// struct dimensiune *dimensiuni_vechi = *lin;
	*lin = (int *)realloc(*lin, nr * sizeof(int));
	*col = (int *)realloc(*col, nr * sizeof(int));
	// TODO
	// if (!*lin) {}
	// TODO
	// if (!*col) {}

	// int ***mat_vechi = *mat;
	(*mat) = (int ***)realloc(*mat, nr * sizeof(int **));
	// TODO
	// if (!*mat) {}
}

void inserare_mat(int ****mat, int **lin, int **col, int nr, int **a, int n,
				  int m)
{
	modif_nr_matrice(mat, lin, col, nr, nr + 1);
	if (*mat) {
		(*lin)[nr] = n;
		(*col)[nr] = m;
		(*mat)[nr] = a;
	}
}
