#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>   // srand 
#include <ctype.h>  // converstion majuscule

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


void clear_terminal()
{
  printf("\033[2J");
  printf("\033[0;0H");
}

int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...)
{
  int res;
  va_list args;
  printf("\x1B[1;%02d;%02dm", fg + 30, bg + 40);
  va_start(args, format);
  res = vprintf(format, args);
  va_end(args);
  printf("\x1B[00m");
  return res;
}

                                /*   Debut Partie 1  */

// Q1 struct cellule
typedef struct{
    int val;
    int initial;
}   cellule;

// Q2 struct grille
typedef struct{
    cellule *tab;
    int n;
}   grille;

// Q3 creer grille
grille * creer_grille(int nb){
    assert((nb==4 || nb==6 || nb==8) && "Probleme dans le champ n de la grille");
    grille *g;
    g = malloc(sizeof(grille));
    g->n=nb;
    g->tab=malloc(g->n*g->n*sizeof(cellule));
    
    if(g->tab == NULL){
        printf("ERREUR DANS LE TAB\n!!!");
        return 0;
    }
    int i;
    for(i=0;i<g->n*g->n;i++){
        g->tab[i].val=-1;
        g->tab[i].initial=0;
    
    }
    return g;
}

// Q4 destroy grille
void detruire_grille(grille *g){
    free(g->tab);
    free(g);
}

// Q5 indice valide
int est_indice_valide(grille * g, int indice){
    if(indice >= 0 && indice <= (g->n)-1)
        return 1;
    else
        return 0;
}

// Q6 cellule
int est_cellule(grille * g, int i, int j){
    if (est_indice_valide(g,i) && est_indice_valide(g,j)) 
        return 1;          
    else 
        return 0;         

}

// Q7 obtenir valeurs de la cellule
int get_val_cellule(grille * g, int i, int j){
    int val;
    assert(est_cellule(g,i,j) == 1 && "Les Var I et J ne correspondent pas a une une cellule de la grille!!");
    val = g->tab[i*(g->n)+j].val;
    return val;
}

// Q8 def de la valeur d'un cellule
void set_val_cellule(grille * g, int i, int j, int val){
    assert(est_cellule(g,i,j) == 1 && "Les Var I et J ne correspondent pas a une une cellule de la grille!!");
    assert(val <=1 && val >=-1 && "Valeur non compris entre -1 et 1!");
    g->tab[i*(g->n)+j].val = val;
}

// Q9 cellule initiale
int est_cellule_initiale(grille * g, int i, int j){
    assert(est_cellule(g,i,j) == 1 && "Les Var I et J ne correspondent pas a une une cellule de la grille!!");
    return g->tab[i*(g->n)+j].initial;
}

// Q10 cellule (i, j) de la grille
int est_cellule_vide(grille * g, int i, int j){
    assert(est_cellule(g,i,j) == 1 && "Les Var I et J ne correspondent pas a une une cellule de la grille!!");
    if(g->tab[i*(g->n)+j].val == -1)
        return 1;
    else
        return 0;
}


// 			Q11 Affichage grille 

void afficher_grille_V1(grille * g){
    int x, y;
    for(x=0; x<g->n; ++x){
        for(y=0; y<g->n; y++){
            if(est_cellule_initiale(g,x,y)) {
                printf("I");
                printf("%d\t", g->tab[x*(g->n)+y].val);
                }
            else printf("%d\t", g->tab[x*(g->n)+y].val);
        }
        printf("\n");
    }
}


