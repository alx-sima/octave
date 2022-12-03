// Copyright Sima Alexandru 312CA 2022-2023

#ifndef ALOCARI_H
#define ALOCARI_H

// Aloca o matrice `n X m`.
int **alocare_matrice(int n, int m);

// Dealoca matricea `mat` de `n` linii.
void eliberare_matrice(int **mat, int n);

// Dealoca `nr` matrice de `n` linii din `mat`.
void eliberare_vector_matrice(int **mat[], int nr, int n);

// Aloca o noua matrice de `n` linii si `m` coloane cu elementele din `sursa`.
int **copiere_matrice(int **sursa, int n, int m);

// Adauga matricea `a`, de dimensiuni `n X m` la finalul listei de matrice.
int ***inserare_mat(int ***mat, int **lin, int **col, int *nr, int **a, int n,
					int m);

// Sterge matricea de la finalul listei de matrice `mat`,
// apoi returneaza noua lista (sau NULL daca a intervenit o eroare).
int ***stergere_mat(int ***mat, int **lin, int **col, int *nr);

// Dealoca toate matricele din lista, apoi lista insasi.
void eliberare_resurse(int ***mat, int *lin, int *col, int nr);

#endif // ALOCARI_H
