// Copyright Sima Alexandru 312CA 2022-2023

#include <stdlib.h>

#include "alocari.h"
#include "operatii.h"
#include "strassen.h"
#include "utilitare.h"

#define NR_MAT_AJUT 7

// Calculeaza matricea C, unde Cij = Aij + semn*Bij, adica:
// - `C = A + B`, daca `semn = +1`;
// - `C = A - B`, daca `semn = -1`;
static int **adunare_matrice(int **a, int **b, int n, int semn)
{
	int **c = alocare_matrice(n, n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			c[i][j] = modulo((long)a[i][j] + semn * b[i][j]);
	}
	return c;
}

static int impartire_cadrane(int **cadrane[4], int **a, int n)
{
	int *temp = (int *)malloc(n * 2 * sizeof(int));
	if (!temp)
		return 0;

	for (int i = 0; i < n * 2; ++i)
		temp[i] = i;

	// !!! Doamne-ajuta !!!
	// ? Codul nu are nevoie de documentatie, codul este documentatia
	// ? Daca merge, merge
	for (int i = 0; i < 4; ++i) {
		cadrane[i] = partitionare_matrice(a, temp + (i >> 1 & 1) * n,
										  temp + (i & 1) * n, n, n);
		if (!cadrane[i]) {
			eliberare_vector_matrice(cadrane, i, n);
			free(temp);
			return 0;
		}
	}

	free(temp);
	return 1;
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

// TODO comenteaza
// Genereaza in `rez` sume de elemente din `v`, in functie de modelul din `st`,
// `dr` si `semn`. Astfel rez[i] va contine
void gen_sume_part(int **rez[], int **v[], int n, const char st[],
				   const char dr[], const char semn[])
{
	for (int i = 0; st[i]; ++i)
		rez[i] = adunare_matrice(v[st[i] - '0'], v[dr[i] - '0'], n,
								 semn[i] == '+' ? 1 : -1);
}

void gen_prod_part(int **rez[], int **s_part_a[], int **s_part_b[],
				   int **cadrane_a[], int **cadrane_b[], int n)
{
	int **factori_st[] = {
		s_part_a[0], s_part_a[1], cadrane_a[0], cadrane_a[3],
		s_part_a[2], s_part_a[3], s_part_a[4],
	};
	int **factori_dr[] = {
		s_part_b[0],  cadrane_b[0], s_part_b[1], s_part_b[2],
		cadrane_b[3], s_part_b[3],	s_part_b[4],
	};

	for (int i = 0; i < NR_MAT_AJUT; ++i) {
		rez[i] = prod_strassen(factori_st[i], factori_dr[i], n);
		if (!rez[i]) {
			eliberare_vector_matrice(rez, i, n);
			return;
		}
	}
}

int **prod_strassen(int **a, int **b, int n)
{
	// Daca `a` si `b` au devenit 1x1, produsul lor
	// se face inmultind cele 2 numere.
	if (n == 1) {
		int **rez = alocare_matrice(1, 1);
		if (rez)
			rez[0][0] = a[0][0] * b[0][0];
		return rez;
	}

	n /= 2;
	int **cadrane_a[4];
	int **cadrane_b[4];

	// TODO error checking
	impartire_cadrane(cadrane_a, a, n);
	impartire_cadrane(cadrane_b, b, n);

	int **s_part_a[5];
	int **s_part_b[5];
	gen_sume_part(s_part_a, cadrane_a, n, "02021", "33103", "+++--");
	gen_sume_part(s_part_b, cadrane_b, n, "01202", "33013", "+--++");

	int **m[7];
	gen_prod_part(m, s_part_a, s_part_b, cadrane_a, cadrane_b, n);

	int **c_part[4];
	gen_sume_part(c_part, m, n, "0602", "3415", "+--+");

	int **c[4] = {
		adunare_matrice(c_part[0], c_part[1], n, 1),
		adunare_matrice(m[2], m[4], n, 1),
		adunare_matrice(m[1], m[3], n, 1),
		adunare_matrice(c_part[2], c_part[3], n, 1),
	};

	eliberare_vector_matrice(cadrane_a, 4, n);
	eliberare_vector_matrice(cadrane_b, 4, n);
	eliberare_vector_matrice(s_part_a, 5, n);
	eliberare_vector_matrice(s_part_b, 5, n);
	eliberare_vector_matrice(m, 7, n);
	eliberare_vector_matrice(c_part, 4, n);

	return reconstituire_matrice(c, n);
}
