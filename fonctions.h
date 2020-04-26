#ifndef FONCTIONS
#define	FONCTIONS

// Couleurs possibles
typedef enum
  {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
  } COULEUR_TERMINAL;
void clear_terminal();
int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...);


                                /*   Debut Partie 1  */

// Q1 struct cellule
typedef struct{
	int val;
	int initial;
}	cellule;

// Q2 struct grille
typedef struct{
	cellule *tab;
	int n;
}	grille;

// Q3 creer grille
grille * creer_grille(int nb);

// Q4 destroy grille
void detruire_grille(grille *g);

// Q5 indice valide
int est_indice_valide(grille * g, int indice);

// Q6 cellule
int est_cellule(grille * g, int i, int j);

// Q7 obtenir valeurs de la cellule
int get_val_cellule(grille * g, int i, int j);

// Q8 def de la valeur d'un cellule
void set_val_cellule(grille * g, int i, int j, int val);

// Q9 cellule initiale
int est_cellule_initiale(grille * g, int i, int j);

// Q10 cellule (i, j) de la grille
int est_cellule_vide(grille * g, int i, int j);

// 	Q11 Affichage grille 
void afficher_grille_V1(grille * g);
void afficher_grille_V2(grille *g);
void afficher_grille_V3(grille *g);

                                /*   Fin Partie 1  */


                                /*   Debut Partie 2  */

//  Q12 rendre initiale 
void rendre_cellule_initiale(grille * g, int i, int j);

//	Q13 intializer grille a partir de fichier
grille * initialiser_grille(char nom_fichier[]);

//	Q14 grille rempli
int est_grille_pleine(grille * g);

//  Q15 nombre succesive
int pas_zero_un_consecutifs(grille * g);

//	Q16 meme nombre de chiffre
int meme_nombre_zero_un(grille * g);

//  Q17 colonnes distinctes
int lignes_colonnes_distinctes(grille * g);

//  Q18 Partie gagner
int est_partie_gagnee(grille * g);

                                /*   Fin Partie 2  */


                                /*   Debut Partie 3  */
//  Q19 mouvement valide
int est_mouvement_valide(grille * g, char mouv[], int * ligne, int * colonne, int * val);

//  Q20 Tour de jeu
void tour_de_jeu(grille * g);

//  Q21 Jouer
void jouer(char ch[]);

//  Q22 choisir grille
void choisir_grille(char s[]);


/*          FONCTIONS SUPPLE        */
void lancer_partie();



                                /*   Fonctions Test  */
//	Q3
void test_creer_grille();

//	Q5
void test_est_indice_valide();

//	Q6
void test_est_cellule();

//	Q7
void test_get_val_cellule();

//	Q8
void test_set_val_cellule();

//	Q9
void test_est_cellule_initiale();

//	Q10
void test_est_cellule_vide();

//	Q11
void test_afficher_grille();

//	Q12
void test_rendre_cellule_initiale();

//	Q13
void test_initialiser_grille();

//	Q14
void test_est_grille_pleine();

//  Q15
void test_pas_zero_un_consecutifs();

//  Q16
void test_meme_nombre_zero_un();

//  Q17
void test_lignes_colonnes_distinctes();

//  Q18
void test_est_partie_gagnee();

//  Q19
void test_est_mouvement_valide();

//  Q20
void test_tour_de_jeu();

//  Q21
void test_jouer();

//  Q22
void test_choisir_grille();


#endif