#include <SFML/Graphics.hpp>
#include <iostream>
#include <numeric>//pour accumulate
#include <algorithm>
#include <set>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "Menu.h"
#include "Jeu.h"
#include <chrono>
#include<Windows.h>
#include <SFML/Network/IpAddress.hpp>
#include <locale>
using namespace std;
//Modifier bot

Menu::Menu()
{
}

void Menu::CreationTexte(sf::Text& text,sf::Font &font, int taille, string texte, sf::Color color, float x, float y) {
	text.setFont(font); // font est un sf::Font
	// choix de la chaîne de caractères à afficher
	text.setString(texte);
	// choix de la taille des caractères
	text.setCharacterSize(taille); // exprimée en pixels, pas en points !
	// choix de la couleur du texte
	text.setFillColor(color);
	text.setPosition(x,y);
	// choix du style du texte
	text.setStyle(sf::Text::Bold );
	return;
}


void Menu::CreationImage(sf::Texture& texture, string nomImage, sf::Sprite& sprite, float scalex, float scaley, float x, float y) {
	if (!texture.loadFromFile(nomImage))
	{
		// erreur...
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.scale(scalex,scaley);/// Redimensionnement
	sprite.setPosition(x,y);
	return;
}
//Affichage lignes et pions
void Menu::AfficherLigneEtPions(sf::RenderWindow& window,int& Taille,vector<string>&tab,int&x2,int& y2,string& symboleJ1,string& symboleJ2,sf::Sprite& sprite2, sf::Sprite& sprite3) {
	//Draw lignes verticales
	for (double i = window.getSize().x * 0.75 / (Taille); i <= window.getSize().x * 0.76; i += window.getSize().x * 0.75 / (Taille)) {
		sf::VertexArray vArray(sf::Lines, 2);
		vArray[0].position = sf::Vector2f((float)(i), 0);
		vArray[1].position = sf::Vector2f((float)(i), (float)(window.getSize().y / 1.25));
		vArray[0].color = sf::Color::Black;
		vArray[1].color = sf::Color::Black;
		window.draw(vArray);
	}
	//Draw lignes horizontales
	for (double i = window.getSize().y * 0.75 / (Taille); i <= window.getSize().y * 0.76; i += window.getSize().y * 0.75 / (Taille)) {
		sf::VertexArray vArray(sf::Lines, 2);
		vArray[0].position = sf::Vector2f(0, (float)(i));
		vArray[1].position = sf::Vector2f((float)(window.getSize().x / 1.25), (float)(i));
		vArray[0].color = sf::Color::Black;
		vArray[1].color = sf::Color::Black;
		window.draw(vArray);
	}
	for (unsigned int i = 0; i < tab.size(); i++) {
		if (tab[i] == symboleJ1) {
			sprite2.setPosition(sf::Vector2f(((float)(window.getSize().x * 0.75 / (Taille))) * x2, (float)((window.getSize().y * 0.75 / (Taille)) * y2))); // position absolue
			window.draw(sprite2);
		}
		if (tab[i] == symboleJ2) {
			sprite3.setPosition(sf::Vector2f(((float)(window.getSize().x * 0.75 / (Taille))) * x2, (float)((window.getSize().y * 0.75 / (Taille)) * y2))); // position absolue
			window.draw(sprite3);
		}
		x2++;
		if (x2 > Taille) {
			x2 = 1;
			y2++;
		}
	}
}
//Affichage de la page principal
void Menu::Menuprincipal(sf::RenderWindow& window, sf::Font& font, int& boutton,sf::Texture& texture4, sf::Sprite sprite4, sf::Text text, sf::Text text2, sf::Text text3, sf::Text text4, sf::Text text5, sf::RectangleShape rectangle,sf::Text text6) {

	CreationTexte(text, font, 44, "Jeu Solo", sf::Color::Black,(float)( window.getSize().x / 15),(float)( window.getSize().y / 8));
	CreationTexte(text2, font, 44, "Jeu Multijoueur local", sf::Color::Black, (float)(window.getSize().x / 15), (float)(window.getSize().y / 2.5));
	CreationTexte(text3, font, 44, "Options", sf::Color::Black, (float)(window.getSize().x / 15), (float)(window.getSize().y / 1.5));
	CreationTexte(text4, font, 44, "Quitter", sf::Color::Black, (float)(window.getSize().x / 15), (float)(window.getSize().y / 1.25));
	CreationTexte(text5, font, 66, "Gomoku", sf::Color::Black, (float)(window.getSize().x / 2.5), (float)(window.getSize().y / 20));
	CreationTexte(text6, font, 44, "Jeu lan", sf::Color::Black, (float)(window.getSize().x / 15), (float)(window.getSize().y / 4));
	while (boutton == 0) {
		sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
		if ((unsigned)(localPosition.x) <= window.getSize().x / 5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 6 && (unsigned)(localPosition.y) >= window.getSize().y / 25) {
			text.setFillColor(sf::Color::Red);
		}
		else {
			text.setFillColor(sf::Color::Black);
		}
		if ((unsigned)(localPosition.x) <= window.getSize().x / 3.5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 2 && (unsigned)(localPosition.y) >= window.getSize().y / 3) {
			text2.setFillColor(sf::Color::Red);
		}
		else {
			text2.setFillColor(sf::Color::Black);
		}
		if ((unsigned)(localPosition.x) <= window.getSize().x / 5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 1.4 && (unsigned)(localPosition.y) >= window.getSize().y / 1.55) {
			text3.setFillColor(sf::Color::Red);
		}
		else {
			text3.setFillColor(sf::Color::Black);
		}
		if ((unsigned)(localPosition.x) <= window.getSize().x / 5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 1.1 && (unsigned)(localPosition.y) >= window.getSize().y / 1.35) {
			text4.setFillColor(sf::Color::Red);
		}
		else {
			text4.setFillColor(sf::Color::Black);
		}
		if ((unsigned)(localPosition.x) <= window.getSize().x / 5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 3 && (unsigned)(localPosition.y) >= window.getSize().y / 6) {
			text6.setFillColor(sf::Color::Red);
		}
		else {
			text6.setFillColor(sf::Color::Black);
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		window.clear();
		window.draw(rectangle);
		//Draw fond d'écran
		window.draw(sprite4);
		window.draw(text);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.draw(text5);
		window.draw(text6);
		window.display();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if ((unsigned)(localPosition.x) <= window.getSize().x / 5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 6 && (unsigned)(localPosition.y) >= window.getSize().y / 25) {
				boutton = 1;
			}
			if ((unsigned)(localPosition.x) <= window.getSize().x / 4 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 2 && (unsigned)(localPosition.y) >= window.getSize().y / 3) {
				boutton = 2;
			}
			if ((unsigned)(localPosition.x) <= window.getSize().x / 5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 1.4 && (unsigned)(localPosition.y) >= window.getSize().y / 1.55) {
				boutton = 3;
			}
			if ((unsigned)(localPosition.x) <= window.getSize().x / 5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 1.1 && (unsigned)(localPosition.y) >= window.getSize().y / 1.35) {
				boutton = 4;
			}
			if ((unsigned)(localPosition.x) <= window.getSize().x / 5 && (unsigned)(localPosition.x) >= window.getSize().x / 100 && (unsigned)(localPosition.y) <= window.getSize().y / 3 && (unsigned)(localPosition.y) >= window.getSize().y / 6) {
				boutton = 5;
			}
		}
	}
}
//Affichage de la page option
void Menu::Menuoption(sf::RenderWindow& window, sf::Font& font, int& boutton, int& playmusic, int& fond, int& figure1, int& figure2, int& botsave, sf::Music& music, int& bot) {
	sf::Texture texture5;
	if (!texture5.loadFromFile("option3.jpg"))
	{
		// erreur...
	}
	sf::Sprite sprite5;
	sprite5.setTexture(texture5);
	sprite5.scale(window.getSize().x / 2560.f, window.getSize().y / 1440.f);/// Redimensionnement
	sf::Text text4;
	CreationTexte(text4, font, 44, "Retour",sf::Color::Green, (float)(window.getSize().x / 15), (float)(window.getSize().y / 1.25));
	sf::Text text;
	CreationTexte(text, font, 44, "Bot lvl:(0dflt)", sf::Color::Green, (float)(window.getSize().x / 15), (float)(window.getSize().y / 20));
	sf::Text text2;
	CreationTexte(text2, font, 44, "1", sf::Color::Green, (float)(window.getSize().x / 15), (float)(window.getSize().y / 8));
	sf::Text text3;
	CreationTexte(text3, font, 44, "2", sf::Color::Green, (float)(window.getSize().x / 15), (float)(window.getSize().y / 5.5));
	sf::Text text5;
	CreationTexte(text5, font, 44, "3", sf::Color::Green, (float)(window.getSize().x / 15), (float)(window.getSize().y / 4.25));
	sf::Text text6;
	CreationTexte(text6, font, 44, "4", sf::Color::Green, (float)(window.getSize().x / 15), (float)(window.getSize().y / 3.5));
	sf::Text text7;
	CreationTexte(text7, font, 44, "5", sf::Color::Green, (float)(window.getSize().x / 15), (float)(window.getSize().y / 2.95));
	sf::Text text8;
	CreationTexte(text8, font, 44, "Options", sf::Color::Green, (float)(window.getSize().x / 2.25), (float)(window.getSize().y / 20));
	sf::Text text9;
	CreationTexte(text9, font, 44, "Fonds", sf::Color::Green, (float)(window.getSize().x / 4), (float)(window.getSize().y / 5));
	sf::Text text10;
	CreationTexte(text10, font, 34, "Selected", sf::Color::Green,1,1);//La position n'est pas importante ici car modifié après
	sf::Text text11;
	CreationTexte(text11, font, 44, "Perso J1:", sf::Color::Green, (float)(window.getSize().x / 4), (float)(window.getSize().y / 2));
	sf::Text text12;
	CreationTexte(text12, font, 34, "Selected", sf::Color::Green,1,1);//La position n'est pas importante ici car modifié après
	sf::Text text13;
	CreationTexte(text13, font, 44, "Perso J2:", sf::Color::Green, (float)(window.getSize().x / 4), (float)(window.getSize().y / 1.4));
	sf::Text text14;
	CreationTexte(text14, font, 34, "Selected", sf::Color::Green,1,1);//La position n'est pas importante ici car modifié après
	sf::Texture texture;
	sf::Sprite sprite;
	CreationImage(texture, "sonon.png", sprite, (float)(1366 / 2.f /window.getSize().x), (float)(768 / 2.f / window.getSize().y), (float)(window.getSize().x / 15), (float)(window.getSize().y / 2));
	sf::Texture texture2;
	sf::Sprite sprite2;
	CreationImage(texture2, "sonoff.png", sprite2, (float)(1366 / 2.f /window.getSize().x), (float)(768 / 2.f / window.getSize().y), (float)(window.getSize().x / 15), (float)(window.getSize().y / 2));
	sf::Texture texture3;
	sf::Sprite sprite3;
	CreationImage(texture3, "bois4.jpg", sprite3, (float)(1023 / 4.f / window.getSize().x), (float)(682 / 3.5 / window.getSize().y), (float)(window.getSize().x / 2.5), (float)(window.getSize().y / 5.5));
	sf::Texture texture4;
	sf::Sprite sprite4;
	CreationImage(texture4, "fond7.png", sprite4, (float)(710 / 2.f / window.getSize().x), (float)(444 / 1.5 / window.getSize().y), (float)(window.getSize().x / 1.75), (float)(window.getSize().y / 5.5));
	sf::Texture texture6;
	sf::Sprite sprite6;
	CreationImage(texture6, "spacecolors.png", sprite6, (float)(1366 / 5.f / window.getSize().x), (float)(768 / 4.f / window.getSize().y), (float)(window.getSize().x / 1.35), (float)(window.getSize().y / 5.5));
	sf::Texture texture7;
	sf::Sprite sprite7;
	CreationImage(texture7, "cercleb.png", sprite7, (float)(1366 / 11.f / window.getSize().x), (float)(768 / 11.f / window.getSize().y), (float)(window.getSize().x / 2.5), (float)(window.getSize().y / 2));
	sf::Texture texture8;
	sf::Sprite sprite8;
	CreationImage(texture8, "pion.png", sprite8, (float)(1366 / 12.f / window.getSize().x), (float)(768 / 12.f / window.getSize().y), (float)(window.getSize().x / 1.75), (float)(window.getSize().y / 2));
	sf::Texture texture9;
	sf::Sprite sprite9;
	CreationImage(texture9, "dino.png", sprite9, (float)(1366 / 9.f / window.getSize().x), (float)(768 / 9.f / window.getSize().y), (float)(window.getSize().x / 1.35), (float)(window.getSize().y / 2));
	sf::Texture texture10;
	sf::Sprite sprite10;
	CreationImage(texture10, "cerclen.png", sprite10, (float)(1366 / 11.f / window.getSize().x), (float)(768 / 11.f / window.getSize().y), (float)(window.getSize().x / 2.5), (float)(window.getSize().y / 1.4));
	sf::Texture texture11;
	sf::Sprite sprite11;
	CreationImage(texture11, "link.png", sprite11, (float)(1366 / 12.f / window.getSize().x), (float)(768 / 12.f / window.getSize().y), (float)(window.getSize().x / 1.75), (float)(window.getSize().y / 1.4));
	sf::Texture texture12;
	sf::Sprite sprite12;
	CreationImage(texture12, "hylien.png", sprite12, (float)(1366 / 9.f / window.getSize().x), (float)(768 / 9.f / window.getSize().y), (float)(window.getSize().x / 1.35), (float)(window.getSize().y / 1.4));
	window.clear();
	//Draw fond d'écran
	window.draw(sprite5);
	window.draw(text);
	window.draw(text2);
	window.draw(text3);
	window.draw(text4);
	window.draw(text5);
	window.draw(text6);
	window.draw(text7);
	window.draw(text8);
	window.draw(text9);
	window.draw(text10);
	window.draw(text11);
	window.draw(text12);
	window.draw(text13);
	window.draw(text14);
	if (playmusic == 1) {
		window.draw(sprite);
	}
	else {
		window.draw(sprite2);
	}
	window.draw(sprite3);
	window.draw(sprite4);
	window.draw(sprite6);
	window.draw(sprite7);
	window.draw(sprite8);
	window.draw(sprite9);
	window.draw(sprite10);
	window.draw(sprite11);
	window.draw(sprite12);
	window.display();
	while (boutton == 3) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
			if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 5 && (unsigned)localPosition.y >= window.getSize().y / 25) {
				text2.setFillColor(sf::Color::Red);
			}
			else {
				text2.setFillColor(sf::Color::Green);
			}
			if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 4.5 && (unsigned)localPosition.y > window.getSize().y / 5) {
				text3.setFillColor(sf::Color::Red);
			}
			else {
				text3.setFillColor(sf::Color::Green);
			}
			if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 3.5 && (unsigned)localPosition.y > window.getSize().y / 4.5) {
				text5.setFillColor(sf::Color::Red);
			}
			else {
				text5.setFillColor(sf::Color::Green);
			}
			if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 3 && (unsigned)localPosition.y > window.getSize().y / 3.5) {
				text6.setFillColor(sf::Color::Red);
			}
			else {
				text6.setFillColor(sf::Color::Green);
			}
			if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 2.5 && (unsigned)localPosition.y > window.getSize().y / 3) {
				text7.setFillColor(sf::Color::Red);
			}
			else {
				text7.setFillColor(sf::Color::Green);
			}
			if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && (unsigned)localPosition.y >= window.getSize().y / 1.35) {
				text4.setFillColor(sf::Color::Red);
			}
			else {
				text4.setFillColor(sf::Color::Green);
			}
			//Si bot est déjà selectionné on change la couleur
			if (bot == 1) {
				text2.setFillColor(sf::Color::Yellow);
			}
			if (bot == 2) {
				text3.setFillColor(sf::Color::Yellow);
			}
			if (bot == 3) {
				text5.setFillColor(sf::Color::Yellow);
			}
			if (bot == 4) {
				text6.setFillColor(sf::Color::Yellow);
			}
			if (bot == 5) {
				text7.setFillColor(sf::Color::Yellow);
			}
			if (event.type == sf::Event::MouseButtonReleased)//modifier ailleurs
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.5 && (unsigned)localPosition.y > window.getSize().y / 2) {
						if (playmusic == 1) {
							playmusic = 0;
						}
						else {
							playmusic = 1;
						}
						music.stop();
					}
				}
			}
			if (fond == 1) {
				text10.setPosition((float)(window.getSize().x / 2.5),(float)( window.getSize().y / 2.4));
			}
			if (fond == 2) {
				text10.setPosition((float)(window.getSize().x / 1.75), (float)(window.getSize().y / 2.4));
			}
			if (fond == 3) {
				text10.setPosition((float)(window.getSize().x / 1.35), (float)(window.getSize().y / 2.4));
			}
			if (figure1 == 1) {
				text12.setPosition((float)(window.getSize().x / 2.5), (float)(window.getSize().y / 1.6));
			}
			if (figure1 == 2) {
				text12.setPosition((float)(window.getSize().x / 1.75), (float)(window.getSize().y / 1.6));
			}
			if (figure1 == 3) {
				text12.setPosition((float)(window.getSize().x / 1.35), (float)(window.getSize().y / 1.6));
			}
			if (figure2 == 1) {
				text14.setPosition((float)(window.getSize().x / 2.5), (float)(window.getSize().y / 1.2));
			}
			if (figure2 == 2) {
				text14.setPosition((float)(window.getSize().x / 1.75), (float)(window.getSize().y / 1.2));
			}
			if (figure2 == 3) {
				text14.setPosition((float)(window.getSize().x / 1.35), (float)(window.getSize().y / 1.2));
			}
			window.clear();
			//Draw fond d'écran
			window.draw(sprite5);
			window.draw(text);
			window.draw(text2);
			window.draw(text3);
			window.draw(text4);
			window.draw(text5);
			window.draw(text6);
			window.draw(text7);
			window.draw(text8);
			window.draw(text9);
			window.draw(text10);
			window.draw(text11);
			window.draw(text12);
			window.draw(text13);
			window.draw(text14);
			if (playmusic == 1) {
				window.draw(sprite);
			}
			else {
				window.draw(sprite2);
			}
			window.draw(sprite3);
			window.draw(sprite4);
			window.draw(sprite6);
			window.draw(sprite7);
			window.draw(sprite8);
			window.draw(sprite9);
			window.draw(sprite10);
			window.draw(sprite11);
			window.draw(sprite12);
			window.display();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && (unsigned)localPosition.y >= window.getSize().y / 1.35) {
					boutton = 0;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 6 && (unsigned)localPosition.y >= window.getSize().y / 25) {
					bot = 1;
					botsave = 1;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 4.5 && (unsigned)localPosition.y > window.getSize().y / 5) {
					bot = 2;
					botsave = 2;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 3.5 && (unsigned)localPosition.y > window.getSize().y / 4.5) {
					bot = 3;
					botsave = 3;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 3 && (unsigned)localPosition.y > window.getSize().y / 3.5) {
					bot = 4;
					botsave = 4;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 2.5 && (unsigned)localPosition.y > window.getSize().y / 3) {
					bot = 5;
					botsave = 5;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 1.82 && (unsigned)localPosition.x >= window.getSize().x / 2.5 && (unsigned)localPosition.y <= window.getSize().y / 2.5 && (unsigned)localPosition.y > window.getSize().y / 5.5) {
					fond = 1;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 1.4 && (unsigned)localPosition.x >= window.getSize().x / 1.75 && (unsigned)localPosition.y <= window.getSize().y / 2.5 && (unsigned)localPosition.y > window.getSize().y / 5.5) {
					fond = 2;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 1.135 && (unsigned)localPosition.x >= window.getSize().x / 1.35 && (unsigned)localPosition.y <= window.getSize().y / 2.5 && (unsigned)localPosition.y > window.getSize().y / 5.5) {
					fond = 3;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 2.18 && (unsigned)localPosition.x >= window.getSize().x / 2.5 && (unsigned)localPosition.y <= window.getSize().y / 1.6 && (unsigned)localPosition.y > window.getSize().y / 2) {
					figure1 = 1;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 1.55 && (unsigned)localPosition.x >= window.getSize().x / 1.75 && (unsigned)localPosition.y <= window.getSize().y / 1.6 && (unsigned)localPosition.y > window.getSize().y / 2) {
					figure1 = 2;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 1.22 && (unsigned)localPosition.x >= window.getSize().x / 1.35 && (unsigned)localPosition.y <= window.getSize().y / 1.6 && (unsigned)localPosition.y > window.getSize().y / 2) {
					figure1 = 3;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 2.18 && (unsigned)localPosition.x >= window.getSize().x / 2.5 && (unsigned)localPosition.y <= window.getSize().y / 1.25 && (unsigned)localPosition.y > window.getSize().y / 1.4) {
					figure2 = 1;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 1.55 && (unsigned)localPosition.x >= window.getSize().x / 1.75 && (unsigned)localPosition.y <= window.getSize().y / 1.305 && (unsigned)localPosition.y > window.getSize().y / 1.4) {
					figure2 = 2;
				}
				if ((unsigned)localPosition.x <= window.getSize().x / 1.22 && (unsigned)localPosition.x >= window.getSize().x / 1.35 && (unsigned)localPosition.y <= window.getSize().y / 1.25 && (unsigned)localPosition.y > window.getSize().y / 1.4) {
					figure2 = 3;
				}
			}
		}
	}
}

