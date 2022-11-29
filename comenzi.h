// Copyright Sima Alexandru 312CA 2022-2023

#ifndef COMENZI_H
#define COMENZI_H

void cmd_adaugare_matrice(int ****mat, int **lin, int **col, int *nr);
void cmd_afisare_dimensiuni(int *lin, int *col, int nr);
void cmd_afisare_matrice(int ***mat, int *lin, int *col, int nr);
void cmd_redimensionare_matrice(int ***matrice, int *lin, int *col, int nr);
void cmd_inmultire_matrice(int ****mat, int **lin, int **col, int *nr);
void cmd_sortare_matrice(int ***mat, int *lin, int *col, int nr);
void cmd_transpunere_matrice(int ***mat, int *lin, int *col, int nr);
void cmd_exp_matrice(int ***mat, int *lin, int *col, int nr);
void cmd_stergere_matrice(int ****mat, int **lin, int **col, int *nr);
void cmd_eliberare_resurse(int ***mat, int *lin, int *col, int nr);
void cmd_produs_strassen(int ****mat, int **lin, int **col, int *nr);

#endif // COMENZI_H
