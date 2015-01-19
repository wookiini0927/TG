#include "LIM_MOUSTATANE_Graphe.h"

void initialisation_matrice_adj(Graphe *G){

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

void initialisation_matrice_val(Graphe *G){

	/*initialisation de la premiere dimension*/
	G->MVal = new int*[G->nbSommets];

	/*initialisation de la deuxieme dimension*/
	for (int lignes = 0; lignes<G->nbSommets;lignes++){
		G->MVal[lignes] = new int[G->nbSommets];

	}

	/*initialisation de chaque case*/
	for(int i = 0; i<G->nbSommets;i++){
		for (int j = 0; j < G->nbSommets; j++)
		{
			G->MVal[i][j] = 0;
		}
	}
}

void initialisation_rang(Graphe *G){
	G->rang = new int[G->nbSommets];

	for (int i = 0; i<G->nbSommets; i++){
		G->rang[i]= -1;
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

void initialisation_cal(Graphe *G){
	G->Cal = new int*[3];

	for(int i=0;i<3;i++){
		G->Cal[i]= new int[G->nbSommets];
	}

	for(int i = 0;i<3;i++){
		for(int j = 0;j<G->nbSommets;j++){
			if(i == 0){
				G->Cal[i][j]=j;
			}
			else{
				G->Cal[i][j]=0;
			}
		}
	}

}

void affiche_matrice_adj(const Graphe *G, bool **M){

	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		cout<<endl; //permet de revenir a la ligne des que le nombre de colonne max est atteint
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			cout<<M[lignes][colonne]<<" ";
		}
	}

	cout<<endl;
	cout<<endl;
}

void affiche_matrice_val(const Graphe *G, int **M){

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

	fichierGraphe.open("LIM-MOUSTATANE_Arc_G1.txt"); //Sauvegarde dans un fichier les traces
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
	initialisation_matrice_adj(G); //initialise la matrice MAdj;
	//initialisation_matrice(G, G->MTrans);

	initialisation_arc(G); //initialise le tableau tabArc

	sourceGraphe>>init; //recupere le premier sommet de la liste du fichier

	G->tabArc[i].extI = init; //sauvegarde dans un tableau les arcs
	//cout<<"tabArc ["<<i<<"] = "<<G->tabArc[i].extI<<endl;

	while(init !=-1){
		sourceGraphe>>term;
		sourceGraphe>>valeur;


		G->tabArc[i].extT = term;
		G->tabArc[i].val = valeur;

		G->MAdj[init][term] = true;
		i++;

		sourceGraphe>>init;
		G->tabArc[i].extI = init;

	}

	ofstream fichierGraphe;

	fichierGraphe.open("LIM-MOUSTATANE_matrice_G1.txt");
	fichierGraphe<<"Il y a "<<G->nbSommets<<" sommets.\n";
	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		fichierGraphe<<"\n";
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			fichierGraphe<<G->MAdj[lignes][colonne]<<" ";
		}
	}

	fichierGraphe<<"\n";

	fichierGraphe.close();

	affiche_tabArc(G);

}

bool detection_circuit(Graphe *G){
	cout<<"Matrice detection"<<endl;
	affiche_matrice_adj(G,G->MAdj);
	bool est_circuit = true;
	int somme = 0;
	for(int i = 0;i<G->nbSommets;i++){
		if(G->MAdj[i][i]){
			somme+=1;
		}
	}
	if(somme == 0){
		est_circuit = false;
	}
	
	return est_circuit;

}

