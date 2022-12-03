// Copyright Sima Alexandru 312CA 2022-2023

#include <stdlib.h>

#include "alocari.h"
#include "operatii.h"
#include "strassen.h"

#define NR_CADRANE 4
#define NR_SUME_PART 5
#define NR_MAT_AJUT 7

// Converteste caracterul `c` intr-o cifra.
static inline int cifra(char c);

// Imparte matricea `a` in 4 cadrane de `n` linii si coloane.
static int impartire_cadrane(int **cadrane[], int **a, int n);

// Genereaza `nr` sume de elemente din `v`, pe care le retine in `rez` astfel:
// pe pozitia `i` in `rez` se va afla al `st[i]` -lea element din `v` adunat
// cu/din care se scade (in functie de `semn[i]`) al `dr[i]` -lea.
static int gen_sume_part(int **rez[], int **v[], int n, const char st[],
						 const char dr[], const char semn[], int nr);

// Calculeaza in `rez` cele 7 matrice ajutatoare pentru calcularea produsului.
static int gen_mat_ajut(int **rez[], int **s_part_a[], int **s_part_b[],
						int **cadrane_a[], int **cadrane_b[], int n);

// Calculeaza in `rez` cadranele matricei-produs.
static int gen_cadrane_finale(int **rez[], int **c_part[], int **m[], int n);

// Construieste o matrice din cele 4 cadrane nxn ale ei (inversul functiei
// `impartire cadrane`).
static int **reconstituire_matrice(int **c[], int n);

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

	int **cadrane_a[NR_CADRANE];
	int **cadrane_b[NR_CADRANE];
	int **s_part_a[NR_SUME_PART];
	int **s_part_b[NR_SUME_PART];
	int **m[NR_MAT_AJUT];
	int **c_part[NR_CADRANE];
	int **c[NR_CADRANE];

	int e_eroare = 0;
	n /= 2;

	if (impartire_cadrane(cadrane_a, a, n))
		return NULL;
	if (impartire_cadrane(cadrane_b, b, n)) {
		eliberare_vector_matrice(cadrane_a, NR_CADRANE, n);
		return NULL;
	}

	if (gen_sume_part(s_part_a, cadrane_a, n, "02021", "33103", "+++--",
					  NR_SUME_PART)) {
		eliberare_vector_matrice(cadrane_a, NR_CADRANE, n);
		eliberare_vector_matrice(cadrane_b, NR_CADRANE, n);
		return NULL;
	}

	if (gen_sume_part(s_part_b, cadrane_b, n, "01202", "33013", "+--++",
					  NR_SUME_PART)) {
		eliberare_vector_matrice(cadrane_a, NR_CADRANE, n);
		eliberare_vector_matrice(cadrane_b, NR_CADRANE, n);
		eliberare_vector_matrice(s_part_a, NR_SUME_PART, n);
		return NULL;
	}

	e_eroare = gen_mat_ajut(m, s_part_a, s_part_b, cadrane_a, cadrane_b, n);

	eliberare_vector_matrice(cadrane_a, NR_CADRANE, n);
	eliberare_vector_matrice(cadrane_b, NR_CADRANE, n);
	eliberare_vector_matrice(s_part_a, NR_SUME_PART, n);
	eliberare_vector_matrice(s_part_b, NR_SUME_PART, n);
	if (e_eroare)
		return NULL;

	if (gen_sume_part(c_part, m, n, "0602", "3415", "+--+", NR_CADRANE)) {
		eliberare_vector_matrice(m, NR_MAT_AJUT, n);
		return NULL;
	}

	e_eroare = gen_cadrane_finale(c, c_part, m, n);

	eliberare_vector_matrice(m, NR_MAT_AJUT, n);
	eliberare_vector_matrice(c_part, NR_CADRANE, n);
	if (e_eroare)
		return NULL;

	int **rez = reconstituire_matrice(c, n);
	eliberare_vector_matrice(c, 4, n);
	return rez;
}

static inline int cifra(char c)
{
	return c - '0';
}

static int impartire_cadrane(int **cadrane[], int **a, int n)
{
	int *v_lin_col = (int *)malloc(n * 2 * sizeof(int));
	if (!v_lin_col)
		return 0;

	for (int i = 0; i < n * 2; ++i)
		v_lin_col[i] = i;

	// Exista 4 cadrane, numerotate de la 0 la 3.
	// Codificarea lor in baza 2 ne ajuta sa facem impartirea mai usor:
	// 00 | 01
	// -------
	// 10 | 11
	// Astfel, daca primul bit (`i >> 1 & 1`) este 1, se vor selecta ultimele
	// `n` linii in loc de primele, iar daca al 2-lea (`i >> 1`) este 1, se va
	// proceda la fel pentru coloane.
	// Pentru a selecta liniile/coloanele, se foloseste operatia de
	// partitionare: se aloca un vector cu valorile 1..2*n. Daca bitul respectiv
	// e 1, se transmite vectorul incepand de la pozitia `n` (a 2-a jumatate).
	for (int i = 0; i < NR_CADRANE; ++i) {
		int deplasare_x = (i >> 1 & 1) * n;
		int deplasare_y = (i & 1) * n;
		cadrane[i] = partitionare_matrice(a, v_lin_col + deplasare_x,
										  v_lin_col + deplasare_y, n, n);
		if (!cadrane[i]) {
			eliberare_vector_matrice(cadrane, i, n);
			free(v_lin_col);
			return 1;
		}
	}

	free(v_lin_col);
	return 0;
}

static int gen_sume_part(int **rez[], int **v[], int n, const char st[],
						 const char dr[], const char semn[], int nr)
{
	for (int i = 0; i < nr; ++i) {
		rez[i] = adunare_matrice(v[cifra(st[i])], v[cifra(dr[i])], n,
								 semn[i] == '+' ? 1 : -1);
		if (!rez[i]) {
			eliberare_vector_matrice(rez, i, n);
			return 1;
		}
	}
	return 0;
}

static int gen_mat_ajut(int **rez[], int **s_part_a[], int **s_part_b[],
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
			return 1;
		}
	}

	return 0;
}

static int gen_cadrane_finale(int **rez[], int **c_part[], int **m[], int n)
{
	int **termeni_st[] = {c_part[0], m[2], m[1], c_part[2]};
	int **termeni_dr[] = {c_part[1], m[4], m[3], c_part[3]};

	for (int i = 0; i < NR_CADRANE; ++i) {
		rez[i] = adunare_matrice(termeni_st[i], termeni_dr[i], n, 1);
		if (!rez) {
			eliberare_vector_matrice(rez, i, n);
			return 1;
		}
	}

	return 0;
}

static int **reconstituire_matrice(int **c[], int n)
{
	int **a = alocare_matrice(n * 2, n * 2);
	if (!a)
		return NULL;

	for (int i = 0; i < NR_CADRANE; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k)
				// Se foloseste aceeasi impartire pe cadrane ca la
				// `impartire_cadrane()`.
				a[j + n * (i >> 1 & 1)][k + n * (i & 1)] = c[i][j][k];
		}
	}

	return a;
}
