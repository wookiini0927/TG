#ifndef LIM_MOUSTATANE_GRAPHE_H_INCLUDED
#define LIM_MOUSTATANE_GRAPHE_H_INCLUDED

#include <iostream>
#include <fstream>

using namespace std;

/**
* Representation d'un arc
**/
typedef struct{
	int extI;
	int extT;
	int val;
}unArc;

/**
* Modele choisis : Matrice d'adjacence
**/
typedef struct{
	bool **MAdj;
	int **MVal;
	unArc *tabArc;
	int *rang;
	int nbSommets;
	int nbArcs;
}Graphe;

/**
* Initialise la matrice booleenne a false
* Param G : Graphe G
**/
void initialisation_matrice_adj(Graphe *G);

/**
* Initialise la matrice à valeur a 0
* Param G : Graphe G
**/
void initialisation_matrice_val(Graphe *G);

/**
* Initialise le tableau des rang
* Param : G : Graphe G
**/
void initialisation_tableau(Graphe *G);

/**
* Initialise le tableau d'arc à 0;
* Param G : Graphe G
**/
void initialisation_arc(Graphe *G);

/**
* Affiche la matrice adjacence booleenne du graphe
* Param G : Graphe G
**/
void affiche_matrice_adj(const Graphe *G, bool **M);

/**
* Affiche la matrice adjacence avec les valeurs du graphe
* Param G : Graphe G
**/
void affiche_matrice_val(const Graphe *G, int **M);

/**
* Enregistre dans un fichier le tableau des arcs
* Param G : Graphe G
**/
void affiche_tabArc(const Graphe *G);

/**
* Affiche le tableau du rang
* Param G : Graphe G
* Param tab : tableau d'entier
**/
void affiche_tabRang(const Graphe *G, const int *tab);


/************************************/
/******    FONCTION TP1       *******/
/************************************/

/**
* lis un fichier lu en parametre, suppose correct et lien correct
* enregistre les informations du fichier à travers un graphe
*
* Param G : Graphe G
**/
void lecture_fichier(Graphe *G);

/**
* A partir du graphe detecter s'il contient un circuit
*
* Param G : Graphe G
*
* Retourne Vrai s'il y en a un
*    sinon Faux
**/
bool detection_circuit(Graphe *G);

/**
* Calcul le rang de chaque sommet
* puis le rang après suppression
* 
* Param G : Graphe G
*
* Retourne liste des rang a chaque etape
**/
void rang(Graphe *G);

/**
* Verifie si on peut faire le calcul du rang
*
* Param G : Graphe G
*
* Si oui fait appel a rang(G);
* Sinon affiche un message d'erreur
**/
void calcul_rang(Graphe *G); 

/************************************/
/******    FONCTION TP2       *******/
/************************************/

void fermeture_transitive(Graphe *G);

void lecture_contrainte(Graphe *G);

#endif