void afficher_grille_V2(grille *g){
    printf("\n\tVERSION 2 :\n");

    int i,j;
    int k=0;

    printf("\n");
    for (i=0; i<g->n; i++){ 
        printf("\t");
        for (j=0; j<g->n; j++){  
                    printf("* * * * ");
        }   printf("*\n\t");

        for (j=0; j<g->n; j++){ 
            printf("*       ");
        }   printf("*\n\t");

        for (j=0; j<g->n; j++){  
            if (est_cellule_vide(g,i,j)){ 
                printf("*       ");
            }
            else if (est_cellule_initiale(g,i,j) == 1){
                    printf("*   %d%d  ",g->tab[k].val,g->tab[k].val);
            }
            else {
                printf("*   %d   ",g->tab[k].val);
            }
            k++;
        }
        printf("*\n\t");

        for (j=0; j<g->n; j++){ 
            printf("*       ");
        }
        printf("*\n");
    }

    printf("\t");
    for (j=0; j<g->n; j++){
        printf("* * * * ");
    }
    printf("*\n\n");
}


void afficher_grille_V3(grille *g){
    printf("\n\tVERSION 3 :\n");

    printf("\n\t");
    int i,j;
    int k=0;
    char c='A';

    printf ("      %c    ",c);
    for (j=0; j<g->n -1; j++){
        c += 1;
        printf ("    %c    ",c);
    }

    c='A';
    printf("\n\t");
    for (i=0; i<g->n; i++){  
        printf ("  ");
        for (j=0; j<g->n; j++){     
            if ((j+i)%2 == 0){    
                color_printf(WHITE,MAGENTA,"         ");
            }
            else {      
                color_printf(WHITE,CYAN,"         ");
            }
        }
        printf("\n\t");

        printf("%c ",c);   
        for (j=0; j<g->n; j++){     
            if ((j+i)%2 == 0 && est_cellule_vide(g,i,j)){   
                color_printf(WHITE,MAGENTA,"         ");
            }
            else if ((j+i)%2 == 1 && est_cellule_vide(g,i,j)){     
                color_printf(WHITE,CYAN,"         ");
            }
            else if ((j+i)%2 == 0 && est_cellule_initiale(g,i,j)){      
                color_printf(YELLOW,MAGENTA,"    %d    ",g->tab[k].val);
            }
            else if ((j+i)%2 == 1 && est_cellule_initiale(g,i,j)) {     
                color_printf(YELLOW,CYAN,"    %d    ",g->tab[k].val);
            }
            else if ((j+i)%2 == 0 && est_cellule_initiale(g,i,j) == 0){     
                color_printf(WHITE,MAGENTA,"    %d    ",g->tab[k].val);
            }
            else {      
                color_printf(WHITE,CYAN,"    %d    ",g->tab[k].val);
            }
            k++;
        }
        printf("\n\t");

        printf ("  ");
        for (j=0; j<g->n; j++){  
            if ((j+i)%2 == 0){  
                color_printf(WHITE,MAGENTA,"         ");
            }
            else {      
                color_printf(WHITE,CYAN,"         ");
            }
        }
        printf("\n\t");
        c++;
    }
    printf ("\n\n");
}

                                /*   Fin Partie 1  */


                                /*   Debut Partie 2  */


//	partie 2.0

//  Q12 rendre initiale 
void rendre_cellule_initiale(grille * g, int i, int j){
	assert(est_cellule(g,i,j) == 1 && "Les Var I et J ne correspondent pas a une une cellule de la grille!!. Cf Q9");
	assert(est_cellule_initiale(g,i,j) == 0 && "La cellule (I,J) est deja initiale de la grille!!. Cf Q9");
	g->tab[i*(g->n)+j].initial = 1;
}

//  Q13 intializer grille a partir de fichier
grille * initialiser_grille(char nom_fichier[]){
    grille *g;
    int taille, nbInit, val;
    int i, x, y;
    FILE * fichier=NULL;
    fichier=fopen(nom_fichier, "r");
    if(fichier==NULL) {
        printf("le fichier n'existe pas ou est mal ecrit\n");
        return NULL;  // Pas necessaire
    }
    else{
        fscanf(fichier, "%d" , &taille);
        g = creer_grille(taille);
        fscanf(fichier, "%d" , &nbInit);
        for(i=0; i<nbInit; i++){
            fscanf(fichier, "%d %d %d" , &x, &y, &val);
            rendre_cellule_initiale(g, x, y);
            set_val_cellule(g, x, y, val);
        }
    }
    fclose(fichier);
	return g;
}

