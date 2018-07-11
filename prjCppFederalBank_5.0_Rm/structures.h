#pragma once
#include<iostream>
#include<string>
using namespace std;

/* 1) Structure Comptes */
struct  Comptes{
	int IdCompte;
	string NumeroCompte;
	string Type;
	float Solde;

	Comptes *comptesSuivant;
	Comptes *comptesPresedant;
};
/* 2) Structure ListCompte */
struct  ListComptes {
	Comptes *comptesPremier;
	Comptes *comptesDernier;
	int NbCompte;
};

/* 3) Structure Client */
struct Client {
	int IdClient;
	string NumeroClient;
	string Nom;
	string Tel;
	ListComptes *SetComptes;
	Client *clientSuivant;
	Client *clientPresedant;
};
/* 4) Structure MaList */
struct  MaList{
	Client *clientPremier;
	Client *clientDernier;
	int NbClient;
};

