// Copyright Sima Alexandru 312CA 2022-2023

#ifndef COMENZI_H
#define COMENZI_H

// FIXME
struct dimensiune {
	int lin;
	int col;
};

void cmd_adaugare_matrice(int ****mat, struct dimensiune **dim, int *nr);
void cmd_afisare_dimensiuni(struct dimensiune *dim, int nr);
void cmd_afisare_matrice(int ***mat, struct dimensiune *dim, int nr);
void cmd_redimensionare_matrice(int ***matrice, struct dimensiune *dim, int nr);
void cmd_inmultire_matrice(int ****mat, struct dimensiune **dim, int *nr);
void cmd_sortare_matrice(int ***mat, struct dimensiune *dim, int nr);
void cmd_transpunere_matrice(int ***mat, struct dimensiune *dim, int nr);
void cmd_exp_matrice(int ***mat, struct dimensiune *dim, int nr);
void cmd_stergere_matrice(int ****mat, struct dimensiune **dim, int *nr);
void cmd_eliberare_resurse(int ***mat, struct dimensiune *dim, int nr);

#endif // COMENZI_H