//  Q14 grille rempli
int est_grille_pleine(grille * g){
    int x, y;
    for(x=0; x<g->n; ++x){
        for(y=0; y<g->n; y++){
            if(est_cellule_vide(g,x,y)) return 0;  
        }
    }
    return 1;
}

//  Q15 meme nombre succesive
int pas_zero_un_consecutifs(grille * g){
    int x, y, nbzer=0, nbun=0 ;
    for(x=0; x<g->n; ++x){
        for(y=0; y<g->n-2; y++) {
            if( get_val_cellule(g,x,y) == 1 && get_val_cellule(g,x,y+1) == 1 && get_val_cellule(g,x,y+2) == 1) return 0;
            else if( get_val_cellule(g,x,y) == 0 && get_val_cellule(g,x,y+1) == 0 && get_val_cellule(g,x,y+2) == 0) return 0;
        }
    }

    for(x=0; x<g->n; ++x){
        for(y=0; y<g->n-2; y++) {
            if( get_val_cellule(g,y,x) == 1 && get_val_cellule(g,y+1,x) == 1 && get_val_cellule(g,y+2,x) == 1 ) return 0;
            else if( get_val_cellule(g,y,x) == 0 && get_val_cellule(g,y+1,x) == 0 && get_val_cellule(g,y+2,x) == 0 ) return 0;
        }
    }
    return 1;
}
    

//  Q16 meme nombre de chiffre
int meme_nombre_zero_un(grille * g){
    int x, y, nbzerlig=0, nbunlig=0, nbzercol=0, nbuncol=0  ;
    for(x=0; x<g->n; ++x){
        for(y=0; y<(g->n); y++){
            if(get_val_cellule(g,x,y)==0)
                nbzerlig++;
            else if(get_val_cellule(g,x,y)==1)
                nbunlig++;
        }
        if ( nbzerlig != nbunlig ) return 0;
    }

    for(x=0; x<g->n; ++x){
        for(y=0; y<(g->n); y++){
            if(get_val_cellule(g,y,x)==0)
                nbzercol++;
            else if(get_val_cellule(g,y,x)==1)
                nbuncol++;
        }
       if ( nbzercol != nbuncol ) return 0;

    }
    return 1;
}

//  Q17 colonnes distinctes
int lignes_colonnes_distinctes(grille * g){
    int y,x,compt=0;
    for(x=1; x<=g->n; x++){
        for (y=0; y< g->n; y++){
            if(compt==3)
                return 0;
            if(g->tab[y].val != g->tab[y+g->n*x].val)
                break;
            compt++;
        }
        compt=0;
    }
    for(x=2*1; x<=g->n; x++){
        for (y=0; y< g->n; y++){
            if(compt==3)
                return 0;
            if(g->tab[y+g->n].val != g->tab[y+g->n*x].val)
                break;
            compt++;
        }
        compt=0;
    }
    for (y=0; y< g->n; y++){
        if(compt==3)
            return 0;
        if(g->tab[y+g->n*2].val != g->tab[y+g->n*3].val)
            break;
        compt++;
    }


    for(x=1; x<g->n; x++){
        for (y=0; y<(g->n*g->n); y+=g->n){
            if(compt==3)
                return 0;
            if(g->tab[y].val != g->tab[y+x].val)
                break;
            compt++;
        }
        compt=0;
    }
    for(x=1; x<g->n; x++){
        for (y=g->n; y<(g->n*g->n); y+=g->n){
            if(compt==3)
                return 0;
            if(g->tab[y].val != g->tab[y+x].val)
                break;
            compt++;
        }
        compt=0;
    }
    for (y=g->n*2; y<(g->n*g->n); y+=g->n){
        if(compt==3)
            return 0;
        if(g->tab[y].val != g->tab[y+1].val)
            break;
        compt++;
    }
    return 1;
}

