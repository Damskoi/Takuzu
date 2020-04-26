#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "fonctions.h"


int main(void){

	color_printf(GREEN, MAGENTA, "Début du programme"); printf("\n");
	printf("*********************************************************\n\n");

/*	// parti 1
	test_creer_grille();
	test_est_indice_valide();
	test_est_cellule();
	test_get_val_cellule();
	test_set_val_cellule();
	test_est_cellule_initiale();
	test_est_cellule_vide();
	test_afficher_grille();

	// parti 2

	test_rendre_cellule_initiale();
	test_initialiser_grille();
	test_est_grille_pleine();
	test_pas_zero_un_consecutifs();
	test_meme_nombre_zero_un();
	test_lignes_colonnes_distinctes();
	test_est_partie_gagnee();
*/

	lancer_partie();

	printf("\n*********************************************************\n");
	color_printf(YELLOW, CYAN, "Fin du programme"); printf("\n");	
	return 0;
}