void rang(Graphe *G){
	Graphe G_copy; //On travaille sur la copie du graphe G

	int *tabRang; //tableau de liste chainee rang pour chaque sommet
	int cmpt=0; //compteur pour avoir les degres
	int j =1;
	int tmp = 0;
	int k = 0; //iteration pour avancer jusqu'au dernier sommet

	ofstream fichierGraphe;

	fichierGraphe.open("LIM-MOUSTATANE_Rang_C1.txt"); //Sauvegarde dans un fichier les traces
	fichierGraphe<<"\n";
	
	G_copy = *G;

	tabRang = new int[G->nbSommets];

	initialisation_rang(G);

	for (int i = 0; i<G->nbSommets;i++){
		tabRang[i] = 0;
	}
	

	/** Etape 0 : initialisation des rang de chaque sommet
			On part de la matrice booleenne, on regarde le nombre de true dans la colonne (ici j) pour chaque ligne (ici i)
			on les enregistre dans un tableau (tabRang)
	**/
	for(int i = 0; i<G_copy.nbSommets; i++){
		for(int j = 0; j<G_copy.nbSommets;j++){
			if(G_copy.MAdj[j][i] == true){ 
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
		for(int i=0;i<G_copy.nbSommets; i++){
			if (tabRang[i] == 0){
				if(k == 0){
					G->rang[k] = i;
				}
				else{
					tmp = k-1;
					if(i != G->rang[tmp]){
						cout<<"racine["<<tmp<<"] : "<<G->rang[tmp]<<endl; 
						fichierGraphe<<"racine["<<tmp<<"] : "<<G->rang[tmp]<<endl; 						
						G->rang[k]=i;

					}
				}
			}
			cout<<"tabRang["<<i<<"] : "<<tabRang[i]<<endl;
			fichierGraphe<<"tabRang["<<i<<"] : "<<tabRang[i]<<endl;

		}
		cout<<endl;
		fichierGraphe<<"\n";

		/**
		* Affiche l'etat des racines
		**/
		for(int i =0; i<G_copy.nbSommets; i++){
			cout<<"racine["<<i<<"] : "<<G->rang[i]<<endl;	
			fichierGraphe<<"racine["<<i<<"] : "<<G->rang[i]<<endl;	

		}


		for(int i = 0;i<G_copy.nbSommets;i++){ //parcours toute la ligne du tableau MAdj
			if(G_copy.MAdj[G->rang[k]][i] == true){
				G_copy.MAdj[G->rang[k]][i] = false;
					tabRang[G->rang[k]]-=1;
					tabRang[i] -=1;
			}
		}

		cout<<"Apres "<<j<<"eme suppr"<<endl;
		fichierGraphe<<"Apres "<<j<<"eme suppr"<<endl;

		affiche_matrice_adj(&G_copy, G_copy.MAdj);
		j++;
		k++;

		cout<<k<<endl;
		fichierGraphe<<k<<endl;
		
	}while(tabRang[k] !=-1 && k<G_copy.nbSommets);

	for (int lignes = 0; lignes<G_copy.nbSommets; lignes++){
		fichierGraphe<<"\n";
		cout<<endl; //permet de revenir a la ligne des que le nombre de colonne max est atteint
		for(int colonne = 0; colonne<G_copy.nbSommets; colonne++){ 
			cout<<G_copy.MAdj[lignes][colonne]<<" ";
			fichierGraphe<<G_copy.MAdj[lignes][colonne]<<" ";

		}
	}

	cout<<endl;
	fichierGraphe<<"\n";
	fichierGraphe.close();
}

void calcul_rang(Graphe *G){
	if(detection_circuit(G)){
		cout<<"Il existe un circuit, on ne peut calculer le rang"<<endl;
	}
	else{
		cout<<"Il n'y a pas de circuit, on peut calculer le rang"<<endl;
		rang(G);
	}
}

/************************************/
/******    FONCTION TP2       *******/
/************************************/

void fermeture_transitive(Graphe *G){
	ofstream fichierGraphe;

	fichierGraphe.open("LIM-MOUSTATANE_fermeture_G1.txt");

	fichierGraphe<<"Matrice de transition initiale\n";
	cout<<"Matrice de transition initiale"<<endl;
	affiche_matrice_adj(G, G->MAdj);

	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		fichierGraphe<<"\n";
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			fichierGraphe<<G->MAdj[lignes][colonne]<<" ";
		}
	}

	fichierGraphe<<"\n\n";
	cout<<endl;

	//Algorithme de Warshall
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
	affiche_matrice_adj(G, G->MAdj);

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

void lecture_contrainte(Graphe *G){
	//Variable locale
	int somme;
	int nbTaches;
	int init, term, temps;

	/**
	* Lecture du fichier
	* syntaxe ifstream
	* ifstream variableFlux ("nomFichier")
	* recupere ligne par ligne va a la prochaine ligne des qu'il ya \n
	**/
	ifstream sourceGraphe ("LIM-MOUSTATANE-C01.txt");
	ofstream fichierGraphe("LIM-MOUSTATANE_Contraintes.txt");

	sourceGraphe>>nbTaches;

	G->nbSommets = nbTaches+2;

	initialisation_matrice_val(G);
	initialisation_matrice_adj(G);

	int tab[G->nbSommets];

	for(int i =0;i<G->nbSommets; i++){
		tab[i]=0;
	}

	fichierGraphe<<"On a "<<nbTaches<<" taches.\n";
	sourceGraphe>>init; //recupere le premier sommet de la liste du fichier

	cout<<"La tache "<<init<<" a pour duree ";
	fichierGraphe<<"La tache "<<init<<" a pour duree ";

	while(init !=-1){
		sourceGraphe>>temps;
		tab[init] = temps;
		cout<<temps;
		fichierGraphe<<temps;

		sourceGraphe>>term;

		if(term == -1){
			cout<<". Premiere tache a effectue"<<endl;
			fichierGraphe<<". Premiere tache a effectue.\n";
			G->MVal[0][init] = 0;
			G->MAdj[0][init] = true;

		}
		while(term != -1){
			cout<<". Ne peut s'executer avant la tache "<<term<<endl;
			fichierGraphe<<". Ne peut s'executer avant la tache "<<term<<".\n";
			G->MAdj[term][init] = true;
			sourceGraphe>>term;

		}
		
		sourceGraphe>>init; //recupere le premier sommet de la liste du fichier

		if(init !=-1){
			cout<<"La tache "<<init<<" a pour duree ";
			fichierGraphe<<"La tache "<<init<<" a pour duree ";
		}
	}

	//pour savoir quel est le sommet qui na pas de successeurs
	for(int i = 0; i<G->nbSommets-1;i++){
		somme=0;

		for(int j=0;j<G->nbSommets-1;j++){
			somme+=G->MAdj[i][j];
		}
		if(somme==0){
			G->MAdj[i][G->nbSommets-1]=true;
			G->MVal[i][G->nbSommets-1]=tab[i];
		}
	}

	//Affectation des durées, matrice a valeur
	for(int i = 0; i<G->nbSommets-1;i++){
		for(int j=0;j<G->nbSommets-1;j++){
			if(G->MAdj[i][j]==true){
				G->MVal[i][j]=tab[i];
			}
		}
	}

	fichierGraphe<<"\nMatrice booleenne"<<endl;


	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		fichierGraphe<<"\n";
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			fichierGraphe<<G->MAdj[lignes][colonne]<<" ";
		}
	}

	fichierGraphe<<"\n\nMatrice valeur"<<endl;


	for (int lignes = 0; lignes<G->nbSommets; lignes++){
		fichierGraphe<<"\n";
		for(int colonne = 0; colonne<G->nbSommets; colonne++){ 
			fichierGraphe<<G->MVal[lignes][colonne]<<" ";
		}
	}

	fichierGraphe<<"\n";

	fichierGraphe.close();

	
}

