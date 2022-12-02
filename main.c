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
	int e_eroare = 0;
	char operatie;

	while (scanf(" %c", &operatie)) {
		switch (operatie) {
		case 'L':
			e_eroare =
				comanda_adaugare(&matrice, &nr_linii, &nr_coloane, &nr_mat);
			break;
		case 'D':
			comanda_dimensiuni(nr_linii, nr_coloane, nr_mat);
			break;
		case 'P':
			comanda_afisare(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'C':
			e_eroare =
				comanda_redimensionare(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'M':
			e_eroare =
				comanda_produs(&matrice, &nr_linii, &nr_coloane, &nr_mat);
			break;
		case 'O':
			e_eroare = comanda_sortare(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'T':
			e_eroare =
				comanda_transpunere(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'R':
			e_eroare =
				comanda_exponentiere(matrice, nr_linii, nr_coloane, nr_mat);
			break;
		case 'F':
			e_eroare =
				comanda_stergere(&matrice, &nr_linii, &nr_coloane, &nr_mat);
			break;
		case 'Q':
			eliberare_resurse(matrice, nr_linii, nr_coloane, nr_mat);
			return 0;
		case 'S':
			e_eroare = comanda_prod_strassen(&matrice, &nr_linii, &nr_coloane,
											 &nr_mat);
			break;
		default:
			printf("Unrecognized command\n");
		}

		if (e_eroare) {
			fprintf(stderr,
					"A intervenit o eroare in timpul alocarii memoriei\n");
			eliberare_resurse(matrice, nr_linii, nr_coloane, nr_mat);
			return EXIT_FAILURE;
		}
	}
}