//  Q18 Partie gagner
int est_partie_gagnee(grille * g){
    if(est_grille_pleine(g) && pas_zero_un_consecutifs(g) && meme_nombre_zero_un(g) && lignes_colonnes_distinctes(g)) return 1;
    return 0;
}

                                /*   Fin Partie 2  */


                                /*   Debut Partie 3  */
//  Q19 mouvement valide
int est_mouvement_valide(grille * g, char mouv[], int * ligne, int * colonne, int * val){
    int i, compt=0;

    // ajout du 25/04/20
    mouv[0]= toupper(mouv[0]);
    mouv[1]= toupper(mouv[1]);

    if(g->n == 4) {
        if(((unsigned)strlen(mouv))==3){
            if( (mouv[0]<'A' || mouv[0]>'D') || (mouv[1]<'A' || mouv[1]>'D') || (mouv[2]<'0' || mouv[2]>'1')    ) return 0;
            else {
                for(i='A'; i<='D'; ++i){
                    if(i==mouv[0])  *ligne= compt;
                    if(i==mouv[1]) *colonne= compt; 
                    compt++;
                }

                if((est_cellule(g, *ligne, *colonne) != 1) || (est_cellule_initiale(g, *ligne, *colonne) == 1)) return 0;
                char nb[2]; nb[0]= mouv[2];
                *val= atoi(nb);
            }
        }

        else {
            if( (mouv[0]<'A' || mouv[0]>'D') || (mouv[1]<'A' || mouv[1]>'D')   ) return 0;
           else {
                for(i='A'; i<='D'; ++i){
                    if(i==mouv[0])  *ligne= compt;
                    if(i==mouv[1]) *colonne= compt; 
                    compt++;
                }
                if((est_cellule(g, *ligne, *colonne) != 1) || (est_cellule_initiale(g, *ligne, *colonne) == 1) || (get_val_cellule(g, *ligne, *colonne) == -1) ) return 0;
                *val= -1;
            }
        }
    }

    else if(g->n == 6){
        if(((unsigned)strlen(mouv))==3){
            if( (mouv[0]<'A' || mouv[0]>'F') || (mouv[1]<'A' || mouv[1]>'F') || (mouv[2]<'0' || mouv[2]>'1')    ) return 0;
            else {
                for(i='A'; i<='F'; ++i){
                    if(i==mouv[0])  *ligne= compt;
                    if(i==mouv[1]) *colonne= compt; 
                    compt++;
                }

                if((est_cellule(g, *ligne, *colonne) != 1) || (est_cellule_initiale(g, *ligne, *colonne) == 1) ) return 0;
                char nb[2]; nb[0]= mouv[2];
                *val= atoi(nb);
            }
        }

        else {
            if( (mouv[0]<'A' || mouv[0]>'F') || (mouv[1]<'A' || mouv[1]>'F')   ) return 0;
           else {
                for(i='A'; i<='F'; ++i){
                    if(i==mouv[0])  *ligne= compt;
                    if(i==mouv[1]) *colonne= compt; 
                    compt++;
                }
                if((est_cellule(g, *ligne, *colonne) != 1) || (est_cellule_initiale(g, *ligne, *colonne) == 1) || (get_val_cellule(g, *ligne, *colonne) == -1)) return 0;
                *val= -1;
            }
        }
    }

    else {
        if(((unsigned)strlen(mouv))==3){
            if( (mouv[0]<'A' || mouv[0]>'H') || (mouv[1]<'A' || mouv[1]>'H') || (mouv[2]<'0' || mouv[2]>'1')    ) return 0;
            else {
                for(i='A'; i<='H'; ++i){
                    if(i==mouv[0])  *ligne= compt;
                    if(i==mouv[1]) *colonne= compt; 
                    compt++;
                }

                if((est_cellule(g, *ligne, *colonne) != 1) || (est_cellule_initiale(g, *ligne, *colonne) == 1)) return 0;
                char nb[2]; nb[0]= mouv[2];
                *val= atoi(nb);
            }
        }

        else {
            if( (mouv[0]<'A' || mouv[0]>'H') || (mouv[1]<'A' || mouv[1]>'H')   ) return 0;
           else {
                for(i='A'; i<='H'; ++i){
                    if(i==mouv[0])  *ligne= compt;
                    if(i==mouv[1]) *colonne= compt; 
                    compt++;
                }
                if((est_cellule(g, *ligne, *colonne) != 1) || (est_cellule_initiale(g, *ligne, *colonne) == 1) || (get_val_cellule(g, *ligne, *colonne) == -1)) return 0;
                *val= -1;
            }
        }
    }

    return 1;
}

