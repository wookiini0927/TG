#include "LIM_MOUSTATANE_Graphe.h"

void initialisation_matrice(Graphe *G){

	/*initialisation de la premiere dimension*/
	G->MAdj = new bool*[G->nbSommets];

	/*initialisation de la deuxieme dimension*/
	for (int lignes = 0; lignes<G->nbSommets;lignes++){
		G->MAdj[lignes] = new bool[G->nbSommets];

	}

	/*initialisation de chaque case*/
	for(int i = 0; i<G->nbSommets;i++){
		for (int j = 0; j < G->nbSommets; j++)
		{
			G->MAdj[i][j] = false;
		}
	}
}

void initialisation_tableau(Graphe *G){
	G->rang = new int[G->nbSommets];

	for (int i = 0; i<G->nbSommets; i++){
		G->rang[i]= 0;
	}
}

void initialisation_arc(Graphe *G){
	/*initialisation de la premiere dimension*/
	G->tabArc = new unArc[G->nbArcs];

	/*initialisation à 0*/
	for (int i = 0; i<G->nbArcs;i++){
		G->tabArc[i].extI = 0;
		G->tabArc[i].extT = 0;
		G->tabArc[i].val = 0;
	}
}

void affiche_matrice(const Graphe *G, bool **M){

	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		cout<<endl; //permet de revenir a la ligne des que le nombre de colonne max est atteint
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			cout<<M[lignes][colonne]<<" ";
		}
	}

	cout<<endl;
	cout<<endl;
}

void affiche_tabArc(const Graphe *G){

	ofstream fichierGraphe;

	fichierGraphe.open("LIM-MOUSTATANE-resultats_G1.txt", ofstream::out|ofstream::app);
	fichierGraphe<<"\n";
	for(int i = 0; i<G->nbArcs; i++){
		//cout<<"i : "<<i<<endl;
		fichierGraphe<<"i :"<<i<<"\n";
		//cout<<"\textI : "<<G->tabArc[i].extI<<endl;
		fichierGraphe<<"\textI : "<<G->tabArc[i].extI<<"\n";
		//cout<<"\textT : "<<G->tabArc[i].extT<<endl;
		fichierGraphe<<"\textT : "<<G->tabArc[i].extT<<"\n";
		//cout<<"\tval : "<<G->tabArc[i].val<<endl;
		fichierGraphe<<"\tval : "<<G->tabArc[i].val<<"\n";

	}
	cout<<endl;

	fichierGraphe.close();

}

void affiche_tabRang(const Graphe *G,const int *tab){
	for(int i=0;i<G->nbSommets; i++){
		cout<<i<<" : "<<tab[i]<<endl;
	}
}

/************************************/
/******    FONCTION TP1       *******/
/************************************/

void lecture_fichier(Graphe *G){
	//Variable locale
	int i =0;
	int init, term, valeur;

	/**
	* Lecture du fichier
	* syntaxe ifstream
	* ifstream variableFlux ("nomFichier")
	* recupere ligne par ligne va a la prochaine ligne des qu'il ya \n
	**/
	ifstream sourceGraphe ("LIM-MOUSTATANE-G1.txt");

	sourceGraphe>>G->nbSommets;
	//cout<<G->nbSommets<<endl;
	sourceGraphe>>G->nbArcs;
	//cout<<G->nbArcs<<endl;
	initialisation_matrice(G); //initialise la matrice MAdj;
	initialisation_arc(G); //initialise le tableau tabArc

	sourceGraphe>>init; //recupere le premier sommet de la liste du fichier

	G->tabArc[i].extI = init; //sauvegarde dans un tableau les arcs
	//cout<<"tabArc ["<<i<<"] = "<<G->tabArc[i].extI<<endl;

	ofstream fichierGraphe;

	fichierGraphe.open("LIM-MOUSTATANE-resultats_G1.txt");


	while(init !=-1){
		sourceGraphe>>term;
		sourceGraphe>>valeur;


		G->tabArc[i].extT = term;
		G->tabArc[i].val = valeur;

		//cout<<"extI "<<init<<" extT "<<term<<" : "<<valeur<<endl;


		G->MAdj[init][term] = true;
		i++;

		sourceGraphe>>init;
		G->tabArc[i].extI = init;

	}

	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		fichierGraphe<<"\n";
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			fichierGraphe<<G->MAdj[lignes][colonne]<<" ";
		}
	}

	fichierGraphe<<"\n";

	fichierGraphe.close();



}

bool detection_circuit(Graphe *G){
	int i = 0;
	bool est_circuit = false; //il n'y a pas de circuit
	while(G->MAdj[i][i] != true && i<G->nbSommets){
		est_circuit = false;
		i++;
	}
	if(i<G->nbSommets){
		if(G->MAdj[i][i] == true){
			est_circuit = true;
		}
	}
	return est_circuit;

}