//Permet de remplir un champ texte pour la taille
void Menu::IntWrite(sf::Event& input,int& clicbarre,string& taille,int& nbdecar,int& Taille) {
	if (clicbarre==1) {
		if (input.type == sf::Event::TextEntered){		
			int charTyped = input.text.unicode;
			if (47 < charTyped && charTyped < 58 ) {        //Oblige l'utilisateur a utiliser les chiffres ou les commandes de base
				if (nbdecar < 5 ) {
					if (nbdecar == taille.size() - 2) {
						taille.at(nbdecar) = charTyped;
					}
					else {
						taille += " ";
						taille.at(nbdecar) = charTyped;
					}
					nbdecar++;
				}
			}
			else if (nbdecar > 0 && (charTyped == 127 || charTyped == 8)) {        // Permet d'effacer
				//On supprime la derniere valeur
				taille.at(nbdecar - 1) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
			}
			else if (nbdecar > 0 && charTyped == 13) {
				//On récupère la valeur
				taille.at(nbdecar) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
				if (stoi(taille) >= 5 && stoi(taille) < 200) {
					Taille = stoi(taille);
				}
			}
			charTyped = 80;
		}
	}
}

//Permet de remplir un champ texte pour la taille
void Menu::WriteResponseServeur(sf::Event& input, int& clicbarre, string& taille, int& nbdecar, string& clientDecision) {
	if (clicbarre == 1) {
		if (input.type == sf::Event::TextEntered) {
			int charTyped = input.text.unicode;
			if ((64 < charTyped && charTyped < 91) || (96 < charTyped && charTyped < 123)) {        //Oblige l'utilisateur a utiliser les chiffres ou les commandes de base
				if (nbdecar < 3) {
					if (nbdecar == taille.size() - 2) {
						taille.at(nbdecar) = charTyped;
					}
					else {
						taille += " ";
						taille.at(nbdecar) = charTyped;
					}
					nbdecar++;
				}
			}
			else if (nbdecar > 0 && (charTyped == 127 || charTyped == 8)) {        // Permet d'effacer
				//On supprime la derniere valeur
				taille.at(nbdecar - 1) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
			}
			else if (nbdecar > 0 && charTyped == 13) {
				//On récupère la valeur
				taille.at(nbdecar) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
				clientDecision = taille;
			}
			charTyped = 80;
		}
	}
}