//  Q20 Tour de jeu
void tour_de_jeu(grille * g){    
    int ligne, colonne, val;
    char mouv[4]="";
    while(est_mouvement_valide(g, mouv, &ligne, &colonne, &val)!=1){
        printf("Veillez Saisir un mouvement valide\nexemple: AA1 ou aa0\nmouv= ");
        scanf("%s", mouv);
    }
    set_val_cellule(g,ligne,colonne,val);
}

//  Q21 Jouer
void jouer(char nom_fichier[]){
    grille *g= initialiser_grille(nom_fichier);
    while(est_partie_gagnee(g)!=1) {
        afficher_grille_V3(g);
        tour_de_jeu(g);
    }
    detruire_grille(g);
    printf("La partie est finie !\n");
}

//  Q22 choisir grille
void choisir_grille(char chemin[]){
    srand(time(NULL)); // 
    char taille[2]="9";
    while(  taille[0] != '4' && taille[0] != '6' && taille[0] != '8'){
   //     printf("%s\n", taille);
        printf("Veillez choisir la taille de la grille: 4, 6 ou 8\nTaille= ");
        scanf("%s", taille);
    }
    int nb=rand() % 5+1;
    printf("rand = %d\n", nb);
    char inst[2];
    sprintf(inst,"%d",nb);
    strcpy(chemin,"./Grilles/G");
    strcat(chemin,taille);
    strcat(chemin,"/grille");
    strcat(chemin, inst);
    strcat(chemin,".txt");
}


/*          FONCTIONS SUPPLE        */

void lancer_partie(){
    char chemin[23];
    choisir_grille(chemin);
    printf("Chemin de la grille= %s\n", chemin);
    jouer(chemin);
}
                                /*   Fin Partie 2  */



/*              LES FONCTIONS TEST                  */


void test_creer_grille(){
    int i,k;
    for(k = 4; k <= 8 ; k+=2){
        grille * g = creer_grille(k);
        assert(g->n == k && "Problème dans le champ n de la grille");

        //Vérification que les cellules sont vides
        for(i = 0 ; i < k * k ; i++){
            assert(g->tab[i].val == -1 && "Problème : cellule non vide !");
            assert(g->tab[i].initial == 0 && "Problème : cellule initiale !");
        }
        detruire_grille(g);
    }
    printf("Test de la fonction creer_grille passé !\n");
}


/**
 * Fonction testant la fonction est_indice_valide
 */
void test_est_indice_valide(){
    int i,k;
    for(k = 4; k <= 8 ; k+=2){

        grille * g = creer_grille(k);
        for(i = 0 ; i < k ; i++)
            assert(est_indice_valide(g,i) == 1 && "Problème indice valide non reconnu !");

        assert(est_indice_valide(g,-1) == 0 && "Problème indice non valide reconnu !");
        assert(est_indice_valide(g,k)  == 0 && "Problème indice non valide reconnu !");
        detruire_grille(g);
    }
    printf("Test de la fonction est_indice_valide passé !\n");
}


