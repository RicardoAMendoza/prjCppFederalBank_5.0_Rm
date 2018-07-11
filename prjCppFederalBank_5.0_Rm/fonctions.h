#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"structures.h"
using namespace std;

/* prototipe des fonctions*/
/* REUTILISATION : une fonction pour tous le titles secondaires */
void afficherUnTitreAvecMinuscules(char mainTitre[]);
void afficherUnTitreAvecMinuscules(char titreAjouterCompte[]);
void afficherUnTitreAvecMinuscules(char comptesTitre[]);
void afficherUnTitreAvecMinuscules(char titreAjouter[]);
void afficherUnTitreAvecMinuscules(char titreClients[]);
void afficherUnTitreAvecMinuscules(char titreComptes[]);
void afficherUnTitreAvecMinuscules(char titreTrouver[]);
void afficherUnTitreAvecMinuscules(char titreClientsenReverse[]);

int afficherMenudeComptes();

Comptes *creerUnCompte();
void ajouterUneCompte(ListComptes *listdeComptes, Comptes *compteCourrant);

void afficherTouslesComptes(ListComptes *listdeComptes);
void afficherUnClient(Client *Courrant, string NumClient, string Nom, string Tel);
void afficherUneCompte(Comptes *compteCourrant, string IdComptes, string Type, float Solde);

void suprimirPremierClient(MaList *Liste);
void enregistrerComptes(ListComptes *listdeComptes);// Comptes in fichier txt
void lireComptes(MaList *List); // Comptes  out fichier txt


Client *creerUnClient(MaList *List) {
	char titreAjouter[] = "Ajouter un Client";
	afficherUnTitreAvecMinuscules(titreAjouter);

	Client *Courrant = new Client;
	Comptes *compteCourrant;
	Client *tmp = List->clientPremier;

	int autreCompte;
	bool ref = true;
	Courrant->SetComptes = new ListComptes;
	Courrant->SetComptes->NbCompte = 0;
	Courrant->SetComptes->comptesPremier = NULL;
	Courrant->SetComptes->comptesDernier = NULL;

	cout << "\n\t Nouveau Client : " << endl;
	cout << "\n\t __________________________________________ " << endl;
	cout << "\n\t Entrez le Numero de Client : "; cin >> Courrant->NumeroClient;
	cout << "\n\t Entrez le Nom de Client : "; cin >> Courrant->Nom;
	cout << "\n\t Entrez le Telephone de Client : "; cin >> Courrant->Tel;
	cout << "\n\t __________________________________________ " << endl;
	cout << endl << endl;

	
	do {
		compteCourrant = creerUnCompte();  /* appel la fonction pour creer une compte */
		compteCourrant->IdCompte = Courrant->IdClient;
		ajouterUneCompte(Courrant->SetComptes, compteCourrant);
		do {
			cout << "\n\t\t Ajouter autre compte ?  oui-> 1, non->2 : "; cin >> autreCompte;
		} while (autreCompte<1 || autreCompte>2);
		if (autreCompte == 2) {
			ref = false;
		}
	} while (ref == true);

	return Courrant;
}

/* Fonction de type Compte */
Comptes *creerUnCompte() {

	Comptes *newCont = new Comptes;
	int choix = 0;
	
	char titreAjouterCompte[] = "Ajouter une Compte";
	afficherUnTitreAvecMinuscules(titreAjouterCompte);

	cout << "\n\t\t Entrez le Numero de Compte : "; cin >> newCont->NumeroCompte;
	choix = afficherMenudeComptes();

	if (choix == 1) {
		cout << "\n\t __________________________________________ " << endl;
			cout << "\n\t COMPTE DE CREDIT : " << endl;
			newCont->Type = "Credit";
	}
	if (choix == 2) {
		cout << "\n\t __________________________________________ " << endl;
		cout << "\n\t COMPTE DE CHEQUES : " << endl;
		newCont->Type = "Cheques";
	}
	if (choix == 3) {
		cout << "\n\t __________________________________________ " << endl;
		cout << "\n\t COMPTE DE EPARGNE : " << endl;
		newCont->Type = "Epargne";
	}
	cout << "\n\t\t Entrez le Solde de Compte : "; cin >> newCont->Solde;
		
	return newCont;
}

void ajouterUnClient(MaList *List, Client *Courrant) {

	if (List->NbClient == 0) {

		Courrant->clientPresedant = NULL;
		List->clientPremier = Courrant;
		List->clientDernier = Courrant;
	}
	else {
		List->clientDernier->clientSuivant = Courrant;
		Courrant->clientPresedant = List->clientDernier;
		List->clientDernier = Courrant;
	}
	Courrant->clientSuivant = NULL;
	List->NbClient++;
	cout << "\n\t Clients dans la list : " << List->NbClient << endl;
	cout << endl << endl;
}

