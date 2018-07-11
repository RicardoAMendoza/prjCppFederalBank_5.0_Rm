#include<iostream>
#include<string>
#include<fstream>
#include"structures.h"
#include"fonctions.h"
using namespace std;

/* une fonction pour le title principal */
void afficherUnTitre(char unTitre[]);
/* fonction qui return el valeur de la selection */
int afficherMenuPrincipal();

Client *creerUnClient(MaList *List);
void ajouterUnClient(MaList *List, Client *Courrant);
void afficherTouslesClients(MaList *List);
void trouverUnClient(MaList *List);
void suprimirClients(MaList *Liste);

void enregistrerClients(MaList *List);// Clients in fichier txt
void lireClients(MaList *List);// Clients  out fichier txt


/* GRACIA MAESTRO FODE, MUCHAS GRACIAS, NO ME GUSTA SU FORMA DE SER, PERO ES UN GRAN MAESTRO */

void main() {
	char unTitre[] = "federal-bank";
	afficherUnTitre(unTitre);

	int choix = 0;

	/* Allocation memoire pour almacenr lObjet dans la list */
	MaList *List = new MaList;
	/* Condition ( dInitio ) de MaList pour le premier element de la list */
	List->clientPremier = NULL;
	List->clientDernier = NULL;
	List->NbClient = 0;
	/* Client de type pointeur qui va a stoke le valeur de un outre variable  */
	Client *Courrant;

	
	do {
		choix = afficherMenuPrincipal();
		switch (choix) {
		case 1:
			/* ( 1 ) Ajouter un client / comptes */
			Courrant = creerUnClient(List);
			ajouterUnClient(List, Courrant);
			enregistrerClients(List);
		
			continue;
		case 2:
			/* ( 2 ) Trouver un client / comptes */
			trouverUnClient(List);
			continue;
		case 3:
			/* ( 3 ) Suprimir un client / comptes */
			suprimirClients(List);
			continue;
		case 4:
			/* ( 4 ) Afficher tous les clients / comptes */
			afficherTouslesClients(List);
			//lireClients(List);
			continue;
		case 5:
			/* ( 5 ) Afficher en revers tous les clients / comptes */
			afficherenReversTouslesClients(List);
			continue;
		case 6:
			cout << "\n\t Fin du programme : Hasta la vista Baby ! " << endl;
			continue;
		}
	} while (choix != 6);

	system("pause");
}