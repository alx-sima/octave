// Copyright Sima Alexandru 312CA 2022-2023

#ifndef _UTILS_H
#define _UTILS_H

#define NR_MOD 10007

void interschimba(int *a, int *b);
int **citire_matrice(int n, int m);
void micsorare_matrice(int ***mat, int n_vechi, int n, int m);
int **prod_matrice(int **a, int **b, int n, int m, int o);
int modulo(long x);
#endif // _UTILS_H