void ajouterUneCompte(ListComptes *listdeComptes, Comptes *compteCourrant) {

	if (listdeComptes->NbCompte == 0) {
		compteCourrant->comptesPresedant = NULL;
		// 1) La premier compte dans la liste deviens la courrant.
		listdeComptes->comptesPremier = compteCourrant;
		// 2) La dernier compte dans la liste deviens la courrant.
		listdeComptes->comptesDernier = compteCourrant;
	}
	else {
		// 1)
		listdeComptes->comptesDernier->comptesSuivant = compteCourrant;
		// 2) La compte courrant q pointea vers sa presedant pointea vers la compte dernier de la liste.
		compteCourrant->comptesPresedant = listdeComptes->comptesDernier;
		// 3) La dernier compte deviens la compte courrant.
		listdeComptes->comptesDernier = compteCourrant;
	}
	compteCourrant->comptesSuivant = NULL;
	listdeComptes->NbCompte++;
	cout << "\n\t Comptes du Client : " << listdeComptes->NbCompte << endl;
	cout << endl << endl;
}

void suprimirPremierClient(MaList *Liste) {

	// On declare un pointeur (Courrant) de type element (Client).
	Client *Courrant = NULL;

	// SI la liste est vide.
	if (Liste->clientPremier != NULL && Liste->clientDernier != NULL) {

		// 1 ) Pointeur point sus la liste.
		Courrant = Liste->clientPremier;
		//Courrant = MaListe->Dernier;
		// Incremetation, nous avon acces aux deuxieme element de la list.
		Courrant = Courrant->clientSuivant;
		//Courrant->Presedant=Courrant;
		// 2 ) Liberer le premier element.
		free(Liste->clientPremier);
		//free(MaListe->Dernier);
		// 3 ) On efectue le chainage.
		Liste->clientPremier = Courrant;
		//MaListe->Dernier = Courrant;
	}
	else
	{
		cout << "\n\t La liste est deja vide ! " << endl;
	}
}

void suprimirClients(MaList *Liste) {
	char titreSuprimir[] = "Suprimir un Client";
	afficherUnTitreAvecMinuscules(titreSuprimir);

	string suprimirClient;
	cout << "\n\t Entrez le Nombre de Client a Suprimir s.v.p => "; cin >> suprimirClient;

	Client *Presedant = NULL;
	Client *Courrant = NULL;

	if (Liste->clientPremier->clientSuivant != NULL && Liste->clientPremier->NumeroClient != suprimirClient) {
		// 1 ) Presedant doit pointer sur le premiere de la list ( le element anterior a etre efface ).
		Presedant = Liste->clientPremier;
		// 2 ) El pointeur ( Courrant ) doit pointer 
		Courrant = Presedant->clientSuivant;
		while (Courrant->NumeroClient != suprimirClient && Courrant != NULL)
		{
			Presedant = Courrant;
			Courrant = Presedant->clientSuivant;
		}
		if (Courrant != NULL) {
			Presedant->clientSuivant = Courrant->clientSuivant;
			free(Courrant);
		}
		else
		{
			cout << "\n\t Element introuvable " << endl;
		}
	}
	else
	{
		suprimirPremierClient(Liste);
	}
}


/* Fonction de type Client */
void trouverUnClient(MaList *List) {
	char titreTrouver[] = "Trouver un Client";
	afficherUnTitreAvecMinuscules(titreTrouver);

	string NbClient;
	cout << "\n\t Entrez le Nombre de Client a Chercher s.v.p => "; cin >> NbClient;

		for (Client *Courrant = List->clientPremier; Courrant != List->clientDernier->clientSuivant; Courrant = Courrant->clientSuivant) {

			if (Courrant->NumeroClient == NbClient) {

				afficherUnClient(Courrant, Courrant->NumeroClient, Courrant->Nom, Courrant->Tel);
				afficherTouslesComptes(Courrant->SetComptes);
			}
		}
	cout << endl << endl;
}

void afficherenReversTouslesClients(MaList *List) {
	char titreClientsenReverse[] = "Afficher en Reverse Tous les Clients";
	afficherUnTitreAvecMinuscules(titreClientsenReverse);

	for (Client *Courrant = List->clientDernier; Courrant != List->clientDernier->clientSuivant; Courrant = Courrant->clientPresedant) {

		afficherUnClient(Courrant, Courrant->NumeroClient, Courrant->Nom, Courrant->Tel);
		afficherTouslesComptes(Courrant->SetComptes);
	}
}

