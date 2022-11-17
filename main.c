// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocare.h"
#include "operatii.h"

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
			op_adaugare_matrice(&matrice, &dimensiuni, &nr_mat);
			break;
		case 'D':
			op_afisare_dimensiuni(dimensiuni, nr_mat);
			break;
		case 'P':
			op_afisare_matrice(matrice, dimensiuni, nr_mat);
			break;
		case 'C':
			op_redimensionare_matrice(matrice, dimensiuni, nr_mat);
			break;
		case 'M':
			op_inmultire_matrice(&matrice, &dimensiuni, &nr_mat);
			break;
		case 'O':
			op_sortare_matrice(matrice, dimensiuni, nr_mat);
			break;
		case 'T':
			break;
		case 'R':
			break;
		case 'F':
			break;
		case 'Q':
			op_eliberare_resurse(matrice, dimensiuni, nr_mat);
			return 0;
		case 'S':
			break;
		default:
			printf("Unrecognized command\n");
		}
	}
}