void rang(Graphe *G){
	Graphe *G_copy; //On travaille sur la copie du graphe G

	int *tabRang; //tableau de liste chainee rang pour chaque sommet
	int cmpt=0; //compteur pour avoir les degres
	int j =1;
	int tmp = 0;
	int k = 0; //iteration pour avancer jusqu'au dernier sommet
	int *racine; //ensemble des racines, indice correspond à k (niveau du rang) 

	G_copy = G;

	tabRang = new int[G->nbSommets];
	racine = new int[G->nbSommets];

	for (int i = 0; i<G->nbSommets;i++){
		tabRang[i] = 0;
		racine[i] = -1;
	}
	

	/** Etape 0 : initialisation des rang de chaque sommet
			On part de la matrice booleenne, on regarde le nombre de true dans la colonne (ici j) pour chaque ligne (ici i)
			on les enregistre dans un tableau (tabRang)
	**/
	for(int i = 0; i<G_copy->nbSommets; i++){
		for(int j = 0; j<G_copy->nbSommets;j++){
			if(G_copy->MAdj[j][i] == true){ 
				cmpt++;
				tabRang[i] = cmpt;
			}
		}
		cmpt=0;
	}	

	cout<<endl;
	//FIn initialisation

	do{
		//garde en memoire les sommets qui sont point d'entree
		for(int i=0;i<G_copy->nbSommets; i++){
			if (tabRang[i] == 0){
				if(k == 0){
					racine[k] = i;
				}
				else{
					tmp = k-1;
					if(i != racine[tmp]){
						cout<<"racine["<<tmp<<"] : "<<racine[tmp]<<endl; 
						racine[k] = i;

					}
				}
				//stabRang[i] = -1;
			}
			cout<<i<<" : "<<tabRang[i]<<endl;
		}

		/**
		* Affiche l'etat des racines
		**/
		for(int i =0; i<G_copy->nbSommets; i++){
			cout<<i<<": "<<racine[i]<<endl;	
		}

		for(int i = 0;i<G_copy->nbSommets;i++){ //parcours toute la ligne du tableau MAdj
			if(G_copy->MAdj[racine[k]][i] == true){
				G_copy->MAdj[racine[k]][i] = false;
					tabRang[i] -=1;
			}
		}

		cout<<"Apres "<<j<<"eme suppr"<<endl;

		affiche_matrice(G_copy, G_copy->MAdj);
		j++;
		k++;

		cout<<k<<endl;
		
	}while(tabRang[k] !=-1 && k<G_copy->nbSommets);

	affiche_matrice(G, G->MAdj);

}

/************************************/
/******    FONCTION TP2       *******/
/************************************/

void fermeture_transitive(Graphe *G){

	ofstream fichierGraphe;

	fichierGraphe.open("LIM-MOUSTATANE-resultats_fermetureG1.txt");

	fichierGraphe<<"Matrice de transition initiale\n";
	cout<<"Matrice de transition initiale"<<endl;
	affiche_matrice(G, G->MAdj);

	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		fichierGraphe<<"\n";
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			fichierGraphe<<G->MAdj[lignes][colonne]<<" ";
		}
	}
	fichierGraphe<<"\n\n";
	cout<<endl;
	cout<<endl;

	for(int i = 0; i<G->nbSommets; i++){
		fichierGraphe<<"i = "<<i<<" ";
		for(int j = 0; j<G->nbSommets; j++){
			fichierGraphe<<"j = "<<j<<" ";
			for(int k = 0; k<G->nbSommets;k++){
				fichierGraphe<<"k = "<<k<<" ";

				fichierGraphe<<"G->MAdj["<<i<<"]["<<j<<"] || (G->MAdj["<<k<<"]["<<j<<"] && G->MAdj["<<i<<"]["<<k<<"] : "<< (G->MAdj[i][j] || (G->MAdj[k][j]&& G->MAdj[i][k]))<<"\n";
				if((G->MAdj[i][j] == true || (G->MAdj[k][j]==true && G->MAdj[i][k]==true))){
					G->MAdj[i][j] = true;
				}
			}
			
		}
	}

	fichierGraphe<<"\n";

	cout<<"Matrice de transition finale"<<endl;
	affiche_matrice(G, G->MAdj);

	fichierGraphe<<"\n";
	fichierGraphe<<"Matrice fermeture transitive"<<endl;
	
	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		fichierGraphe<<"\n";
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			fichierGraphe<<G->MAdj[lignes][colonne]<<" ";
		}
	}

	fichierGraphe<<"\n";

	fichierGraphe.close();
}

