#include <SFML/Graphics.hpp>
#include <iostream>
#include <numeric>//pour accumulate
#include <algorithm>
#include <set>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "Jeu.h"
#include<Windows.h>
#include <locale>
using namespace std;
//Modifier bot


Jeu::Jeu()
{
}

Jeu::Jeu(int X, string Joueur1, string Joueur2, string nom1, string nom2)
{
	taille = X;
	symboleJ1 = Joueur1;
	symboleJ2 = Joueur2;
	nomJ1 = nom1;
	nomJ2 = nom2;
}



Jeu::~Jeu()
{
}
//Permet de remplir le tableau selon le joueur qui est en train de jouer
void Jeu::Jouer(vector<string>& tab, int x, int y, int j) {
	if (j == 1) {
		tab[(x - 1) + (y - 1) * taille] = symboleJ1;
		tabLastMoveJ1[0] = x;
		tabLastMoveJ1[1] = y;
	}
	if (j == 2) {
		tab[(x - 1) + (y - 1) * taille] = symboleJ2;
		tabLastMoveJ2[0] = x;
		tabLastMoveJ2[1] = y;
	}
	if (j != 2 && j != 1) {
		cout << "Erreur";
	}
}

//Creation tableau
void Jeu::CreationTab(vector<string>& tab) {
	if (!tab.empty()) {
		tab.clear();//Si le vecteur est rempli on le vide
	}
	tab.assign(taille*taille, " ");
	return;
}

void Jeu::AggrandirCarte(vector<string>& tab, vector<string>& tab2, int taille, int newtaille) {
	int compteur = 0;
	int compteur2 = 1;
	for (int i = 0; i < taille * taille; i ++) {
		compteur++;
		if (compteur > taille) {
			compteur = 1;
			compteur2++;
		}
		if (tab[i] == symboleJ1) {
			tab2[compteur - 1 + (compteur2 - 1) * newtaille] = symboleJ1;
		}
		if (tab[i] == symboleJ2) {
			tab2[compteur - 1 + (compteur2 - 1) * newtaille] = symboleJ2;
		}
	}
	return;
}

int Jeu::Gagnant(vector<string>& tab, const int& x, const int& y) {
	int compteurJ1 = 0;
	int compteurJ2 = 0;
	//vérification horizontale
	for (int i = -4; i <= 4; ++i) {
		if (x + i > 0 && x + i <= taille) {
			if (tab[(x - 1+i) + (y - 1) * taille] == symboleJ1) {
				compteurJ1++;
			}
			else if(compteurJ1<5){
				compteurJ1 = 0;
			}
			if (tab[(x - 1 + i) + (y - 1) * taille] == symboleJ2) {
				compteurJ2++;
			}
			else if (compteurJ2 < 5) {
				compteurJ2 = 0;
			}
		}
		else if (compteurJ1 < 5 && compteurJ2<5) {
			compteurJ1 = 0;
			compteurJ2 = 0;
		}
	}
	if (compteurJ1 >= 5) {
		return 1;
	}
	else if(compteurJ2 >= 5) {
		return 2;
	}
	compteurJ1 = 0;
	compteurJ2 = 0;
	//vérification verticale
	for (int i = -4; i <= 4; ++i) {
		if (y + i > 0 && y+ i <= taille) {
			if (tab[(x - 1 ) + (y - 1 + i) * taille] ==symboleJ1) {
				compteurJ1++;
			}
			else if(compteurJ1<5){
				compteurJ1 = 0;
			}
			if ((tab[(x - 1 ) + (y - 1 + i) * taille] == symboleJ2) ){
				compteurJ2++;
			}
			else if (compteurJ2 < 5) {
				compteurJ2 = 0;
			}
		}
		else if (compteurJ1 < 5 && compteurJ2<5) {
			compteurJ1 = 0;
			compteurJ2 = 0;
		}
	}
	if (compteurJ1 >= 5) {
		return 1;
	}
	else if(compteurJ2 >= 5) {
		return 2;
	}
	compteurJ1 = 0;
	compteurJ2 = 0;
	//vérification gauche haut à droite bas
	for (int i = -4; i <= 4; ++i) {
		if (y + i > 0 && y + i <= taille && x + i > 0 && x + i <= taille) {
			if (tab[(x - 1 + i) + (y - 1 + i) * taille] == symboleJ1) {
				compteurJ1++;
			}
			else if (compteurJ1 < 5) {
				compteurJ1 = 0;
			}
			if ((tab[(x - 1 + i) + (y - 1 + i) * taille] == symboleJ2)) {
				compteurJ2++;
			}
			else if (compteurJ2 < 5) {
				compteurJ2 = 0;
			}
		}
		else if (compteurJ1 < 5 && compteurJ2 < 5) {
			compteurJ1 = 0;
			compteurJ2 = 0;
		}
	}
	if (compteurJ1 >= 5) {
		return 1;
	}
	else if (compteurJ2 >= 5) {
		return 2;
	}
	compteurJ1 = 0;
	compteurJ2 = 0;
	//vérification gauche bas à droite haut
	for (int i = -4; i <= 4; ++i) {
		if (y - i > 0 && y - i <= taille && x + i > 0 && x + i <= taille) {
			if (tab[(x - 1 + i) + (y - 1 - i) * taille] == symboleJ1) {
				compteurJ1++;
			}
			else if (compteurJ1 < 5) {
				compteurJ1 = 0;
			}
			if ((tab[(x - 1 + i) + (y - 1 - i) * taille] == symboleJ2)) {
				compteurJ2++;
			}
			else if (compteurJ2 < 5) {
				compteurJ2 = 0;
			}
		}
		else if (compteurJ1 < 5 && compteurJ2 < 5) {
			compteurJ1 = 0;
			compteurJ2 = 0;
		}
	}
	if (compteurJ1 >= 5) {
		return 1;
	}
	else if (compteurJ2 >= 5) {
		return 2;
	}
	for (int i = 0; i < taille * taille; i++) {
		if (tab[i] != symboleJ1 && tab[i] != symboleJ2) {
			return 0;
		}
	}
	return 4;
}

