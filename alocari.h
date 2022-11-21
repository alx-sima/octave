// Copyright Sima Alexandru 312CA 2022-2023

#ifndef ALOCARI_H
#define ALOCARI_H

#include "comenzi.h"

// Aloca o matrice `(n x m)`.
int **alocare_matrice(int n, int m);

// Dealoca matricea de `mat` de `n` linii.
void eliberare_matrice(int **mat, int n);

// Functia va redimensiona matricea de `n_vechi` linii pointata de `mat`,
// facand-o de `n` linii si `m` coloane.
// Dupa apel, in `mat` se va retine noua adresa a matricei, sau `NULL`,
// daca a intervenit o eroare pe parcurs.
void redimensionare_matrice(int ***mat, int nr_vechi, int n, int m);

void modif_nr_matrice(int ****mat, struct dimensiune **dim, int nr_vechi,
					  int nr);
void inserare_mat(int ****mat, struct dimensiune **dim, int nr, int **a, int n,
				  int m);

// Copiaza toate elementele din matricea `src` in `dest`,
// avand dimensiunile `m x n`, apoi dealoca matricea sursa.
void mutare_matrice(int **dest, int **src, int n, int m);

#endif // ALOCARI_H
