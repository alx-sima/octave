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
			// Daca exista o eroare se dealoca
			// toate randurile alocate pana acum.
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

void modif_nr_matrice(int ****mat, int **lin, int **col, int nr)
{
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
	modif_nr_matrice(mat, lin, col, nr + 1);
	if (*mat) {
		(*mat)[nr] = a;
		(*lin)[nr] = n;
		(*col)[nr] = m;
	}
}