void calendrier(Graphe *G){
	cout<<"matrice"<<endl;
//	lecture_contrainte(G);
	cout<<"cal"<<endl;
	int tab_pred[2][G->nbSommets];
	int cmpt = 0;
	int sommet = -1;
	int valeur_ajout = 0;

	//initialisation
	for(int i =0;i<2;i++){
		for(int j = 0;j<G->nbSommets;j++){
			if(i==0){
				tab_pred[i][j] = j;
			}
			else{
				tab_pred[i][j]=0;
 			}
		}
	}

	//nombre de predecesseurs
	for(int i=0;i<G->nbSommets;i++){
		for(int j = 0;j<G->nbSommets;j++){
			if(G->MAdj[j][i]==true){
				cmpt++;
				tab_pred[1][i] = cmpt;
			}
		}
		cmpt=0;

	}

	//Affichage
	for(int i=0;i<2;i++){
		cout<<endl;
		for(int j=0;j<G->nbSommets;j++){
			cout<<tab_pred[i][j]<<" ";
		}
	}


	//Date au plus tot
	for(int i = 0;i<G->nbSommets;i++){
		sommet = G->rang[i];
		cout<<"sommet : "<<sommet<<endl;
		if(tab_pred[1][sommet] == 0){
			G->Cal[1][sommet] = 0;
			valeur_ajout = 0;
		}
		else if(tab_pred[1][sommet] == 1){
			if(G->MAdj[i][sommet] == 1){
				G->Cal[1][sommet] = valeur_ajout+G->MVal[i][sommet];
				valeur_ajout = G->MVal[i][sommet];
			}
		}
	}
	
	cout<<endl;
}

