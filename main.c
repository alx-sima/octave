// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "comenzi.h"

int main(void)
{
	int ***matrice = NULL;
	struct dimensiune *dimensiuni = NULL;
	int nr_mat = 0;
	char operatie;

	while (1) {
		scanf(" %c", &operatie);
		switch (operatie) {
		case 'L':
			cmd_adaugare_matrice(&matrice, &dimensiuni, &nr_mat);
			break;
		case 'D':
			cmd_afisare_dimensiuni(dimensiuni, nr_mat);
			break;
		case 'P':
			cmd_afisare_matrice(matrice, dimensiuni, nr_mat);
			break;
		case 'C':
			cmd_redimensionare_matrice(matrice, dimensiuni, nr_mat);
			break;
		case 'M':
			cmd_inmultire_matrice(&matrice, &dimensiuni, &nr_mat);
			break;
		case 'O':
			cmd_sortare_matrice(matrice, dimensiuni, nr_mat);
			break;
		case 'T':
			cmd_transpunere_matrice(matrice, dimensiuni, nr_mat);
			break;
		case 'R':
			cmd_exp_matrice(matrice, dimensiuni, nr_mat);
			break;
		case 'F':
			cmd_stergere_matrice(&matrice, &dimensiuni, &nr_mat);
			break;
		case 'Q':
			cmd_eliberare_resurse(matrice, dimensiuni, nr_mat);
			return 0;
		case 'S':
			// TODO:
			break;
		default:
			printf("Unrecognized command\n");
		}
	}
}