//Bot aléatoire et/ou basique
void Jeu::botIdiot(vector<string>& tab, int& x, int& y,int& mdj) {
	srand((unsigned int)(time(NULL))); // initialisation de rand
	int x2 = 1;
	int y2 = 1;
	if (mdj == 2) {
		for (unsigned int i = 0; i < tab.size(); i++) {//rajouter unsigned
			if (tab[(x2 - 1) + (y2 - 1) * taille] != symboleJ1 && tab[(x2 - 1) + (y2 - 1) * taille] != symboleJ2) {
				if (x2 < taille && x2>1 && y2 > 1 && x2 < taille) {
					if (tab[(x2 - 2) + (y2 - 2) * taille] == symboleJ1 || tab[(x2 - 2) + (y2 - 2) * taille] == symboleJ2 || tab[(x2 - 1) + (y2 - 2) * taille] == symboleJ1 || tab[(x2 - 1) + (y2 - 2) * taille] == symboleJ2 || tab[(x2 - 2) + (y2 - 1) * taille] == symboleJ1 || tab[(x2 - 2) + (y2 - 1) * taille] == symboleJ2 || tab[(x2)+(y2)*taille] == symboleJ1 || tab[(x2)+(y2)*taille] == symboleJ2 || tab[(x2 - 2) + (y2)*taille] == symboleJ1 || tab[(x2 - 2) + (y2)*taille] == symboleJ2 || tab[(x2 - 1) + (y2 - 2) * taille] == symboleJ1 || tab[(x2 - 1) + (y2 - 2) * taille] == symboleJ2 || tab[(x2)+(y2 - 2) * taille] == symboleJ1 || tab[(x2)+(y2 - 2) * taille] == symboleJ2 || tab[(x2)+(y2 - 1) * taille] == symboleJ1 || tab[(x2)+(y2 - 1) * taille] == symboleJ2) {
						x = x2;
						y = y2;
						return;
					}
				}
			}
			x2++;
			if (x2 > taille) {
				y2++;
				x2 = 1;
			}
		}
	}
	else{
		x2 = 0;
		y2 = 0;
		x = rand() % (taille)+1;
		y = rand() % (taille)+1;
		if (tab[(x - 1) + (y - 1) * taille] == symboleJ1 || tab[(x - 1) + (y - 1) * taille] == symboleJ2) {
			x2 = 0;
			y2 = 1;
			for (unsigned int i = 0; i < tab.size(); i++) {
				x2++;
				if (x2 > taille) {
					x2 = 1;
					y2++;
				}
				if (tab[(x2 - 1) + (y2 - 1) * taille] != symboleJ1 && tab[(x2 - 1) + (y2 - 1) * taille] != symboleJ2) {
					x = x2;
					y = y2;
					return;
				}
			}


		}
	}
	return;
}

