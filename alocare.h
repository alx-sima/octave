// Copyright Sima Alexandru 312CA 2022-2023

#ifndef _ALOCARE_H
#define _ALOCARE_H

#include "operatii.h"

int **alocare_matrice(int n, int m);
void inserare_mat(int ****mat, struct dimensiune **dim, int *nr, int **a, int n,
				  int m);
void eliberare_matrice(int **mat, int n);

#endif // _ALOCARE_H