//Permet de remplir un champ texte pour la taille
void Menu::WriteIpServeur(sf::Event& input, int& clicbarre, string& taille, int& nbdecar, sf::IpAddress& server) {
	if (clicbarre == 1) {
		if (input.type == sf::Event::TextEntered) {
			int charTyped = input.text.unicode;
			if (47 < charTyped && charTyped < 58 || charTyped==46) {   //Oblige l'utilisateur a utiliser les chiffres ou les commandes de base
				if (nbdecar < 15) {
					if (nbdecar == taille.size() - 2) {
						taille.at(nbdecar) = charTyped;
					}
					else {
						taille += " ";
						taille.at(nbdecar) = charTyped;
					}
					nbdecar++;
				}
			}
			else if (nbdecar > 0 && (charTyped == 127 || charTyped == 8)) {        // Permet d'effacer
				//On supprime la derniere valeur
				taille.at(nbdecar - 1) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
			}
			else if (nbdecar > 0 && charTyped == 13) {
				//On récupère la valeur
				taille.at(nbdecar) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
				server = taille;
			}
			charTyped = 80;
		}
	}
}
// Permet de remplir un champ texte pour la nouvelle taille
void Menu::IntReWrite(sf::Event & input, int& clicbarre, string & taille, int& nbdecar, int& Taille,string& symboleJ1, string& symboleJ2, string& nomJ1 , string& nomJ2,Jeu& Carte,vector<string>& tab,vector<string>& tab2) {
	if (clicbarre == 1) {
		if (input.type == sf::Event::TextEntered) {
			int charTyped = input.text.unicode;
			if (47 < charTyped && charTyped < 58) {        //Oblige l'utilisateur a utiliser les chiffres ou les commandes de base
				if (nbdecar < 5) {
					if (nbdecar == taille.size() - 2) {
						taille.at(nbdecar) = charTyped;
					}
					else {
						taille += " ";
						taille.at(nbdecar) = charTyped;
					}
					nbdecar++;
				}
			}
			else if (nbdecar > 0 && (charTyped == 127 || charTyped == 8)) {        // Permet d'effacer
				//On supprime la derniere valeur
				taille.at(nbdecar - 1) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
			}
			else if (nbdecar > 0 && charTyped == 13) {
				//On récupère la valeur
				taille.at(nbdecar) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
				if (stoi(taille) >= 5 && stoi(taille) < 200 && stoi(taille)>Taille) {
					int Othertaille = stoi(taille);
					Jeu Carte2(Othertaille, symboleJ1, symboleJ2, nomJ1, nomJ2);
					Carte2.CreationTab(tab2);
					Carte2.AggrandirCarte(tab, tab2, Taille, Othertaille);
					Taille = Othertaille;
					Carte.taille = Othertaille;
					tab = tab2;
					taille = " ";
					nbdecar = 0;
				}
			}
			charTyped = 80;
		}
	}
}

