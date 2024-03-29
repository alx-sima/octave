// Copyright Sima Alexandru 312CA 2022-2023

#ifndef OPERATII_H
#define OPERATII_H

// Aloca o matrice `n`x`m` si citeste de
// la tastatura elementele sale.
int **citire_matrice(int n, int m);

// Afiseaza elementele matricei `a`.
void printare_matrice(int **a, int n, int m);

// Aloca si intoarce o matrice care contine pe pozitia `(i,j)`, elementul de pe
// linia `lin[i]` si coloana `col[j]` din `mat`.
int **partitionare_matrice(int **mat, int *lin, int *col, int nrlin, int nrcol);

// Calculeaza suma elementelor din matricea `a`.
int insumare_elemente(int **a, int n, int m);

// Calculeaza matricea C, unde `Cij = Aij + semn*Bij`, adica:
// - `C = A + B`, daca `semn = +1`;
// - `C = A - B`, daca `semn = -1`;
int **adunare_matrice(int **a, int **b, int n, int semn);

// Calculeaza produsul a 2 matrice `a` (`n`x`m`) si `b` (`m`x`o`).
int **prod_matrice(int **a, int **b, int n, int m, int o);

// Calculeaza `baza^k` in timp logaritmic.
int **putere_matrice(int **baza, int n, int k);

#endif // OPERATII_H