void afficherTouslesClients(MaList *List) {
		char titreClients[] = "Afficher Tous les Clients";
		afficherUnTitreAvecMinuscules(titreClients);

		Client *Courrant = List->clientPremier;
		while (Courrant!=NULL)
		{
			afficherUnClient(Courrant, Courrant->NumeroClient, Courrant->Nom, Courrant->Tel);
			afficherTouslesComptes(Courrant->SetComptes);
		
				Courrant = Courrant->clientSuivant;
		}
		cout << endl << endl;
}

void afficherTouslesComptes(ListComptes *listdeComptes) {
	char titreComptes[] = "Afficher Tous les Comptes du Client";
	afficherUnTitreAvecMinuscules(titreComptes);

	for (Comptes *compteCourrant = listdeComptes->comptesPremier; compteCourrant != listdeComptes->comptesDernier->comptesSuivant; compteCourrant = compteCourrant->comptesSuivant) {

		afficherUneCompte(compteCourrant, compteCourrant->NumeroCompte, compteCourrant->Type, compteCourrant->Solde);
	}
	cout << endl << endl;
}

void enregistrerClients(MaList *List) {

	https://openclassrooms.com/courses/lecture-et-ecriture-dans-les-fichiers-en-c
	ofstream clientFile ("Clients.txt", ios::out | ios::app);
	/*
	ecrire dans le fichier
	_____________________________________________________________
	*/
	//ofstream clientFile;
	//clientFile.open("Clients.txt");
	/*_____________________________________________________________*/

	Client *tmpC = List->clientPremier;
	if (clientFile) {
		// si le fichier est ouvert
		for (Client *tmpC = List->clientPremier; tmpC != List->clientPremier->clientSuivant; tmpC = tmpC->clientSuivant) {

			clientFile << tmpC->NumeroClient << " " << tmpC->Nom << " " << tmpC->Tel << endl;

			/*clientFile << tmpC->NumeroClient << endl;
			clientFile << tmpC->Nom << endl;
			clientFile << tmpC->Tel << endl;*/
			enregistrerComptes(tmpC->SetComptes);
		}
	}
	else // si non est ouvert
	{
		cout << "\n\t Impossible d'ouvrir le fichier !";
	}
	clientFile.close();
}

void enregistrerComptes(ListComptes *listdeComptes) {

	ofstream compteFile("Comptes.txt", ios::out | ios::app);
	/*
	ecrire dans le fichier
	___________________________________________________________
	*/
	//ofstream compteFile;
	//compteFile.open("Comptes.txt");
	/*_____________________________________________________________*/

	Comptes *tmpCpt = listdeComptes->comptesPremier;
	if (compteFile)// si le fichier est ouvert
	{
		while (tmpCpt != NULL) {
			compteFile << tmpCpt->NumeroCompte << " " << tmpCpt->Type << " " << tmpCpt->Solde<< endl;

			/*compteFile << tmpCpt->NumeroCompte << endl;
			compteFile << tmpCpt->Type << endl;
			compteFile << tmpCpt->Solde << endl;*/

			tmpCpt = tmpCpt->comptesSuivant;//on passe ou client suivant
		}
	}
	else // si non est ouvert
	{
		cout << "\n\t Error dans le ouverture de fichier ";
	}
	compteFile.close();
}

void lireClients(MaList *List) {

https://openclassrooms.com/courses/lecture-et-ecriture-dans-les-fichiers-en-c
	ifstream lireClient("Clients.txt", ios::in);

	if (lireClient)// si le fichier est ouvert
	{
		//for (Client *tmpC = MaListe->Premier; tmpC != MaListe->Dernier->Suivant; tmpC = tmpC->Suivant) { clientFile << tmpC->NumClient << " " << tmpC->Nom << " " << tmpC->Tel << endl; }
		Client *tmpClire = List->clientPremier;
		for (Client *tmpClire = List->clientPremier; tmpClire != List->clientDernier->clientSuivant; tmpClire = tmpClire->clientSuivant) {

			string ligne;
			getline(lireClient >> tmpClire->NumeroClient >> tmpClire->Nom >> tmpClire->Tel, ligne);

			/*lireClient >> tmpClire->NumeroClient;
			lireClient >> tmpClire->Nom;
			lireClient >> tmpClire->Tel;*/

		//	lireComptes(tmpClire->SetComptes);
		}
	}
	else // si non est ouvert
	{
		cerr << "\n\t Impossible d'ouvrir le fichier !";
	}
	lireClient.close();
	afficherTouslesClients(List);
	cout << endl;
}


