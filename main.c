// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "comenzi.h"

int main(void)
{
	int ***matrice = NULL;
	int *nr_linii = NULL;
	int *nr_coloane = NULL;
	int nr_mat = 0;
	char operatie;

	while (scanf(" %c", &operatie)) {
		switch (operatie) {
		case 'L':
			cmd_adaugare_matrice(&matrice, &nr_linii, &nr_coloane, &nr_mat);
			break;
		case 'D':
			cmd_afisare_dimensiuni(nr_linii, nr_coloane, nr_mat);
			break;
		case 'P':
			cmd_afisare_matrice(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'C':
			cmd_redimensionare_matrice(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'M':
			cmd_inmultire_matrice(&matrice, &nr_linii, &nr_coloane, &nr_mat);
			break;
		case 'O':
			cmd_sortare_matrice(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'T':
			cmd_transpunere_matrice(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'R':
			cmd_exp_matrice(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'F':
			cmd_stergere_matrice(&matrice, &nr_linii, &nr_coloane, &nr_mat);
			break;
		case 'Q':
			cmd_eliberare_resurse(matrice, nr_linii, nr_coloane, nr_mat);
			return 0;
		case 'S':
			cmd_produs_strassen(&matrice, &nr_linii, &nr_coloane, &nr_mat);
			break;
		default:
			printf("Unrecognized command\n");
		}
	}
}