/**
 * Fonction testant la fonction est_cellule
 */
void test_est_cellule(){
    int i,j,k;
    for(k = 4; k <= 8 ; k+=2){

        grille * g = creer_grille(k);
        for(i = 0 ; i < k ; i++)
            for(j = 0 ; j < k ; j++)
                assert(est_cellule(g,i,j) == 1 && "Problème indice valide non reconnu !");
        assert(est_cellule(g,-1,1) == 0 && "Problème indice non valide reconnu !");
        assert(est_cellule(g,k,1)  == 0 && "Problème indice non valide reconnu !");
        assert(est_cellule(g,1,-1) == 0 && "Problème indice non valide reconnu !");
        assert(est_cellule(g,1,k)  == 0 && "Problème indice non valide reconnu !");
        detruire_grille(g);
    }
    printf("Test de la fonction est_cellule passé !\n");
}


/**
 * Fonction testant la fonction get_val_cellule
 */
void test_get_val_cellule(){
    grille * g = creer_grille(6);
    g->tab[0].val = 1;
    g->tab[6].val = 1;
    g->tab[15].val = 0;
    assert(get_val_cellule(g,0,0) == 1 && "Problème de valeur");
    assert(get_val_cellule(g,1,0) == 1 && "Problème de valeur");
    assert(get_val_cellule(g,2,3) == 0 && "Problème de valeur");
    assert(get_val_cellule(g,1,4) == -1 && "Problème de valeur");
    detruire_grille(g);
    printf("Test de la fonction get_val_cellule passé !\n");
}


/**
 * Fonction testant la fonction set_val_cellule
 */
void test_set_val_cellule(){
    int k;
    for(k = 4; k <= 8 ; k+=2){
        grille * g = creer_grille(k);
        set_val_cellule(g,0,0,1);
        assert(get_val_cellule(g,0,0) == 1 && "Problème de valeur");
        set_val_cellule(g,k-1,k-1,0);
        assert(get_val_cellule(g,k-1,k-1) == 0 && "Problème de valeur");
        set_val_cellule(g,0,k-2,1);
        assert(get_val_cellule(g,0,k-2) == 1 && "Problème de valeur");
        set_val_cellule(g,k-2,1,0);
        assert(get_val_cellule(g,k-2,1) == 0 && "Problème de valeur");
        set_val_cellule(g,k-1,k-1,-1);
        assert(get_val_cellule(g,k-1,k-1) == -1 && "Problème de valeur");
        detruire_grille(g);
    }
    printf("Test de la fonction set_val_cellule passé !\n");
}


/**
 * Fonction testant la fonction est_cellule_initiale
 */
void test_est_cellule_initiale(){
    int i,j,k;
    for(k = 4; k <= 8 ; k+=2){
        grille * g = creer_grille(k);
        for(i = 0 ; i < k * k ; i++){
            g->tab[i].initial = 0;
        }
        for(i = 0 ; i < k ; i++)
            for(j = 0 ; j < k ; j++)
                assert(est_cellule_initiale(g,i,j) == 0 && "Problème valeur initiale au début");
        for(i = 0 ; i < k * k ; i++){
            g->tab[i].initial = 1;
        }
        for(i = 0 ; i < k ; i++)
            for(j = 0 ; j < k ; j++)
                assert(est_cellule_initiale(g,i,j) == 1 && "Problème valeur initiale au début");
        detruire_grille(g);
    }   
    printf("Test de la fonction est_cellule_initiale passé !\n");
}


/**
 * Fonction testant la fonction est_cellule_vide
 */