void lireComptes(ListComptes *listdeComptes) {

https://openclassrooms.com/courses/lecture-et-ecriture-dans-les-fichiers-en-c

	ifstream lireComptes("Comptes.txt", ios::in);

	Comptes *tmpCptlire = listdeComptes->comptesPremier;

	if (lireComptes)// si le fichier est ouvert
	{
		//for (Client *tmpC = MaListe->Premier; tmpC != MaListe->Dernier->Suivant; tmpC = tmpC->Suivant) { clientFile << tmpC->NumClient << " " << tmpC->Nom << " " << tmpC->Tel << endl; }

		//for (Client *tmpClire = MaListe->Premier; tmpClire != MaListe->Dernier->Suivant; tmpClire = tmpClire->Suivant) {
		while (tmpCptlire != NULL) {

			string ligne;
			getline(lireComptes >> tmpCptlire->NumeroCompte >> tmpCptlire->Type >> tmpCptlire->Solde, ligne);

			/*lireComptes >> tmpCptlire->NumeroCompte;
			lireComptes >> tmpCptlire->Type;
			lireComptes >> tmpCptlire->Solde;*/
		}
	}
	else // si non est ouvert
	{
		cerr << "\n\t Impossible d'ouvrir le fichier !";
	}
	lireComptes.close();
	cout << endl;
}

void afficherUneCompte(Comptes *compteCourrant, string IdComptes, string Type, float Solde) {
	cout << "\n\t __________________________________________ " << endl;
	cout << "\n\t Numero de Compte : " << IdComptes << endl;
	cout << "\n\t Type de Compte : " << Type << endl;
	cout << "\n\t Solde de Compte : " << Solde << endl;
	cout << endl;
}

void afficherUnClient(Client *Courrant, string NumClient, string Nom, string Tel) {
		cout << "\n\t __________________________________________ " << endl;
		cout << "\n\t Numero de Client : " << NumClient << endl;
		cout << "\n\t Nom de Client : " << Nom << endl;
		cout << "\n\t Telephone de Client : " << Tel << endl;
		cout << endl;
}

int afficherMenuPrincipal() {
	char mainTitre[] = "Menu Principal";
	afficherUnTitreAvecMinuscules(mainTitre);
	int choix = 0;

	cout << "\n\t ( 1 ) Ajouter un client / comptes " << endl;
	cout << "\n\t ( 2 ) Trouver un client / comptes " << endl;
	cout << "\n\t ( 3 ) Suprimir un client / comptes " << endl;
	cout << "\n\t ( 4 ) Afficher tous les clients / comptes " << endl;
	cout << "\n\t ( 5 ) Afficher en revers tous les clients / comptes " << endl;
	cout << "\n\t ( 6 ) Quitter " << endl;

	cout << "\n\t Entrez votre choix ( 1 - 6 ) : "; cin >> choix;
	cout << endl << endl;

	return choix;
}

int afficherMenudeComptes() {
	
	int choix = 0;
	cout << "\n\t ( 1 ) Ajouter Compte Credit " << endl;
	cout << "\n\t ( 2 ) Ajouter Compte Cheques " << endl;
	cout << "\n\t ( 3 ) Ajouter Compte Epargne " << endl;
	cout << "\n\t Entrez votre choix ( 1 - 3 ) : "; cin >> choix;
	cout << endl << endl;

	return choix;
}

void afficherUnTitreAvecMinuscules(char unTitreAvecMinuscules[]) {
		cout << "\n\t\t\t";
		char c;
		for (int j = 0; j < strlen(unTitreAvecMinuscules); j++) {
			c = unTitreAvecMinuscules[j];
			cout << c;
		}
		cout << endl;
		cout << "\t\t\t";
		for (int j = 0; j < strlen(unTitreAvecMinuscules); j++) {
			cout << "_";
	}
	cout << endl << endl;
}

void afficherUnTitre(char unTitre[]) {
	cout << "\n\t\t\t";
	char c;
	for (int j = 0; j < strlen(unTitre); j++) {
		c = unTitre[j];
		if (islower(c)) {
			c = toupper(c);
		}
		cout << c;
	}
	cout << endl;
	cout << "\t\t\t";
	for (int j = 0; j < strlen(unTitre); j++) {
		cout << "_";
	}
	cout << endl << endl;
}