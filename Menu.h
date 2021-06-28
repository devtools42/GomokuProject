#include <SFML/Graphics.hpp>
#include <iostream>
#include <numeric>//pour accumulate
#include <algorithm>
#include <set>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <string>
#include<Windows.h>
#include"Jeu.h"
#include <locale>
#include <SFML/Network/IpAddress.hpp>
using namespace std;
using namespace std;

class Menu {
public:
	Menu();
	void Menuoption(sf::RenderWindow&, sf::Font&, int&, int&, int&, int&, int&, int&, sf::Music&, int&);
	void AfficherLigneEtPions(sf::RenderWindow& , int& , vector<string>& , int& , int& , string& , string& , sf::Sprite&, sf::Sprite& );
	void Menuprincipal(sf::RenderWindow& , sf::Font& , int& , sf::Texture& , sf::Sprite , sf::Text , sf::Text , sf::Text , sf::Text , sf::Text , sf::RectangleShape,sf::Text );
	void CreationTexte(sf::Text&,sf::Font&,int,string, sf::Color,float,float);
	void CreationImage(sf::Texture&, string, sf::Sprite&,float,float, float, float);
	void IntWrite(sf::Event&, int&, string&, int&, int&);
	void IntReWrite(sf::Event&, int&, string&, int&, int&, string&, string&, string&, string&, Jeu&, vector<string>&, vector<string>&);
	void StringWrite(sf::Event&, int&, string&, int&, string&);
	void WriteResponseServeur(sf::Event&, int&, string&, int&, string&);
	void WriteIpServeur(sf::Event& , int& , string& , int& , sf::IpAddress& );
	void AnimationWin(sf::RenderWindow&,  sf::Text);
};

