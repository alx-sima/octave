// Copyright Sima Alexandru 312CA 2022-2023

#include <stdio.h>
#include <stdlib.h>

#include "alocari.h"
#include "comenzi.h"

int main(void)
{
	int ***matrice = NULL;
	int *v_linii = NULL;
	int *v_coloane = NULL;
	int nr_mat = 0;
	int e_eroare = 0;
	char operatie;

	while (scanf(" %c", &operatie) != EOF) {
		switch (operatie) {
		case 'L':
			e_eroare =
				comanda_adaugare(&matrice, &v_linii, &v_coloane, &nr_mat);
			break;
		case 'D':
			comanda_dimensiuni(v_linii, v_coloane, nr_mat);
			break;
		case 'P':
			comanda_afisare(matrice, v_linii, v_coloane, nr_mat);
			break;
		case 'C':
			e_eroare =
				comanda_redimensionare(matrice, v_linii, v_coloane, nr_mat);
			break;
		case 'M':
			e_eroare = comanda_produs(&matrice, &v_linii, &v_coloane, &nr_mat);
			break;
		case 'O':
			e_eroare = comanda_sortare(matrice, v_linii, v_coloane, nr_mat);
			break;
		case 'T':
			e_eroare = comanda_transpunere(matrice, v_linii, v_coloane, nr_mat);
			break;
		case 'R':
			e_eroare = comanda_putere(matrice, v_linii, v_coloane, nr_mat);
			break;
		case 'F':
			e_eroare =
				comanda_stergere(&matrice, &v_linii, &v_coloane, &nr_mat);
			break;
		case 'Q':
			eliberare_resurse(matrice, v_linii, v_coloane, nr_mat);
			return EXIT_SUCCESS;
		case 'S':
			e_eroare =
				comanda_prod_strassen(&matrice, &v_linii, &v_coloane, &nr_mat);
			break;
		default:
			printf("Unrecognized command\n");
		}

		// Daca a intervenit o eroare, se elibereaza toate
		// matricele si se inchide programul.
		if (e_eroare) {
			fprintf(stderr,
					"A intervenit o eroare in timpul alocarii memoriei\n");
			eliberare_resurse(matrice, v_linii, v_coloane, nr_mat);
			return EXIT_FAILURE;
		}
	}

	eliberare_resurse(matrice, v_linii, v_coloane, nr_mat);
	return EXIT_SUCCESS;
}
