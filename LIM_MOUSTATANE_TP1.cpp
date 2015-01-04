#include "LIM_MOUSTATANE_Graphe.h"
/**
*
*	MAIN
*
**/

int main(int argc, char const *argv[])
{
	/* code */

	/************************/
	/**   TEST AFFICHAGE   **/
	/************************/

	
	Graphe G1; // Graphe sans circuit

	lecture_fichier(&G1);
	affiche_matrice(&G1, G1.MAdj); //affiche la matrice apres la lecture du fichier
	affiche_tabArc(&G1);  //enregistre le tableau des arcs dans un fichier
	fermeture_transitive(&G1); //affiche la matrice transitive, les etapes intermeidaires sont dans un fichier
	//rang(&G1);

	/************************/
	/**     TEST RANG      **/
	/************************/

	/*Graphe G2;
	lecture_fichier(&G2);
	affiche_matrice(&G2, G2.MAdj);
	//affiche_tabArc(&G2);
	rang(&G2);*/

	/************************/
	/**    TEST CIRCUIT    **/
	/************************/

	/**Graphe G3;
	bool c =false;
	lecture_fichier(&G3);
	affiche_matrice(&G3, G3.MAdj);
	//affiche_tabArc(&G3);
	//rang(&G3);
	fermeture_transitive(&G3);
	c = detection_circuit(&G3);

	cout<<"Graphe a circuit "<<c<<endl;**/

	return 0;
}