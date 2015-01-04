#include "LIM_MOUSTATANE_Graphe.h"

int main(int argc, char const *argv[])
{
	/* code */
	Graphe G1;
	lecture_fichier(&G1);
	affiche_matrice(&G1, G1.MAdj);
	fermeture_transitive(&G1);
	bool c;

	c = detection_circuit(&G1);

	cout<<"circuit :"<<c<<endl;
	return 0;
}