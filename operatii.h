// Copyright Sima Alexandru 312CA 2022-2023

#ifndef _OPERATII_H
#define _OPERATII_H

// FIXME:
struct dimensiune {
	int lin;
	int col;
};

void op_adaugare_matrice(int ****mat, struct dimensiune **dim, int *nr);
void op_afisare_dimensiuni(struct dimensiune *dim, int nr);
void op_afisare_matrice(int ***mat, struct dimensiune *dim, int nr);
void op_redimensionare_matrice(int ***matrice, struct dimensiune *dim, int nr);
void op_inmultire_matrice(int ****mat, struct dimensiune **dim, int *nr);
void op_sortare_matrice(int ***mat, struct dimensiune *dim, int nr);
void op_exp_matrice(int ***mat, struct dimensiune *dim, int nr);
void op_eliberare_resurse(int ***mat, struct dimensiune *dim, int nr);

#endif // _OPERATII_H