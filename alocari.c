// Copyright Sima Alexandru 312CA 2022-2023

#include <stdlib.h>

#include "alocari.h"

// Realoca `mat`, `lin` si `col` astfel incat sa aiba lungimea `nr`, apoi
// returneaza noul `mat`, sau NULL, daca a intervenit o eroare.
static int ***modif_nr_matrice(int ***mat, int **lin, int **col, int nr);

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

void eliberare_matrice(int **mat, int n)
{
	for (int i = 0; i < n; ++i)
		free(mat[i]);
	free(mat);
}

void eliberare_vector_matrice(int **mat[], int nr, int n)
{
	for (int i = 0; i < nr; ++i)
		eliberare_matrice(mat[i], n);
}

int ***inserare_mat(int ***mat, int **lin, int **col, int *nr, int **a, int n,
					int m)
{
	mat = modif_nr_matrice(mat, lin, col, *nr + 1);
	if (!mat)
		return NULL;

	(*lin)[*nr] = n;
	(*col)[*nr] = m;
	mat[*nr] = a;
	++(*nr);
	return mat;
}

int ***stergere_mat(int ***mat, int **lin, int **col, int *nr)
{
	// Daca exista o singura matrice in lista,
	// se dealoca toti vectorii.
	if (*nr == 1) {
		free(mat);
		free(*lin);
		free(*col);
		*nr = 0;
		*lin = NULL;
		*col = NULL;
		return NULL;
	}

	int ***mat_nou = modif_nr_matrice(mat, lin, col, *nr - 1);
	// Daca intervine o eroare la alocari, `nr` nu se modifica
	// pentru a nu ramane valori leakuite.
	if (mat_nou)
		--(*nr);
	return mat_nou;
}

static int ***modif_nr_matrice(int ***mat, int **lin, int **col, int nr)
{
	int *lin_nou = (int *)realloc(*lin, nr * sizeof(int));
	if (!lin_nou)
		return NULL;

	int *col_nou = (int *)realloc(*col, nr * sizeof(int));
	if (!col_nou) {
		free(lin_nou);
		return NULL;
	}

	int ***mat_nou = (int ***)realloc(mat, nr * sizeof(int **));
	if (!mat_nou) {
		free(lin_nou);
		free(col_nou);
		return NULL;
	}

	*lin = lin_nou;
	*col = col_nou;
	return mat_nou;
}