//Bot amélioré
void Jeu::botStrategiquev2(vector<string>& tab, int& x, int& y,int& mdj) {
	int compteurJ1 = 0;
	int compteurJ2 = 0;
	int x2 = 1;
	int y2 = 1;
	//On regarde si 3 sont alignés
	for (unsigned int i = 0; i < tab.size(); i += taille) {
		if (tab.size() > i + taille) {
			for (unsigned int u = i; u <= i + taille; ++u) {
				if (tab[u] == symboleJ1) {
					if (tab[u + 1] == symboleJ1 && x2 + 3 <= taille && tab[u + 2] == symboleJ1 && tab[u + 3] == " ") {
						x = x2 + 3;
						y = y2;
						return;
					}
					if (0 < ((int)u - 1)) {
						if (tab[u + 1] == symboleJ1 && tab[u + 2] == symboleJ1 && x2 - 1 > 0 && tab[u - 1] == " ") {
							x = x2 - 1;
							y = y2;
							return;
						}
					}
					if ((int)tab.size() > (u + (taille * 3))) {
						if (tab[u + taille] == symboleJ1 && tab[u + taille * 2] == symboleJ1 && tab[u + taille * 3] == " ") {
							x = x2;
							y = y2 + 3;
							return;
						}
					}
					if (((int)u-(taille * 3))>0) {//modifier partout
						if (tab[u - taille] == symboleJ1 && tab[u - taille * 2] == symboleJ1 && tab[u - taille * 3] == " ") {
							x = x2;
							y = y2 - 3;
							return;
						}
					}
					if ((int)tab.size() > (u + (taille * 3) + 3)) {
						if (tab[u + taille + 1] == symboleJ1 && x2 + 3 <= taille && tab[u + taille * 2 + 2] == symboleJ1 && tab[u + taille * 3 + 3] == " ") {
							x = x2 + 3;
							y = y2 + 3;
							return;
						}
					}
					if (0 < ((int)u - (taille * 3) - 3)) {
						if (tab[u - taille - 1] == symboleJ1 && x2 - 3 > 0 && tab[u - taille * 2 - 2] == symboleJ1 && tab[u - taille * 3 - 3] == " ") {//modifier partout
							x = x2 - 3;
							y = y2 - 3;
							return;
						}
					}
					if ((int)tab.size() > ((int)u + (taille * 3) - 3)) {
						if (tab[u + taille - 1] == symboleJ1 && x2 - 3 > 0 && tab[u + taille * 2 - 2] == symboleJ1 && tab[u + taille * 3 - 3] == " ") {
							x = x2 - 3;
							y = y2 + 3;
							return;
						}
					}
					if ((int)tab.size() > ((int)u - (taille * 3) + 3) && ((int)u - (taille * 3) + 3)>0) {
						if (tab[u - taille + 1] == symboleJ1 && x2 + 3 <= taille && tab[u - taille * 2 + 2] == symboleJ1 && tab[u - taille * 3 + 3] == " ") {
							x = x2 + 3;
							y = y2 - 3;
							return;
						}
					}
				}
				++x2;
				if (x2 > taille) {
					x2 = 1;
				}
			}
			x2 = 1;
			compteurJ1 = 0;
		}
		y2++;
	}
	x2 = 1;
	y2 = 1;
	//On passe à l'attaque
	//On regarde si 3 sont alignés
	for (unsigned int i = 0; i < tab.size(); i += taille) {
		if (tab.size() > i + taille) {
			for (unsigned int u = i; u <= i + taille; ++u) {
				if (tab[u] == symboleJ2) {
					if (tab[u + 1] == symboleJ2 && x2 + 3 <= taille && tab[u + 2] == symboleJ2 && tab[u + 3] == " ") {
						x = x2 + 3;
						y = y2;
						return;
					}
					if (0 < ((int)u - 1)) {
						if (tab[u + 1] == symboleJ2 && tab[u + 2] == symboleJ2 && x2 - 1 > 0 && tab[u - 1] == " ") {
							x = x2 - 1;
							y = y2;
							return;
						}
					}
					if (tab.size() > (u + taille * 3)) {
						if (tab[u + taille] == symboleJ2 && tab[u + taille * 2] == symboleJ2 && tab[u + taille * 3] == " ") {
							x = x2;
							y = y2 + 3;
							return;
						}
					}
					if (0 < ((int)u + taille * -3)) {
						if (tab[u - taille] == symboleJ2 && tab[u - taille * 2] == symboleJ2 && tab[u - taille * 3] == " ") {
							x = x2;
							y = y2 - 3;
							return;
						}
					}
					if (tab.size() > (u + taille * 3 + 3)) {
						if (tab[u + taille + 1] == symboleJ2 && x2 + 3 <= taille && tab[u + taille * 2 + 2] == symboleJ2 && tab[u + taille * 3 + 3] == " ") {
							x = x2 + 3;
							y = y2 + 3;
							return;
						}
					}
					if (0 < ((int)u - taille * 3 - 3)) {
						if (tab[u - taille - 1] == symboleJ2 && x2 - 3 > 0 && tab[u - taille * 2 - 2] == symboleJ2 && tab[u - taille * 3 - 3] == " ") {
							x = x2 - 3;
							y = y2 - 3;
							return;
						}
					}
					if ((int)tab.size() > ((int)u + taille * 3 - 3)) {
						if (tab[u + taille - 1] == symboleJ2 && x2 - 3 > 0 && tab[u + taille * 2 - 2] == symboleJ2 && tab[u + taille * 3 - 3] == " ") {
							x = x2 - 3;
							y = y2 + 3;
							return;
						}
					}
					if ((int)tab.size() > ((int)u - taille * 3 + 3) && ((int)u - taille * 3 + 3) > 0) {
						if (tab[u - taille + 1] == symboleJ2 && x2 + 3 <= taille && tab[u - taille * 2 + 2] == symboleJ2 && tab[u - taille * 3 + 3] == " ") {
							x = x2 + 3;
							y = y2 - 3;
							return;
						}
					}
				}
				++x2;
				if (x2 > taille) {
					x2 = 1;
				}
			}
			x2 = 1;
			compteurJ1 = 0;
		}
		y2++;
	}
	x2 = 1;
	y2 = 1;
	//De nouveau défense
	//On verifie si 2 cases sont alignés
	for (unsigned int i = 0; i < tab.size(); i += taille) {
		if (tab.size() > i + taille) {
			for (unsigned int u = i; u <= i + taille; ++u) {
				if (tab[u] == symboleJ1) {
					if (tab[u + 1] == symboleJ1 && x2 + 2 <= taille && tab[u + 2] == " ") {
						x = x2 + 2;
						y = y2;
						return;
					}
					if (0 < ((int)u - 1)) {
						if (tab[u + 1] == symboleJ1 && x2 - 1 > 0 && tab[u - 1] == " ") {
							x = x2 - 1;
							y = y2;
							return;
						}
					}
					if (tab.size() > (u + taille * 2)) {
						if (tab[u + taille] == symboleJ1 && tab[u + taille*2] == " ") {
							x = x2;
							y = y2+2;
							return;
						}
					}
					if (0 < ((int)u + taille * -2)) {
						if (tab[u - taille] == symboleJ1  && tab[u - taille * 2] == " ") {
							x = x2;
							y = y2 - 2;
							return;
						}
					}
					if (tab.size() > (u + taille * 2+2)) {
						if (tab[u + taille+1] == symboleJ1 && x2 + 2 <= taille && tab[u + taille * 2+2] == " ") {
							x = x2+2;
							y = y2 + 2;
							return;
						}
					}
					if (0 < ((int)u - taille * 2 - 2)) {
						if (tab[u - taille - 1] == symboleJ1 && x2 - 2 > 0 && tab[u- taille * 2 - 2] == " ") {
							x = x2 - 2;
							y = y2 - 2;
							return;
						}
					}
					if ((int)tab.size() > ((int)u + taille * 2 - 2 )) {
						if (tab[u + taille - 1] == symboleJ1 && x2 - 2 > 0 && tab[u + taille * 2 - 2] == " ") {
							x = x2 - 2;
							y = y2 + 2;
							return;
						}
					}
					if ((int)tab.size() > ((int)u - taille * 2 + 2) && ((int)u - taille * 2 + 2)>0) {
						if (tab[u - taille + 1] == symboleJ1 && x2 + 2 <= taille && tab[u - taille * 2 + 2] == " ") {
							x = x2 + 2;
							y = y2 - 2;
							return;
						}
					}
				}
				++x2;
				if (x2 > taille) {
					x2 = 1;
				}
			}
			x2 = 1;
			compteurJ1 = 0;
		}
		y2++;
	}
	x2 = 1;
	y2 = 1;
	//De nouveau attaque
	//On verifie si 2 cases sont alignés
	for (unsigned int i = 0; i < tab.size(); i += taille) {
		if (tab.size() > i + taille) {
			for (unsigned int u = i; u <= i + taille; ++u) {
				if (tab[u] == symboleJ2) {
					if (tab[u + 1] == symboleJ2 && x2 + 2 <= taille && tab[u + 2] == " ") {
						x = x2 + 2;
						y = y2;
						return;
					}
					if (0 < ((int)u - 1)) {
						if (tab[u + 1] == symboleJ2 && x2 - 1 > 0 && tab[u - 1] == " ") {
							x = x2 - 1;
							y = y2;
							return;
						}
					}
					if (tab.size() > (u + taille * 2)) {
						if (tab[u + taille] == symboleJ2 && tab[u + taille * 2] == " ") {
							x = x2;
							y = y2 + 2;
							return;
						}
					}
					if (0 < ((int)u + taille * -2)) {
						if (tab[u - taille] == symboleJ2 && tab[u - taille * 2] == " ") {
							x = x2;
							y = y2 - 2;
							return;
						}
					}
					if (tab.size() > (u + taille * 2 + 2)) {
						if (tab[u + taille + 1] == symboleJ2 && x2 + 2 <= taille && tab[u + taille * 2 + 2] == " ") {
							x = x2 + 2;
							y = y2 + 2;
							return;
						}
					}
					if (0 < ((int)u - taille * 2 - 2)) {
						if (tab[u - taille - 1] == symboleJ2 && x2 - 2 > 0 && tab[u - taille * 2 - 2] == " ") {
							x = x2 - 2;
							y = y2 - 2;
							return;
						}
					}
					if ((int)tab.size() > ((int)u + taille * 2 - 2)) {
						if (tab[u + taille - 1] == symboleJ2 && x2 - 2 > 0 && tab[u + taille * 2 - 2] == " ") {
							x = x2 - 2;
							y = y2 + 2;
							return;
						}
					}
					if ((int)tab.size() > ((int)u - taille * 2 + 2) && ((int)u - taille * 2 + 2)>0) {
						if (tab[u - taille + 1] == symboleJ2 && x2 + 2 <= taille && tab[u - taille * 2 + 2] == " ") {
							x = x2 + 2;
							y = y2 - 2;
							return;
						}
					}
				}
				++x2;
				if (x2 > taille) {
					x2 = 1;
				}
			}
			x2 = 1;
			compteurJ1 = 0;
		}
		y2++;
	}
	//Si on ne trouve vraiment rien on renvoie une position aléatoire
	return botIdiot(tab, x, y,mdj);
}

//On crée des niveau de difficulté
void Jeu::bots(vector<string>& tab, int& x, int& y, int& difficulte,int& mdj) {
	srand((unsigned int)(time(NULL))); // initialisation de rand
	int number = rand() % (5 - 1) + 1;
	if (number > difficulte) {
		return botIdiot(tab, x, y,mdj);
	}
	else {
		return botStrategiquev2(tab, x, y,mdj);
	}
}