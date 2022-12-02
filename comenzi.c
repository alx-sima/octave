// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocari.h"
#include "comenzi.h"
#include "operatii.h"
#include "strassen.h"
#include "utilitare.h"

// Verifica daca indicele `i` este valid (apartine `[0, n)`).
static int e_index_valid(int i, int n);

static int citire_index(int n);

// Citeste 2 indecsi de matrice de la tastatura, apoi verifica daca sunt valizi
// si daca cele 2 matrice pot fi inmultite (nr. de linii al primeia = nr. de
// coloane ale celei de a 2-a).
static int citire_matrice_produs(int *col, int *lin, int n, int *a, int *b);

int comanda_adaugare(int ****mat, int **lin, int **col, int *nr)
{
	int n, m;
	scanf("%d%d", &n, &m);

	int **a = citire_matrice(n, m);
	if (!a)
		return 1;

	int ***mat_nou = inserare_mat(*mat, lin, col, nr, a, n, m);
	if (!mat_nou)
		return 1;

	*mat = mat_nou;
	return 0;
}

void comanda_dimensiuni(int *lin, int *col, int nr)
{
	int index = citire_index(nr);
	if (index != -1)
		printf("%d %d\n", lin[index], col[index]);
}

void comanda_afisare(int ***mat, int *lin, int *col, int nr)
{
	int index = citire_index(nr);
	if (index != -1)
		printare_matrice(mat[index], lin[index], col[index]);
}

int comanda_redimensionare(int ***matrice, int *lin, int *col, int nr)
{
	int l, c;
	int index;
	index = citire_index(nr);

	scanf("%d", &l);
	int *linii = (int *)malloc(l * sizeof(int));
	if (!linii)
		return 1;

	for (int i = 0; i < l; ++i)
		scanf("%d", &linii[i]);

	scanf("%d", &c);
	int *coloane = (int *)malloc(c * sizeof(int));

	if (!coloane) {
		free(linii);
		return 1;
	}

	for (int i = 0; i < c; ++i)
		scanf("%d", &coloane[i]);

	if (index == -1) {
		free(linii);
		free(coloane);
		return 0;
	}

	int **aux = partitionare_matrice(matrice[index], linii, coloane, l, c);
	if (!aux) {
		free(linii);
		free(coloane);
		return 1;
	}

	eliberare_matrice(matrice[index], lin[index]);
	matrice[index] = aux;
	lin[index] = l;
	col[index] = c;
	free(linii);
	free(coloane);
	return 0;
}

int comanda_produs(int ****mat, int **lin, int **col, int *nr)
{
	int x, y;
	if (!citire_matrice_produs(*col, *lin, *nr, &x, &y))
		return 0;

	int **c =
		prod_matrice((*mat)[x], (*mat)[y], (*lin)[x], (*col)[x], (*col)[y]);
	if (!c)
		return 1;
	int ***mat_nou = inserare_mat(*mat, lin, col, nr, c, (*lin)[x], (*col)[y]);
	if (!mat_nou)
		return 1;
	*mat = mat_nou;
	return 0;
}

int comanda_sortare(int ***mat, int *lin, int *col, int nr)
{
	int *sume = (int *)calloc(nr, sizeof(int));
	if (!sume)
		return 1;

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
	return 0;
}

int comanda_transpunere(int ***mat, int *lin, int *col, int nr)
{
	int index = citire_index(nr);
	if (index == -1)
		return 0;

	int n = lin[index];
	int m = col[index];

	int **transpusa = alocare_matrice(m, n);
	if (!transpusa)
		return 1;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			transpusa[j][i] = mat[index][i][j];
	}
	eliberare_matrice(mat[index], n);
	mat[index] = transpusa;
	interschimba(&lin[index], &col[index]);
	return 0;
}

int comanda_exponentiere(int ***mat, int *lin, int *col, int nr)
{
	int index, exp;
	index = citire_index(nr);
	scanf("%d", &exp);

	if (index == -1)
		return 0;

	if (exp < 0) {
		printf("Power should be positive\n");
		return 0;
	}

	if (lin[index] != col[index]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}

	int **rez = exp_matrice(mat[index], lin[index], exp);
	if (!rez)
		return 1;

	mat[index] = rez;
	return 0;
}

int comanda_stergere(int ****mat, int **lin, int **col, int *nr)
{
	int index = citire_index(*nr);
	if (index == -1)
		return 0;

	eliberare_matrice((*mat)[index], (*lin)[index]);

	for (int i = index; i < *nr - 1; ++i) {
		(*mat)[i] = (*mat)[i + 1];
		(*lin)[i] = (*lin)[i + 1];
		(*col)[i] = (*col)[i + 1];
	}
	int ***mat_nou = stergere_mat(*mat, lin, col, nr);
	// if (!mat_nou) {return;}
	*mat = mat_nou;
	return 0;
}

void eliberare_resurse(int ***mat, int *lin, int *col, int nr)
{
	// Daca nu exista nicio matrice, toate
	// resursele au fost deja dealocate.
	if (!nr)
		return;

	for (int i = 0; i < nr; ++i)
		eliberare_matrice(mat[i], lin[i]);

	free(mat);
	free(lin);
	free(col);
}

int comanda_prod_strassen(int ****mat, int **lin, int **col, int *nr)
{
	int x, y;

	if (!citire_matrice_produs(*col, *lin, *nr, &x, &y))
		return 0;

	int **rez = prod_strassen((*mat)[x], (*mat)[y], (*lin)[x]);
	if (!rez)
		return 1;

	int ***mat_nou =
		inserare_mat(*mat, lin, col, nr, rez, (*lin)[x], (*lin)[x]);
	// if (!mat_nou) {}
	*mat = mat_nou;
	return 0;
}

static int e_index_valid(int i, int n)
{
	return i >= 0 && i < n;
}

static int citire_index(int n)
{
	int index;
	scanf("%d", &index);

	if (e_index_valid(index, n))
		return index;
	printf("No matrix with the given index\n");
	return -1;
}

static int citire_matrice_produs(int *col, int *lin, int n, int *a, int *b)
{
	scanf("%d%d", a, b);
	if (!(e_index_valid(*a, n) && e_index_valid(*b, n))) {
		printf("No matrix with the given index\n");
		return 0;
	}

	if (col[*a] != lin[*b]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}

	return 1;
}
