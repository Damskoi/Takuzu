#include <stdio.h>
#include <assert.h> //Il faut inclure ce fichier d'en-tête pour pouvoir utiliser la fonction assert

/***************************************************/
/*** EXEMPLE D'UTILISATION DE LA FONCTION ASSERT ***/
/***************************************************/

/* La fonction assert prend en paramètre un test. Si ce test est faux, le programme affiche un message d'erreur et s'arrête.
   Cette fonction permet lors du développement de vérifier par exemple que les valeurs des paramètres sont valides lors
   de l'appel d'une fonction.
   A titre d'exemple, comme il n'est pas possible d'effectuer une division par 0, on s'assure, à l'aide de la fonction assert
   que le diviseur est un nombre différent de 0. On supposera en effet que si l'on appelle la fonction division avec un diviseur
   nul, c'est qu'il y a un bug dans le programme.
*/



double division(int a, int b)
{
	assert(b!=0); //Si le test b!=0 est faux, alors le programme affiche un message d'erreur et s'arrête
	return (double) a / b;
}


double division2(int a, int b)
{
	/* Remarque : 
	   On peut ajouter au test : && "...". Ceci ne modifie pas le test puisque "..." est toujours considéré comme true
	   Cela permet d'afficher un message d'erreur plus explicite
	*/
	assert(b!=0 && "Problème dans la fonction division2, on essaie de diviser par 0"); 
	return (double) a / b;
}



int main()
{
	printf("%d / %d = %lf\n",4,3,division(4,3));
	
//Décommenter chacun des exemples pour voir comprendre l'intérêt de la fonction assert.
//	printf("%d / %d = %lf\n",4,0,division(4,0));
//	printf("%d / %d = %lf\n",4,0,division2(4,0));
	
	printf("Fin du programme\n");
	
	return 0;


	
}
