// Copyright Sima Alexandru 312CA 2022-2023

#ifndef OPERATII_H
#define OPERATII_H

// Afiseaza elementele matricei `a`.
void printare_matrice(int **a, int n, int m);

int **partitionare_matrice(int **mat, int *lin, int *col, int nrlin, int nrcol);

// Aloca si intoarce matricea `In`.
int **identitate(int n);

// Calculeaza suma elementelor din matricea `a`.
int insumare_elemente(int **a, int n, int m);

// Calculeaza produsul a 2 matrice `a` (n x m) si `b` (m x o).
int **prod_matrice(int **a, int **b, int n, int m, int o);

// Calculeaza X^k.
int **exp_matrice(int **x, int n, int k);

#endif // OPERATII_H