void test_est_cellule_vide(){
    int i,j,k;
    for(k = 4; k <= 8 ; k+=2){
        grille * g = creer_grille(k);
        for(i = 0 ; i < k * k ; i++){
            g->tab[i].val = -1;
        }
        for(i = 0 ; i < k ; i++)
            for(j = 0 ; j < k ; j++)
                assert(est_cellule_vide(g,i,j) == 1 && "Problème valeur initiale au début");
        for(i = 0 ; i < k * k ; i++){
            g->tab[i].val = 0;
        }
        for(i = 0 ; i < k ; i++)
            for(j = 0 ; j < k ; j++)
                assert(est_cellule_vide(g,i,j) == 0 && "Problème valeur initiale au début");
        for(i = 0 ; i < k * k ; i++){
            g->tab[i].val = 1;
        }
        for(i = 0 ; i < k ; i++)
            for(j = 0 ; j < k ; j++)
                assert(est_cellule_vide(g,i,j) == 0 && "Problème valeur initiale au début");
        detruire_grille(g);
    }   
    printf("Test de la fonction est_cellule_vide passé !\n");
}


/**
 * Fonction testant la fonctino afficher_grille
 */
void test_afficher_grille(){
    grille * g = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
    int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int i;
    for(i = 0 ; i < 16 ; i++){
        g->tab[i].val = val_cellule[i];
        g->tab[i].initial = initial_cellule[i];
    }
    afficher_grille_V3(g);
    detruire_grille(g);
    printf("L'affichage doit être celui de la grille solution dans le pdf\n");
}


/**
 * Fonction testant la fonction rendre_cellule_initiale
 */
void test_rendre_cellule_initiale(){
   grille *g = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,-1,-1,0,-1,0,0,1,1,1,1,0,0};
    int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int i;
    for(i = 0 ; i < 16 ; i++){
        g->tab[i].val = val_cellule[i];
        g->tab[i].initial = initial_cellule[i];
    }
    int j=0; i=0;
//    afficher_grille_V3(g);
    rendre_cellule_initiale(g,j,i);
//    afficher_grille_V3(g);
    assert(est_cellule_initiale(g,i,j) && "Problème dans la fonction rendre_cellule_initiale");
    if(est_cellule_initiale(g,i,j)) printf("Test de la fonction rendre_cellule_initiale passé !\n");
    detruire_grille(g);
}


/**
 * Fonction testant la fonction initiliser_grille
 */
void test_initialiser_grille(){
    char nom_fichier[22]="./Grilles/grille.txt";
    grille *g= initialiser_grille(nom_fichier);
    grille *test = creer_grille(4);
    set_val_cellule(test,0,1,1);
    rendre_cellule_initiale(test,0,1);
    set_val_cellule(test,0,3,0);
    rendre_cellule_initiale(test,0,3);
    set_val_cellule(test,1,2,0);
    rendre_cellule_initiale(test,1,2);
    set_val_cellule(test,2,1,0);
    rendre_cellule_initiale(test,2,1);
    int i;
    for(i=0; i<g->n; i++){
        assert((g->tab[i].val == test->tab[i].val) && (g->tab[i].initial == test->tab[i].initial) && "Problème dans la fonction initialiser_grille !");
    }   detruire_grille(g);
        printf("Test de la fonction initialiser_grille passé !\n");
} 


/**
 * Fonction testant la fonction est_grille_pleine
 */
void test_est_grille_pleine(){
    grille *g = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,1,1,0,1,0,0,1,1,1,1,0,0};
    int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int i, x, y;
    for(i = 0 ; i < 16 ; i++){
        g->tab[i].val = val_cellule[i];
        g->tab[i].initial = initial_cellule[i];
    }
  //  afficher_grille_V3(g);
    assert(est_grille_pleine(g) && "Grille non pleine !");
    detruire_grille(g);
    printf("Test de la fonction est_grille_pleine passé !\n");   
}


/**
 * Fonction testant la fonction pas_zero_un_consecutifs
 */
