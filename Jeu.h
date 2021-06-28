#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;
class Jeu {
protected:
	string symboleJ1 = "1";
	string symboleJ2 = "$";
	string nomJ1 = "Joueur";
	string nomJ2 = "bot";
	int tabLastMoveJ1[2] = { 0,0 };
	int tabLastMoveJ2[2] = { 0,0 };
public:
	int taille = 0;
	Jeu();
	Jeu(int, string, string, string, string);
	~Jeu();
	void CreationTab(vector<string>&);
	void Jouer(vector<string>&, int, int,int);
	int Gagnant(vector<string>&,const int&,const int&);
	void AggrandirCarte(vector<string>&, vector<string>&, int, int);
	void botIdiot(vector<string>&,int&,int&,int&);
	void botStrategiquev2(vector<string>&, int&, int&,int&);
	void bots(vector<string>&, int&, int&,int&,int&);
};
