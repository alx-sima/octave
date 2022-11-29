// Copyright Sima Alexandru 312CA 2022-2023

#ifndef ALOCARI_H
#define ALOCARI_H

// Aloca o matrice `(n x m)`.
int **alocare_matrice(int n, int m);

void eliberare_vector_matrice(int **mat[], int nr, int n);

// Dealoca matricea de `mat` de `n` linii.
void eliberare_matrice(int **mat, int n);

void modif_nr_matrice(int ****mat, int **lin, int **col, int nr_vechi, int nr);

void inserare_mat(int ****mat, int **lin, int **col, int nr, int **a, int n,
				  int m);

#endif // ALOCARI_H