//Permet de remplir un champ texte pour le nom
void Menu::StringWrite(sf::Event& input, int& clicbarre, string& taille, int& nbdecar,string&nom) {
	if (clicbarre == 1) {
		if (input.type == sf::Event::TextEntered) {
			int charTyped = input.text.unicode;
			if ((64 < charTyped && charTyped < 91)||(96 < charTyped && charTyped < 123)) {        //Oblige l'utilisateur a utiliser les chiffres ou les commandes de base
				if (nbdecar < 8) {
					if (nbdecar == taille.size()-2) {
						taille.at(nbdecar) = charTyped;
					}
					else {
						taille += " ";
						taille.at(nbdecar) = charTyped;
					}
					nbdecar++;
				}
			}
			else if (nbdecar > 0 && (charTyped == 127 || charTyped == 8)) {        // modifier pour le suppr
				//On supprime la derniere valeur
				taille.at(nbdecar-1) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
			}
			else if (nbdecar > 0 && charTyped == 13) {
				//On récupère la valeur
				taille.at(nbdecar) = ' ';
				taille = taille.substr(0, taille.size() - 1);
				nbdecar--;
				nom = taille;
			}
			charTyped = 80;
		}
	}
}
//Animation quand quelqu'un gagne
void Menu::AnimationWin(sf::RenderWindow& window, sf::Text text9) {
	sf::Texture texture6;
	if (!texture6.loadFromFile("victory.png"))
	{
		// erreur...
	}
	sf::Music music2;
	if (!music2.openFromFile("bam.ogg")) {
		// erreur
	}
	//music.setLoop(true);
	sf::Sprite sprite6;
	sprite6.setTexture(texture6);
	sprite6.scale(window.getSize().x / 1920.f, window.getSize().y / 1200.f);/// Redimensionnement
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);
	sf::CircleShape shape2(10.f);
	shape2.setFillColor(sf::Color::Red);
	sf::CircleShape shape3(10.f);
	shape3.setFillColor(sf::Color::Blue);
	sf::CircleShape shape4(10.f);
	shape4.setFillColor(sf::Color::White);
	sf::CircleShape shape5(10.f);
	shape5.setFillColor(sf::Color::Yellow);
	sf::CircleShape shape6(10.f);
	shape6.setFillColor(sf::Color::Magenta);
	sf::CircleShape shape7(10.f);
	shape7.setFillColor(sf::Color::Cyan);
	music2.play();//On démarre la musique
	for (int i = 1; i < 200000; i += 1150) {
		window.clear();
		window.draw(sprite6);
		shape.setPosition((float)(window.getSize().x / 2 + sqrt(i)), (float)(window.getSize().y - sqrt(i)));
		window.draw(shape);
		shape2.setPosition((float)(window.getSize().x / 2 - sqrt(i)), (float)(window.getSize().y - sqrt(i)));
		window.draw(shape2);
		shape.setPosition((float)(window.getSize().x / 2 - sqrt(i / 2)), (float)(window.getSize().y - sqrt(i / 2)));
		window.draw(shape);
		shape3.setPosition((float)(window.getSize().x / 2 + sqrt(i / 2)), (float)(window.getSize().y - sqrt(i / 2)));
		window.draw(shape3);
		shape4.setPosition((float)(window.getSize().x / 2 - sqrt(i * 2)), (float)(window.getSize().y - sqrt(i / 2)));
		window.draw(shape4);
		shape4.setPosition((float)(window.getSize().x / 2 + sqrt(i / 2)), (float)(window.getSize().y - sqrt(i * 2)));
		window.draw(shape4);
		shape6.setPosition((float)(window.getSize().x / 2 - sqrt(2 * i)), (float)(window.getSize().y - sqrt(i / 2)));
		window.draw(shape6);
		shape5.setPosition((float)(window.getSize().x / 2 - sqrt(i / 2)), (float)(window.getSize().y - sqrt(i * 2)));
		window.draw(shape5);
		shape7.setPosition((float)(window.getSize().x / 2 - sqrt(3 * i)), (float)(window.getSize().y - sqrt(i * 2)));
		window.draw(shape7);
		shape5.setPosition((float)(window.getSize().x / 2 + sqrt(i * 4)), (float)(window.getSize().y - sqrt(i * 3)));
		window.draw(shape5);
		shape6.setPosition((float)(window.getSize().x / 2 + sqrt(3 * i)), (float)(window.getSize().y - sqrt(i * 2)));
		window.draw(shape6);
		shape6.setPosition((float)(window.getSize().x / 2 - sqrt(6 * i)), (float)(window.getSize().y - sqrt(i / 3)));
		window.draw(shape6);
		shape5.setPosition((float)(window.getSize().x / 2 - sqrt(i * 2)), (float)(window.getSize().y - sqrt(i * 3)));
		window.draw(shape5);
		shape2.setPosition((float)(window.getSize().x / 2 - sqrt(5 * i)), (float)(window.getSize().y - sqrt(i * 7)));
		window.draw(shape2);
		shape3.setPosition((float)(window.getSize().x / 2 + sqrt(i * 6)), (float)(window.getSize().y - sqrt(i * 2)));
		window.draw(shape3);
		shape.setPosition((float)(window.getSize().x / 2 + sqrt(3 * i)), (float)(window.getSize().y - sqrt(i * 5)));
		window.draw(shape);
		shape6.setPosition((float)(window.getSize().x / 2 + sqrt(6 * i)), (float)(window.getSize().y - sqrt(i / 3)));
		window.draw(shape6);
		shape5.setPosition((float)(window.getSize().x / 2 + sqrt(i * 2)), (float)(window.getSize().y - sqrt(i * 3)));
		window.draw(shape5);
		shape2.setPosition((float)(window.getSize().x / 2 + sqrt(5 * i)), (float)(window.getSize().y - sqrt(i * 7)));
		window.draw(shape2);
		window.draw(text9);
		window.display();
		Sleep(15);

	}
}