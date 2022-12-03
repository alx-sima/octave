// Copyright Sima Alexandru 312CA 2022-2023

#ifndef COMENZI_H
#define COMENZI_H

int comanda_adaugare(int ****mat, int **lin, int **col, int *nr);

void comanda_dimensiuni(int *lin, int *col, int nr);

void comanda_afisare(int ***mat, int *lin, int *col, int nr);

int comanda_redimensionare(int ***matrice, int *lin, int *col, int nr);

int comanda_produs(int ****mat, int **lin, int **col, int *nr);

int comanda_sortare(int ***mat, int *lin, int *col, int nr);

int comanda_transpunere(int ***mat, int *lin, int *col, int nr);

int comanda_putere(int ***mat, int *lin, int *col, int nr);

int comanda_stergere(int ****mat, int **lin, int **col, int *nr);

int comanda_prod_strassen(int ****mat, int **lin, int **col, int *nr);

#endif // COMENZI_H