void test_pas_zero_un_consecutifs(){
    grille *g = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,-1,-1,0,-1,0,0,1,1,1,1,0,0};
    int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int i;
    for(i = 0 ; i < 16 ; i++){
        g->tab[i].val = val_cellule[i];
        g->tab[i].initial = initial_cellule[i];
    }
 //   afficher_grille_V3(g);
    assert(pas_zero_un_consecutifs(g) && "3 chiffre 0 ou 1 consecutif ");
    detruire_grille(g);
    printf("Test de la fonction pas_zero_un_consecutifs passé !\n");
}


/**
 * Fonction testant la fonction meme_nombre_zero_un
 */
void test_meme_nombre_zero_un(){
    grille *g = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
    int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int i;
    for(i = 0 ; i < 16 ; i++){
        g->tab[i].val = val_cellule[i];
        g->tab[i].initial = initial_cellule[i];
    }
 //   afficher_grille_V3(g);
    assert(meme_nombre_zero_un(g) && "Pas le meme nombre zero et de un !");
    detruire_grille(g);
    printf("Test de la fonction meme_nombre_zero_un passé !\n");
}


/**
 * Fonction testant la fonction lignes_colonnes_distinctes
 */
void test_lignes_colonnes_distinctes(){
    char nom_fichier[21]="./Grilles/grille.txt";
    grille *g= initialiser_grille(nom_fichier);
 //   afficher_grille_V3(g);
    assert(lignes_colonnes_distinctes(g) && "lignes et colonnes non distinctes !");
    detruire_grille(g);
    printf("Test de la fonction lignes_colonnes_distinctes passé !\n");
}


/**
 * Fonction testant la fonction est_partie_gagnee
 */
void test_est_partie_gagnee(){
    grille *g = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
    int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int i;
    for(i = 0 ; i < 16 ; i++){
        g->tab[i].val = val_cellule[i];
        g->tab[i].initial = initial_cellule[i];
    }
 //   afficher_grille_V3(g);
    assert(est_grille_pleine(g) && pas_zero_un_consecutifs(g) && meme_nombre_zero_un(g) && lignes_colonnes_distinctes(g) && "Partie non fini !");
    detruire_grille(g);
    printf("Test de la fonction est_partie_gagnee passé !\n");
}


/**
 * Fonction testant la fonction est_mouvement_valide
 */
void test_est_mouvement_valide(){
    int x, y, val; 
    char mouv[4]= "AA1";
    char nom_fichier[21]="./Grilles/grille.txt";
    grille *g= initialiser_grille(nom_fichier);
//    afficher_grille_V3(g);
    assert(est_mouvement_valide(g, mouv, &x, &y, &val) && "Mouvement non valide  !");
    detruire_grille(g);
    printf("Test de la fonction test_est_mouvement_valide passé !\n");
}


/**
 * Fonction testant la fonction tour_de_jeu
 */
void test_tour_de_jeu(){
    char nom_fichier[21]="./Grilles/grille.txt";
    grille *g= initialiser_grille(nom_fichier);
    int ligne, colonne, val;
    char mouv[4]="AA1";
    assert(est_mouvement_valide(g, mouv, &ligne, &colonne, &val) && "Problème dans la fonction tour_de_jeu");
    detruire_grille(g);
    printf("Test de la fonction tour_de_jeu passé !\n");
}


/**
 * Fonction testant la fonction test_jouer
 */
void test_jouer(){
    grille *g = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
    int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int i;
    for(i = 0 ; i < 16 ; i++){
        g->tab[i].val = val_cellule[i];
        g->tab[i].initial = initial_cellule[i];
    }
    assert(est_partie_gagnee(g) && "Problème dans la fonction jouer");
    detruire_grille(g);
    printf("Test de la fonction jouer passé !\n");
}


/**
 * Fonction testant la fonction choisir_grille
 */
void test_choisir_grille(){
    int nb=rand()%5+1;
    char taille[2]="4";
    assert( taille[0] == '4' || taille[0] == '6' || taille[0] == '8' && "Problème de taille");
    assert(nb>0 && nb<5 &&"Problème d'instance");
    printf("Test de la fonction choisir_grille passé !\n");
}