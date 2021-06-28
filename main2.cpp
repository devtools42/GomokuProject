#include <SFML/Graphics.hpp>
#include <iostream>
#include <numeric>//pour accumulate
#include <algorithm>
#include <set>
#include <SFML/Audio.hpp>
#include <cmath>//math.h
#include <fstream>
#include <vector>
#include <string>
#include "Jeu.h"
#include <SFML/Network/IpAddress.hpp>
#include "Menu.h"
#include <SFML/Network.hpp>
#include <chrono>
#include <locale>
using namespace std;

////////////////////////////////////////////////////////////
/// send a message and wait for the answer.				  //
///														  //
////////////////////////////////////////////////////////////
void Server(unsigned short port, int& joueur, int& x, int& y, sf::TcpListener& listener,sf::TcpSocket& socket,Jeu& Carte,vector<string>&tab,sf::RenderWindow& window,sf::RectangleShape& rectangle2,sf::Sprite& sprite5, sf::Sprite& sprite7, sf::Sprite sprite6, sf::Sprite& sprite,sf::Text& text4, sf::Text& text8, sf::Text& text10, sf::Text& text11,int& taille2,string&symboleJ1,string& symboleJ2,sf::Sprite& sprite2, sf::Sprite& sprite3,Menu& Menu,sf::Text& text0)
{	
	if (joueur == 1) {
		// Send a message with the coordonate x and y
		Carte.Jouer(tab, x, y, joueur);
		window.clear();
		//Draw fond d'écran
		window.draw(rectangle2);
		window.draw(sprite5);
		window.draw(sprite7);
		window.draw(sprite6);
		window.draw(sprite);
		window.draw(text10);
		window.draw(text11);
		window.draw(text0);
		int x2 = 1;
		int y2 = 1;
		Menu.AfficherLigneEtPions(window, taille2, tab, x2, y2, symboleJ1, symboleJ2, sprite2, sprite3);
		window.display();
		char x3 = x;
		char y3 = y;
		const char out[2] = { x3,y3 };
		if (socket.send(out, sizeof(out)) != sf::Socket::Done)
			return;
		std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;
		// Receive a message back from the client
		char in[128];
		std::size_t received;
		if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
			return;
		if (joueur == 2) {
			joueur = 1;
		}
		else {
			joueur++;
		}
		return;
	}
	if (joueur == 2) {
		const char out[] = " ";
		if (socket.send(out, sizeof(out)) != sf::Socket::Done)
			return;

		// Receive a message back from the client
		char in[128];
		std::size_t received;
		if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
			return;
		x = in[0];
		y = in[1];
		Carte.Jouer(tab, x, y, joueur);
		if (joueur == 2) {
			joueur = 1;
		}
		else {
			joueur++;
		}
		window.clear();
		//Draw fond d'écran
		window.draw(rectangle2);
		window.draw(sprite5);
		window.draw(sprite7);
		window.draw(sprite6);
		window.draw(sprite);
		window.draw(text10);
		window.draw(text11);
		window.draw(text0);
		int x2 = 1;
		int y2 = 1;
		Menu.AfficherLigneEtPions(window, taille2, tab, x2, y2, symboleJ1, symboleJ2, sprite2, sprite3);
		window.display();
		return;
	}
}



////////////////////////////////////////////////////////////
/// Create a client, connect it to a server, display the  //
/// welcome message and send an answer.					  //
///														  //
////////////////////////////////////////////////////////////
void Client(unsigned short port, int& joueur, int& x, int& y, sf::TcpListener& listener, sf::TcpSocket& socket, Jeu& Carte, vector<string>& tab, sf::RenderWindow& window, sf::RectangleShape rectangle2, sf::Sprite sprite5, sf::Sprite sprite7, sf::Sprite sprite6, sf::Sprite sprite, sf::Text text4, sf::Text text8, sf::Text text10, sf::Text text11, int& taille2, string& symboleJ1, string& symboleJ2, sf::Sprite& sprite2, sf::Sprite& sprite3, Menu& Menu,sf::Text& text0)
{
	if (joueur == 1) {
		// Receive a message from the server
		char in[128];
		std::size_t received;
		if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
			return;
		x = in[0];
		y = in[1];
		Carte.Jouer(tab, x, y, joueur);
		window.clear();
		//Draw fond d'écran
		window.draw(rectangle2);
		window.draw(sprite5);
		window.draw(sprite7);
		window.draw(sprite6);
		window.draw(sprite);
		window.draw(text4);
		window.draw(text10);
		window.draw(text11);
		int x2 = 1;
		int y2 = 1;
		Menu.AfficherLigneEtPions(window, taille2, tab, x2, y2, symboleJ1, symboleJ2, sprite2, sprite3);
		window.display();
		const char out[] = " ";
		if (socket.send(out, sizeof(out)) != sf::Socket::Done)
			return;

		if (joueur == 2) {
			joueur = 1;
		}
		else {
			joueur++;
		}
		return;
	}
	if (joueur == 2) {
		// Send an answer to the server
		Carte.Jouer(tab, x, y, joueur);
		window.clear();
		//Draw fond d'écran
		window.draw(rectangle2);
		window.draw(sprite5);
		window.draw(sprite7);
		window.draw(sprite6);
		window.draw(sprite);
		window.draw(text4);
		window.draw(text10);
		window.draw(text11);
		int x3 = 1;
		int y3 = 1;
		Menu.AfficherLigneEtPions(window, taille2, tab, x3, y3, symboleJ1, symboleJ2, sprite2, sprite3);
		window.display();
		char x2 = x;
		char y2 = y;
		const char out[2] = { x2,y2 };
		if (socket.send(out, sizeof(out)) != sf::Socket::Done)
			return;
		std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
		char in[128];
		std::size_t received;
		if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
			return;
		if (joueur == 2) {
			joueur = 1;
		}
		else {
			joueur++;
		}
		return;

	}
}
int main()
{

#pragma region variables
	int lan = 0;//Variable pour savoir si nous sommes en lan ou non
	int taille = 0;//taille2 temporaire qui permet de changer la taille du tableau
	int port = 53000;//Port utiliser
	int tempsSave = 0;//Temps pour éviter la remise à zéro quand l'animation de l'invite de commande apparait
	sf::TcpSocket socket;
	sf::IpAddress server;
	sf::TcpListener listener;
	char data[100] = { NULL };
	int elapsed_seconds = 0;
	int menu = 1;//Variable pour se situer dans les menus
	string clientDecision = " ";//Variable pour savoir si l'ordi est client ou serveur
	int clicbarre = 0;//Variable pour savoir si l'utilisateur a cliqué ou non sur l'invite de commande
	chrono::time_point<std::chrono::system_clock> start, end;
	int firstMove = 1;//Variable qui permet de connaitre si c'est la première fois ou non
	string tailleEnTexte = "";
	int nbdecardansstring = 0;
	string symboleJ1 = "1";//Symbole du joueur 1 dans le tableau
	string symboleJ2 = "$";//Symbole du joueur 2 dans le tableau
	string nomJ1 = "J1";
	string nomJ2 = "bot";
	int playmusic = 1;//Variable pour savoir si on doit lancer la musique ou non
	int scoreJ1 = 0;
	int exception = 0;
	int scoreJ2 = 0;
	int play = 0;
	int bot = -1;//Difficulté du bot
	int joueur = 1;//Var qui permet de savoir quel joueur doit jouer
	int game = 0;
	int firstTime2 = 1;
	int boutton = 0;
	int taille2 = 0;//taille du tableau
	int nbDejoueurs = 1;
	int x2 = 0;
	int y2 = 0;
	int x = 0;
	int modeDeJeu = 0;
	int botsave = -1;//Sauvegarde du niveau de difficulté du bot
	int y = 0;
	int fond = 1;
	int aJouer = 0;
	int figure1 = 1;
	int figure2 = 1;
	int firstTime = 1;
	vector<string>tab;
	vector<string>tab2;
	Menu Menu;
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width ,sf::VideoMode::getDesktopMode().height), "Gomoku", sf::Style::Fullscreen);
#pragma endregion variables
	window.setFramerateLimit(60); // On limite le nombre de fps
	while (window.isOpen())
	{
		while (menu == 1) {
			sf::Music music;
			if (playmusic == 1) {
				if (!music.openFromFile("undertale.ogg")) {
					return -1; // erreur
				}
				music.play();//On démarre la musique
				music.setLoop(true);
			}
			if (botsave != -1) {//On crée un moyen de  sauvegarder le niveau choisi pour le bot
				bot = botsave;
			}
			sf::Font font;
			if (!font.loadFromFile("arial.ttf"))//On inclus la police
			{
				// erreur...
			}
			if (boutton == 0) {//Si on est sur le menu principal on le charge
				sf::Texture texture4;
				if (!texture4.loadFromFile("fond4.png"))
				{
					// erreur...
				}
				sf::RectangleShape rectangle(sf::Vector2f((float)window.getSize().x , (float)window.getSize().y));
				sf::Sprite sprite4;
				sprite4.setTexture(texture4);
				sprite4.scale(window.getSize().x/1024.f, window.getSize().y / 800.f);/// Redimensionnement
				sf::Text text;
				sf::Text text2;
				sf::Text text3;
				sf::Text text4;
				sf::Text text5;
				sf::Text text6;
				Menu.Menuprincipal(window, font,boutton,texture4,sprite4,text,text2, text3, text4,text5, rectangle,text6);
			}
			if (boutton == 1) {//Si bouton==1 on charge le menu de jeu
				sf::Text text0;
				Menu.CreationTexte(text0, font, 25, " ", sf::Color::Black, (float)(window.getSize().x / 1.25), (float)(window.getSize().y / 1.4));
				game = 0;
				play = 0;
				firstMove = 1;
				if (nbDejoueurs == 1 && bot == -1) {//Si la difficulté n'a pas été choisi dans les options on met le bot à une difficulté de 0
					bot = 0;
				}
				//Selon le choix de l'utilisateur on associe les différents sprites
				sf::RectangleShape rectangle2(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
				sf::Texture texture5;
				sf::Sprite sprite5;
				Menu.CreationImage(texture5, "fond5.jpg", sprite5, window.getSize().x / 3600.f, window.getSize().y / 3000.f, (float)(window.getSize().x /1.25), (float)(window.getSize().y / 4412.f));
				sf::Texture texture6;
				sf::Sprite sprite6;
				Menu.CreationImage(texture6, "fond6.png", sprite6, (float)(window.getSize().x / 1200.f), (float)(window.getSize().y / 1100.f),(float)(window.getSize().x / 3.5),(float)( window.getSize().y / 1.35));
				sf::Texture texture7;
				sf::Sprite sprite7;
				Menu.CreationImage(texture7, "shenron.png", sprite7, (float)(window.getSize().x / 11000.f), (float)(window.getSize().y / 8500.f), (float)(window.getSize().x /1.252), (float)(window.getSize().y / 3.5));
				sf::Texture texture;
				if (fond == 1) {
					if (!texture.loadFromFile("bois4.jpg"))
					{
						// erreur...
					}
				}
				if (fond == 2) {
					if (!texture.loadFromFile("fond7.png"))
					{
						// erreur...
					}
				}
				if (fond == 3) {
					if (!texture.loadFromFile("spacecolors.png"))
					{
						// erreur...
					}
				}
				texture.setSmooth(true);
				sf::Sprite sprite;
				sprite.setTexture(texture);
				if (fond == 1) {
					sprite.scale(window.getSize().x / 1250.f, window.getSize().y / 834.f);/// Redimensionnement *5/4
				}
				if (fond == 2) {
					sprite.scale(window.getSize().x / 888.f, window.getSize().y / 555.f);/// Redimensionnement
				}
				if (fond == 3) {
					sprite.scale(window.getSize().x / 1200.f, window.getSize().y / 898.f);/// Redimensionnement
				}
				sf::Texture texture2;
				if (figure1 == 1) {
					if (!texture2.loadFromFile("cercleb.png"))
					{
						// erreur...
					}
				}
				if (figure1 == 2) {
					if (!texture2.loadFromFile("pion.png"))
					{
						// erreur...
					}
				}
				if (figure1 == 3) {
					if (!texture2.loadFromFile("dino.png"))
					{
						// erreur...
					}
				}
				texture2.setSmooth(true);
				sf::Sprite sprite2;
				sprite2.setTexture(texture2);
				if (figure1 == 1) {
					sprite2.setOrigin(sf::Vector2f(457, 449.5));//On se place au milieu de la figure
				}
				if (figure1 == 2) {
					sprite2.setOrigin(sf::Vector2f(600, 521));//On se place au milieu de la figure
				}
				if (figure1 == 3) {
					sprite2.setOrigin(sf::Vector2f(482, 325));//On se place au milieu de la figure
				}
				sf::Texture texture3;
				if (figure2 == 1) {
					if (!texture3.loadFromFile("cerclen.png"))
					{
						// erreur...
					}
				}
				if (figure2 == 2) {
					if (!texture3.loadFromFile("link.png"))
					{
						// erreur...
					}
				}
				if (figure2 == 3) {
					if (!texture3.loadFromFile("hylien.png"))
					{
						// erreur...
					}
				}
				texture3.setSmooth(true);
				sf::Sprite sprite3;
				sprite3.setTexture(texture3);
				if (figure2 == 1) {
					sprite3.setOrigin(sf::Vector2f(512, 512));//On se place au milieu de la figure
				}
				if (figure2 == 2) {
					sprite3.setOrigin(sf::Vector2f(380, 500));//On se place au milieu de la figure
				}
				if (figure2 == 3) {
					sprite3.setOrigin(sf::Vector2f(450, 270));//On se place au milieu de la figure
				}
				//On crée différents textes
				sf::Text text4;
				Menu.CreationTexte(text4, font, 44, "Retour", sf::Color::Black, (float)(window.getSize().x / 15), (float)(window.getSize().y / 1.25));
				sf::Text text5;
				Menu.CreationTexte(text5, font, 44, "Mode de jeu :", sf::Color::Black, (float)(window.getSize().x / 5), (float)(window.getSize().y / 1.25));
				sf::Text text6;
				Menu.CreationTexte(text6, font, 44, "Puissance 5(Morpion) ", sf::Color::Black, (float)(window.getSize().x / 2), (float)(window.getSize().y / 1.25));
				sf::Text text7;
				Menu.CreationTexte(text7, font, 44, "Gomoku ", sf::Color::Black, (float)(window.getSize().x / 2), (float)(window.getSize().y / 1.1));
				sf::Text text8;
				Menu.CreationTexte(text8, font, 44, "Rentrer la taille ici :", sf::Color::Black, (float)(window.getSize().x / 1.5), (float)(window.getSize().y / 1.25));
				sf::Text text9;
				Menu.CreationTexte(text9, font, 44, "", sf::Color::White, (float)(window.getSize().x / 1.5), (float)(window.getSize().y / 1.11));
				sf::Text text10;
				Menu.CreationTexte(text10, font, 33, "Score :", sf::Color::Black, (float)(window.getSize().x / 5), (float)(window.getSize().y / 1.25));
				sf::Text text11;
				Menu.CreationTexte(text11, font, 44, " ", sf::Color::Black, (float)(window.getSize().x / 15), (float)(window.getSize().y / 1.1));
				if (lan == 0) {
					modeDeJeu = 0;
					clicbarre = 0;
					taille2 = 0;
				}
				nbdecardansstring = 0;
				text9.setStyle(sf::Text::Regular);
				tailleEnTexte = ' ';
				sf::RectangleShape rectangle(sf::Vector2f((float)(window.getSize().x / 5.f), (float)(window.getSize().y / 15.f)));
				rectangle.setFillColor(sf::Color::Black);
				rectangle.setPosition((float)(window.getSize().x / 1.5), (float)(window.getSize().y / 1.1));
				//tant que le mode de jeu n'est pas choisi on affiche
				while (modeDeJeu == 0) {
					//Tant que la taille n'est pas selectionné on affiche
					while (taille2 <= 0) {
						sf::Event event;
						if (modeDeJeu == 3) {
							break;
						}
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed)
								window.close();
							text9.setString(tailleEnTexte);
							window.clear();
							//Draw fond d'écran
							window.draw(rectangle2);
							window.draw(rectangle);
							window.draw(sprite5);
							window.draw(sprite6);
							window.draw(sprite7);
							window.draw(sprite);
							window.draw(text4);
							window.draw(text8);
							window.draw(text9);
							window.display();
							if (event.type == sf::Event::MouseButtonReleased)//modifier ailleurs
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
									if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && localPosition.y <= window.getSize().y / 1.1 && localPosition.y >= window.getSize().y / 1.35) {
										boutton = 0;
										play = 1;
										modeDeJeu = 3;
										//Si on clic sur le bouton retour le jeu quitte
										break;
									}
									if (localPosition.x <= window.getSize().x / 1.15 && localPosition.x >= window.getSize().x / 1.5 && localPosition.y <= window.getSize().y / 1.03 && localPosition.y >= window.getSize().y / 1.1) {
										clicbarre = 1;
										//Si on clic sur le rectangle une invite de commande s'affiche
										tailleEnTexte.at(nbdecardansstring) = '|';
										start = std::chrono::system_clock::now();
									}
								}
							}
							if (clicbarre == 1) {
								end = std::chrono::system_clock::now();
								elapsed_seconds = (int)(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());//On obtient le temps depuis le start
								if (elapsed_seconds > 0.5 && tailleEnTexte.at(nbdecardansstring) == '|') {//Si cela fais plus de 0.5 seconde on enlève 
									tailleEnTexte.at(nbdecardansstring) = ' ';
									start = std::chrono::system_clock::now();
								}
								else if (elapsed_seconds > 0.5) {//Si cela fais plus de 1 seconde on ajoute
									tailleEnTexte.at(nbdecardansstring) = '|';
									start = std::chrono::system_clock::now();
								}

							}
							//On vérifie si les touches chiffres ont été appuyés
							Menu.IntWrite(event, clicbarre, tailleEnTexte, nbdecardansstring, taille2);
						}
					}
					tailleEnTexte = ' ';
					nbdecardansstring = 0;
					nomJ1 = "J1";
					nomJ2 = "J2";
					text8.setString("Nom J1 :");
					//Tant que l'utilisateur ne donne pas de nom
					while (nomJ1 == "J1" && modeDeJeu == 0 && lan==0) {
						boutton = 1;
						play = 0;
						modeDeJeu = 0;
						if (nomJ2 != "J2") {
							break;
						}
						sf::Event event;
						while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
								window.close();
							text9.setString(tailleEnTexte);
							window.clear();
							//Draw fond d'écran
							window.draw(rectangle2);
							window.draw(rectangle);
							window.draw(sprite5);
							window.draw(sprite6);
							window.draw(sprite7);
							window.draw(sprite);
							window.draw(text4);
							window.draw(text8);
							window.draw(text9);
							window.display();
							if (event.type == sf::Event::MouseButtonReleased)//modifier ailleurs
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
									if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && localPosition.y <= window.getSize().y / 1.1 && localPosition.y >= window.getSize().y / 1.35) {
										boutton = 0;
										play = 1;
										modeDeJeu = 3;
										nbDejoueurs = 1;
										break;
									}
									if (localPosition.x <= window.getSize().x / 1.15 && localPosition.x >= window.getSize().x / 1.5 && localPosition.y <= window.getSize().y / 1.03 && localPosition.y >= window.getSize().y / 1.1) {
										clicbarre = 1;
										tailleEnTexte.at(nbdecardansstring) = '|';
										start = std::chrono::system_clock::now();
									}
								}
							}
							if (clicbarre == 1) {
								end = std::chrono::system_clock::now();
								elapsed_seconds =(int)( std::chrono::duration_cast<std::chrono::seconds>(end - start).count());//On obtient le temps depuis le start
								if (elapsed_seconds > 0.5 && tailleEnTexte.at(nbdecardansstring) == '|') {//Si cela fais plus de 0.5 seconde on enlève 
									tailleEnTexte.at(nbdecardansstring) = ' ';
									start = std::chrono::system_clock::now();
								}
								else if (elapsed_seconds > 0.5) {//Si cela fais plus de 1 seconde on ajoute
									tailleEnTexte.at(nbdecardansstring) = '|';
									start = std::chrono::system_clock::now();
								}

							}
							//On crée une invite de commande pour demander le nom de l'utilisateur
							Menu.StringWrite(event, clicbarre, tailleEnTexte, nbdecardansstring, nomJ1);
						}
					}
					if (nbDejoueurs == 2 && modeDeJeu!=3 && lan==0) {
						tailleEnTexte = ' ';
						nbdecardansstring = 0;
						text8.setString("Nom J2 :");
						while (nomJ2 == "J2" && modeDeJeu != 3) {
							sf::Event event;
							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
									window.close();
								text9.setString(tailleEnTexte);
								window.clear();
								//Draw fond d'écran
								window.draw(rectangle2);
								window.draw(rectangle);
								window.draw(sprite5);
								window.draw(sprite6);
								window.draw(sprite7);
								window.draw(sprite);
								window.draw(text4);
								window.draw(text8);
								window.draw(text9);
								window.display();
								if (event.type == sf::Event::MouseButtonReleased)//modifier ailleurs
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
										if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && localPosition.y <= window.getSize().y / 1.1 && localPosition.y >= window.getSize().y / 1.35) {
											boutton = 0;
											play = 1;
											modeDeJeu = 3;
											break;
										}
										if ((unsigned)localPosition.x <= window.getSize().x / 1.15 && localPosition.x >= window.getSize().x / 1.5 && localPosition.y <= window.getSize().y / 1.03 && localPosition.y >= window.getSize().y / 1.1) {
											clicbarre = 1;
											tailleEnTexte.at(nbdecardansstring) = '|';
											start = std::chrono::system_clock::now();
										}
									}
								}
								if (clicbarre == 1) {
									end = std::chrono::system_clock::now();
									elapsed_seconds =(int)( std::chrono::duration_cast<std::chrono::seconds>(end - start).count());//On obtient le temps depuis le start
									if (elapsed_seconds > 0.5 && tailleEnTexte.at(nbdecardansstring) == '|') {//Si cela fais plus de 0.5 seconde on enlève 
										tailleEnTexte.at(nbdecardansstring) = ' ';
										start = std::chrono::system_clock::now();
									}
									else if (elapsed_seconds > 0.5) {//Si cela fais plus de 1 seconde on ajoute
										tailleEnTexte.at(nbdecardansstring) = '|';
										start = std::chrono::system_clock::now();
									}

								}
								//On crée une invite de commande pour demander le nom de l'utilisateur
								Menu.StringWrite(event, clicbarre, tailleEnTexte, nbdecardansstring, nomJ2);
							}
							
						}
					}
					//Tant que le mode de jeu n'est pas selectionné
					while (modeDeJeu == 0) {
						sf::Event event;
						event.mouseButton.button = sf::Mouse::Right;
						while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
								window.close();
						}
						window.clear();
						//Draw fond d'écran
						window.draw(rectangle2);
						window.draw(sprite7);
						window.draw(sprite5);
						window.draw(sprite);
						window.draw(text4);
						window.draw(text5);
						window.draw(text6);
						//if (nbDejoueurs == 2) {
							window.draw(text7);
						//}
						window.display();
						if (event.type == sf::Event::MouseButtonReleased)
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
								if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && (unsigned)localPosition.y >= window.getSize().y / 1.35) {
									boutton = 0;
									play = 1;
									nbDejoueurs = 1;
									break;
								}
								if ((unsigned)localPosition.x <= window.getSize().x / 1.2 && (unsigned)localPosition.x >= window.getSize().x / 2 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && (unsigned)localPosition.y >= window.getSize().y / 1.35) {
									modeDeJeu = 1;
									break;
								}
								if ((unsigned)localPosition.x <= window.getSize().x / 1.2 && (unsigned)localPosition.x >= window.getSize().x / 2 && (unsigned)localPosition.y <= window.getSize().y / 1 && (unsigned)localPosition.y > window.getSize().y / 1.1 ){
									//&& nbDejoueurs == 2) {
									modeDeJeu = 2;
									firstMove = 1;
									break;
								}
							}
						}
						sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
						if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1 && (unsigned)localPosition.y >= window.getSize().y / 1.1) {
							text4.setFillColor(sf::Color::Red);
						}
						else {
							text4.setFillColor(sf::Color::Black);
						}
						if ((unsigned)localPosition.x <= window.getSize().x / 1.2 && (unsigned)localPosition.x >= window.getSize().x / 2 && (unsigned)localPosition.y <= window.getSize().y / 1.15 && (unsigned)localPosition.y >= window.getSize().y / 1.3) {
							text6.setFillColor(sf::Color::Red);
						}
						else {
							text6.setFillColor(sf::Color::Black);
						}
						if ((unsigned)localPosition.x <= window.getSize().x / 1.2 && (unsigned)localPosition.x >= window.getSize().x / 2 && (unsigned)localPosition.y <= window.getSize().y / 1 && (unsigned)localPosition.y >= window.getSize().y / 1.1) {
							text7.setFillColor(sf::Color::Red);
						}
						else {
							text7.setFillColor(sf::Color::Black);
						}
					}
					
				}
				text8.setString("Rentrer la taille ici :");
				Jeu Carte(taille2, symboleJ1, symboleJ2, nomJ1, nomJ2);
				text9.setString("");
				while (play == 0  && modeDeJeu!=3) {
					start = std::chrono::system_clock::now();
					//Permet de ne pas perdre le temps lors de l'animation
					tempsSave = 0;
					text10.setString("Score : " + nomJ1 + " : " + to_string(scoreJ1) + " / " + nomJ2 + " : " + to_string(scoreJ2));
					firstMove = 1;
					//Creation du tableau
					Carte.CreationTab(tab);
					while (game == 0) {
						end = std::chrono::system_clock::now();
						elapsed_seconds = (int)(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
						text11.setString(to_string(elapsed_seconds+tempsSave)+" secondes");
						sf::Event event;
						while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
								window.close();
						}
						x = 2;
						y = 2;
						window.clear();
						//Draw fond d'écran
						window.draw(rectangle2);
						window.draw(sprite5);
						window.draw(sprite7);
						window.draw(sprite6);
						window.draw(sprite);
						if (lan == 0) {
							window.draw(text4);
							window.draw(text8);
						}
						window.draw(text10);
						window.draw(text11);
						if (lan == 0) {
							window.draw(rectangle);
							window.draw(text9);
						}
						if (nbDejoueurs == 2 || lan == 1) {
							window.draw(text0);
						}
						x2 = 1;
						y2 = 1;
						Menu.AfficherLigneEtPions(window, taille2, tab, x2, y2, symboleJ1, symboleJ2, sprite2, sprite3);
						window.display();
						tailleEnTexte = " ";
						nbdecardansstring = 0;
						clicbarre = 0;
						firstTime = 1;
						aJouer = 0;
						//Si le mode de Jeu est égal à 1 et que le joueur en question doit jouer on attend sa selection de position pour le pion
						if ((((joueur == 1 || nbDejoueurs == 2)&& lan==0)||(lan==1 && ((joueur==1 && clientDecision=="non")|| (joueur == 2 && clientDecision == "oui" )))) && modeDeJeu==1 ) {
							Sleep(300);
							sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
							while (((tab[(x - 1) + (y - 1) * taille2] == symboleJ1) || (tab[(x - 1) + (y - 1) * taille2] == symboleJ2)) || (x <= 0 || y <= 0) || firstTime == 1){
								end = std::chrono::system_clock::now();
								elapsed_seconds = (int)(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
								//On crée le un moyen de cliquer directement sur l'écran
									sf::Event event; 
									while (window.pollEvent(event))
									{
										if (event.type == sf::Event::Closed)
											window.close();

										sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
										if (event.type == sf::Event::MouseButtonReleased)//modifier ailleurs
										{
											if (event.mouseButton.button == sf::Mouse::Left)
											{
												x2 = (int)(localPosition.x / (window.getSize().x * 0.85 / (taille2)) + 1);
												y2 = (int)(localPosition.y / (window.getSize().x * 0.85 / (taille2)) + 1);
												if (x2 > 0 && x2 <= taille2 && y2 > 0 && y2 <= taille2) {
													x2 = 1;
													y2 = 1;
													for (unsigned int i = 0; i < tab.size(); i++) {
														if (x2 > taille2) {
															x2 = 1;
															y2++;

														}
														if ((localPosition.x >= (window.getSize().x * 0.75 / (taille2)) * (x2 - 0.5)) && (localPosition.x <= (window.getSize().x * 0.75 / (taille2)) * (x2 + 0.5)) && (localPosition.y <= (window.getSize().y * 0.75 / (taille2)) * (y2 + 0.5)) && (localPosition.y >= (window.getSize().y * 0.75 / (taille2)) * (y2 - 0.5))) {
															x = x2;
															y = y2;
															firstTime = 0;
															aJouer = 1;
														}
														x2++;
													}
												}
												//retour
												if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && localPosition.y >= window.getSize().y / 1.23 && lan==0) {
													boutton = 0;
													firstTime = 0;
													game = 3;
													play = 1;
													scoreJ1 = 0;
													scoreJ2 = 0;
													nbDejoueurs = 1;
													break;
												}
												//Invite de commande
												if ((unsigned)localPosition.x <= window.getSize().x / 1.15 && (unsigned)localPosition.x >= window.getSize().x / 1.5 && (unsigned)localPosition.y <= window.getSize().y / 1.03 && localPosition.y >= window.getSize().y / 1.1 && lan==0) {
													clicbarre = 1;
													tailleEnTexte.at(nbdecardansstring) = '|';
													tempsSave += elapsed_seconds;
													start = std::chrono::system_clock::now();
												}
											}
										}
										x2 = 0;
										y2 = 0;
										if (clicbarre == 1) {
											end = std::chrono::system_clock::now();
											elapsed_seconds = (int)(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());//On obtient le temps depuis le start
											if (elapsed_seconds > 0.5 && tailleEnTexte.at(nbdecardansstring) == '|') {//Si cela fais plus de 0.5 seconde on enlève 
												tailleEnTexte.at(nbdecardansstring) = ' ';
												start = std::chrono::system_clock::now();
											}
											else if (elapsed_seconds > 0.5) {//Si cela fais plus de 1 seconde on ajoute
												tailleEnTexte.at(nbdecardansstring) = '|';
												start = std::chrono::system_clock::now();
											}

										}
										//On appelle la fonction qui permet de taper une nouvelle taille 
										Menu.IntReWrite(event, clicbarre, tailleEnTexte, nbdecardansstring, taille2, symboleJ1, symboleJ2, nomJ1, nomJ2, Carte, tab, tab2);
										text9.setString(tailleEnTexte);
									}
									sprite2.setScale(sf::Vector2f((float)(0.5 / taille2), (float)(0.5 / taille2))); // facteurs d'échelle absolus
									sprite3.setScale(sf::Vector2f((float)(0.5 / taille2), (float)(0.5 / taille2))); // facteurs d'échelle absolus
									if (clicbarre == 0) {
										text11.setString(to_string(elapsed_seconds + tempsSave) + " secondes");
									}
									else {
										text11.setString(to_string(tempsSave) + " secondes");
									}
									window.clear();
									//Draw fond d'écran
									window.draw(rectangle2);
									window.draw(sprite5);
									window.draw(sprite7);
									window.draw(sprite6);
									window.draw(sprite);
									if (lan == 0) {
										window.draw(text4);
										window.draw(text8);
									}
									window.draw(text10);
									window.draw(text11);
									if (lan == 0) {
										window.draw(rectangle);
										window.draw(text9);
									}
									if (nbDejoueurs == 2  || lan==1) {
										window.draw(text0);
									}
									x2 = 1;
									y2 = 1;
									Menu.AfficherLigneEtPions(window, taille2, tab, x2, y2, symboleJ1, symboleJ2, sprite2, sprite3);
									window.display();
								
								if (game == 3 ) {
									break;
								}
							}
						}
						//Si mode de jeu 2 (Gomoku)
						if (modeDeJeu == 2) {
							if ((((joueur == 1 && modeDeJeu == 2 && lan==0) || (clientDecision == "oui"  && joueur == 2) || (clientDecision == "non"  && joueur == 1)) || nbDejoueurs == 2) && ((modeDeJeu == 2 || modeDeJeu == 4) && firstMove == 0)) {
								//if ((joueur == 1 && modeDeJeu == 2) || (nbDejoueurs == 2) && ((modeDeJeu == 2) && firstMove == 0)) {

								Sleep(300);
								//On vérifie que le joueur pose bien à coté d'un pion
								while (((tab[(x - 1) + (y - 1) * taille2] == symboleJ1) || (tab[(x - 1) + (y - 1) * taille2] == symboleJ2)) || (x <= 0 || y <= 0) || firstTime == 1 || ((tab[(x - 1) + (y - 2) * taille2] != symboleJ1) && (tab[(x - 1) + (y - 2) * taille2] != symboleJ2) && (tab[(x - 2) + (y - 1) * taille2] != symboleJ1) && (tab[(x - 2) + (y - 1) * taille2] != symboleJ2) && (tab[(x)+(y - 1) * taille2] != symboleJ1) && (tab[(x)+(y - 1) * taille2] != symboleJ2) && (tab[(x - 1) + (y)*taille2] != symboleJ1) && (tab[(x - 1) + (y)*taille2] != symboleJ2 && (tab[(x - 2) + (y - 2) * taille2] != symboleJ1) && (tab[(x - 2) + (y - 2) * taille2] != symboleJ2) && (tab[(x)+(y)*taille2] != symboleJ1) && (tab[(x)+(y)*taille2] != symboleJ2) && (tab[(x)+(y - 2) * taille2] != symboleJ1) && (tab[(x)+(y - 2) * taille2] != symboleJ2) && (tab[(x - 2) + (y)*taille2] != symboleJ1) && (tab[(x - 2) + (y)*taille2] != symboleJ2)))) {
									end = std::chrono::system_clock::now();
									elapsed_seconds = (int)(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
									sf::Event event;
									while (window.pollEvent(event))
									{
										sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
										if (event.type == sf::Event::MouseButtonReleased)//modifier ailleurs
										{
											if (event.mouseButton.button == sf::Mouse::Left)
											{
												x2 = (int)(localPosition.x / (window.getSize().x * 0.85 / (taille2)) + 1);
												y2 = (int)(localPosition.y / (window.getSize().x * 0.85 / (taille2)) + 1);
												if (x2 > 0 && x2 <= taille2 && y2 > 0 && y2 <= taille2) {
													x2 = 1;
													y2 = 1;
													for (unsigned int i = 0; i < tab.size(); i++) {
														if (x2 > taille2) {
															x2 = 1;
															y2++;

														}
														if ((localPosition.x >= (window.getSize().x * 0.75 / (taille2)) * (x2 - 0.5)) && (localPosition.x <= (window.getSize().x * 0.75 / (taille2)) * (x2 + 0.5)) && (localPosition.y <= (window.getSize().y * 0.75 / (taille2)) * (y2 + 0.5)) && (localPosition.y >= (window.getSize().y * 0.75 / (taille2)) * (y2 - 0.5))) {
															x = x2;
															y = y2;
															aJouer = 1;
														}
														x2++;
													}
													firstTime = 0;
												}
												if (x == taille2 && y < taille2 && y>1) {//Exceptions
													if (((tab[(x - 1) + (y - 1) * taille2] != symboleJ1) && (tab[(x - 1) + (y - 1) * taille2] != symboleJ2)) && ((tab[(x - 1) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 1) + (y - 2) * taille2] == symboleJ2) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ2) || (tab[(x - 1) + (y)*taille2] == symboleJ1) || (tab[(x - 1) + (y)*taille2] == symboleJ2 || (tab[(x - 2) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 2) * taille2] == symboleJ2) || (tab[(x - 2) + (y)*taille2] == symboleJ1) || (tab[(x - 2) + (y)*taille2] == symboleJ2)))) {
														exception = 1;
														break;
													}
													else {
														firstTime = 1;
														x = 2;
														y = 2;
													}
												}
												if (x == taille2 && y == taille2) {//Exceptions
													if (((tab[(x - 1) + (y - 1) * taille2] != symboleJ1) && (tab[(x - 1) + (y - 1) * taille2] != symboleJ2)) && ((tab[(x - 1) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 1) + (y - 2) * taille2] == symboleJ2) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ2) || (tab[(x - 2) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 2) * taille2] == symboleJ2))) {
														exception = 1;
														break;
													}
													else {
														firstTime = 1;
														x = 2;
														y = 2;
													}
												}
												if (x < taille2 && y == taille2 && x>1) {//Exceptions
													if (((tab[(x - 1) + (y - 1) * taille2] != symboleJ1) && (tab[(x - 1) + (y - 1) * taille2] != symboleJ2)) && (((tab[(x - 1) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 1) + (y - 2) * taille2] == symboleJ2) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ2) || (tab[(x)+(y - 1) * taille2] == symboleJ1) || (tab[(x)+(y - 1) * taille2] == symboleJ2) || (tab[(x - 2) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 2) * taille2] == symboleJ2) || (tab[(x)+(y - 2) * taille2] == symboleJ1) || (tab[(x)+(y - 2) * taille2] == symboleJ2)))) {
														exception = 1;
														break;
													}
													else {
														firstTime = 1;
														x = 2;
														y = 2;
													}
												}
												if (x == taille2 && y == 1) {//Exceptions
													if (((tab[(x - 1) + (y - 1) * taille2] != symboleJ1) && ((tab[(x - 1) + (y - 1) * taille2] != symboleJ2)) && (tab[(x - 2) + (y - 1) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ2) || (tab[(x - 1) + (y)*taille2] == symboleJ1) || (tab[(x - 1) + (y)*taille2] == symboleJ2 || (tab[(x - 2) + (y)*taille2] == symboleJ1) || (tab[(x - 2) + (y)*taille2] == symboleJ2)))) {
														exception = 1;
														break;
													}
													else {
														firstTime = 1;
														x = 2;
														y = 2;
													}
												}
												if (x == 1 && y == taille2) {//Exceptions
													if (((tab[(x - 1) + (y - 1) * taille2] != symboleJ1) && (tab[(x - 1) + (y - 1) * taille2] != symboleJ2)) && (((tab[(x - 1) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 1) + (y - 2) * taille2] == symboleJ2) || (tab[(x)+(y - 1) * taille2] == symboleJ1) || (tab[(x)+(y - 1) * taille2] == symboleJ2) || (tab[(x)+(y - 2) * taille2] == symboleJ1) || (tab[(x)+(y - 2) * taille2] == symboleJ2)))) {
														exception = 1;
														break;
													}
													else {
														firstTime = 1;
														x = 2;
														y = 2;
													}
												}
												if (x > 0 && y == taille2 && x < taille2) {//Exceptions
													if (((tab[(x - 1) + (y - 1) * taille2] != symboleJ1) && (tab[(x - 1) + (y - 1) * taille2] != symboleJ2)) && (((tab[(x - 1) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 1) + (y - 2) * taille2] == symboleJ2) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ2) || (tab[(x)+(y - 1) * taille2] == symboleJ1) || (tab[(x)+(y - 1) * taille2] == symboleJ2) || (tab[(x - 2) + (y - 2) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 2) * taille2] == symboleJ2) || (tab[(x)+(y - 2) * taille2] == symboleJ1) || (tab[(x)+(y - 2) * taille2] == symboleJ2)))) {
														exception = 1;
														break;
													}
													else {
														firstTime = 1;
														x = 2;
														y = 2;
													}
												}
												if (x == 1 && y == 1) {//Exceptions
													if (((tab[(x - 1) + (y - 1) * taille2] != symboleJ1) && (tab[(x - 1) + (y - 1) * taille2] != symboleJ2)) && (((tab[(x)+(y - 1) * taille2] == symboleJ1) || (tab[(x)+(y - 1) * taille2] == symboleJ2) || (tab[(x - 1) + (y)*taille2] == symboleJ1) || (tab[(x - 1) + (y)*taille2] == symboleJ2) || (tab[(x)+(y)*taille2] == symboleJ1) || (tab[(x)+(y)*taille2] == symboleJ2)))) {
														exception = 1;
														break;
													}
													else {
														firstTime = 1;
														x = 2;
														y = 2;
													}
												}
												if (x > 1 && y == 1 && x < taille2) {//Exceptions
													if (((tab[(x - 1) + (y - 1) * taille2] != symboleJ1) && (tab[(x - 1) + (y - 1) * taille2] != symboleJ2)) && (((tab[(x - 2) + (y - 1) * taille2] == symboleJ1) || (tab[(x - 2) + (y - 1) * taille2] == symboleJ2) || (tab[(x)+(y - 1) * taille2] == symboleJ1) || (tab[(x)+(y - 1) * taille2] == symboleJ2) || (tab[(x - 1) + (y)*taille2] == symboleJ1) || (tab[(x - 1) + (y)*taille2] == symboleJ2 || (tab[(x)+(y)*taille2] == symboleJ1) || (tab[(x)+(y)*taille2] == symboleJ2) || (tab[(x - 2) + (y)*taille2] == symboleJ1) || (tab[(x - 2) + (y)*taille2] == symboleJ2))))) {
														exception = 1;
														break;
													}
													else {
														firstTime = 1;
														x = 2;
														y = 2;
													}
												}
												//Retour
												if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && localPosition.y >= window.getSize().y / 1.23) {
													boutton = 0;
													firstTime = 0;
													game = 3;
													play = 1;
													scoreJ1 = 0;
													scoreJ2 = 0;
													nbDejoueurs = 1;
													break;
												}
												//Invite de commande
												if (localPosition.x <= window.getSize().x / 1.15 && localPosition.x >= window.getSize().x / 1.5 && localPosition.y <= window.getSize().y / 1.03 && localPosition.y >= window.getSize().y / 1.1) {
													clicbarre = 1;
													tailleEnTexte.at(nbdecardansstring) = '|';
													tempsSave += elapsed_seconds;
													start = std::chrono::system_clock::now();
												}
											}
										}
										if (clicbarre == 1) {
											end = std::chrono::system_clock::now();
											elapsed_seconds = (int)(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());//On obtient le temps depuis le start
											if (elapsed_seconds > 0.5 && tailleEnTexte.at(nbdecardansstring) == '|') {//Si cela fais plus de 0.5 seconde on enlève 
												tailleEnTexte.at(nbdecardansstring) = ' ';
												start = std::chrono::system_clock::now();
											}
											else if (elapsed_seconds > 0.5) {//Si cela fais plus de 1 seconde on ajoute
												tailleEnTexte.at(nbdecardansstring) = '|';
												start = std::chrono::system_clock::now();
											}

										}
										Menu.IntReWrite(event, clicbarre, tailleEnTexte, nbdecardansstring, taille2, symboleJ1, symboleJ2, nomJ1, nomJ2, Carte, tab, tab2);
										text9.setString(tailleEnTexte);
									}
									sprite2.setScale(sf::Vector2f((float)(0.5 / taille2), (float)(0.5 / taille2))); // facteurs d'échelle absolus
									sprite3.setScale(sf::Vector2f((float)(0.5 / taille2), (float)(0.5 / taille2))); // facteurs d'échelle absolus
									if (clicbarre == 0) {
										text11.setString(to_string(elapsed_seconds + tempsSave) + " secondes");
									}
									else {
										text11.setString(to_string(tempsSave) + " secondes");
									}
									window.clear();
									//Draw fond d'écran
									window.draw(rectangle2);
									window.draw(sprite5);
									window.draw(sprite7);
									window.draw(sprite6);
									window.draw(sprite);
									if (lan == 0) {
										window.draw(text4);
										window.draw(text8);
									}
									window.draw(text10);
									window.draw(text11);
									if (nbDejoueurs == 2 || lan == 1) {
										window.draw(text0);
									}
									if (lan== 0) {
										window.draw(rectangle);
										window.draw(text9);
									}
									x2 = 1;
									y2 = 1;
									Menu.AfficherLigneEtPions(window, taille2, tab, x2, y2, symboleJ1, symboleJ2, sprite2, sprite3);
									window.display();

									if (game == 3 || exception == 1) {
										break;
									}
								}
							}
							//Si c'est le premier tour et que l'on joue au gomoku alors on place le pion au centre
							else  {
							if (taille2 % 2) {
								x = taille2 / 2 + 1;
								y = taille2 / 2 + 1;
								aJouer = 1;
							}
							else {
								x = taille2 / 2;
								y = taille2 / 2;
								aJouer = 1;
							}
						}
						}
						
						if (game == 3) {
							break;
						}
						exception = 0;
						if (nbDejoueurs == 1 && joueur == 2 &&  (modeDeJeu==1 || firstMove == 0)&& lan==0) {
							//On appelle le bot si besoin selon le niveau definit préalablement
							if (bot == 0) {
								Carte.botIdiot(tab, x, y,modeDeJeu);
								aJouer = 1;
							}
							if (bot > 0) {
								Carte.bots(tab, x, y,bot, modeDeJeu);
								aJouer = 1;
							}
						}
						firstMove = 0;
						firstTime = 1;
						sprite2.setScale(sf::Vector2f((float)(0.5 / taille2), (float)(0.5 / taille2))); // facteurs d'échelle absolus
						sprite3.setScale(sf::Vector2f((float)(0.5 / taille2), (float)(0.5 / taille2))); // facteurs d'échelle absolus
						if (lan == 0) {
							while (x > taille2 || y > taille2&& nbDejoueurs == 1 && joueur == 2) {
								Carte.botIdiot(tab, x, y, modeDeJeu);//Si on voit que le bot à un pb on renvoie une position aleatoire
								aJouer = 1;
							}
						}
						if (joueur == 1) {
							if (clientDecision == "Oui" || clientDecision == "oui") {
								Client(port, joueur, x, y, listener, socket, Carte, tab, window, rectangle2, sprite5, sprite7, sprite6, sprite, text4, text8, text10, text11, taille2, symboleJ1, symboleJ2, sprite2, sprite3, Menu,text0);
							}
							if (clientDecision == "Non" || clientDecision == "non") {
								Server(port, joueur, x, y, listener, socket, Carte, tab, window, rectangle2, sprite5, sprite7, sprite6, sprite, text4, text8, text10, text11, taille2, symboleJ1, symboleJ2, sprite2, sprite3, Menu,text0);
							}
						}
						else {
							if (clientDecision == "Non" || clientDecision == "non") {
								Server(port, joueur, x, y, listener, socket, Carte, tab, window, rectangle2, sprite5, sprite7, sprite6, sprite, text4, text8, text10, text11, taille2, symboleJ1, symboleJ2, sprite2, sprite3, Menu,text0);
							}
							if (clientDecision == "Oui" || clientDecision == "oui") {
								Client(port, joueur, x, y, listener, socket, Carte, tab, window, rectangle2, sprite5, sprite7, sprite6, sprite, text4, text8, text10, text11, taille2, symboleJ1, symboleJ2, sprite2, sprite3, Menu,text0);
							}
						}
						if (aJouer == 1 && lan==0) {//permet de vérifier si un coup à été joué
							//Sleep(200);
							Carte.Jouer(tab, x, y, joueur);
						}
						if (lan == 0) {
							if (joueur == 2) {
								joueur = 1;
							}
							else {
								joueur++;
							}
						}
						//On change le nom du joueur afin d'indiquer quel joueur doit jouer
						if (joueur == 1) {
							text0.setString(nomJ1 + " Turn");
						}
						else {
							text0.setString(nomJ2 + " Turn");
						}
						if (game != 3) {
							game = Carte.Gagnant(tab,x,y);
						}
					}
					sf::Text text9;
					Menu.CreationTexte(text9, font,88," ",sf::Color::Black, (float)(window.getSize().x / 2), (float)(window.getSize().y / 2));
					if (game == 1) {
						text9.setString(nomJ1+" Won");
					}
					else if(game==2){
						text9.setString(nomJ2 + " Won");
					}
					else if (game == 3) {
						break;
					}
					text5.setString("Memes configs ?");
					text6.setString("Oui ");
					text6.setFillColor(sf::Color::Black);
					text7.setString("Non ");
					text7.setFillColor(sf::Color::Black);
					if (playmusic == 1) {
						music.stop();
					}
					if (game == 1 || game == 2) {
						Menu.AnimationWin(window, text9);
					}
					while (game == 1 || game == 2 || game==4) {
						sf::Event event;
						while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
								window.close();
						}
						x = 2;
						y = 2;
						window.clear();
						//Draw fond d'écran
						window.draw(rectangle2);
						window.draw(sprite5);
						window.draw(sprite7);
						window.draw(sprite);
						window.draw(text4);
						window.draw(text5);
						window.draw(text6);
						if (lan == 0) {
							window.draw(text7);
						}
						x2 = 1;
						y2 = 1;
						Menu.AfficherLigneEtPions(window, taille2, tab, x2, y2, symboleJ1, symboleJ2, sprite2, sprite3);
						window.display();
						text4.setFillColor(sf::Color::Black);
						text6.setFillColor(sf::Color::Black);
						play = 3;
						if (game == 1) {

							scoreJ1++;
						}
						else if (game == 2) {
							scoreJ2++;//J2 signifie soit bot soit joueur 2
						}
						while (play == 3) {
							sf::Event event;
							while (window.pollEvent(event))
							{
								sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
								if (event.type == sf::Event::MouseButtonPressed)//modifier ailleurs
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && (unsigned)localPosition.y >= window.getSize().y / 1.23 && lan==0) {
											boutton = 0;
											game = 3;
											play = 1;
											scoreJ1 = 0;
											scoreJ2 = 0;
											if (playmusic == 1) {
												music.play();//On démarre la musique
												music.setLoop(true);
											}
											break;
										}
										//On rejoue avec les mêmes configs
										if ((unsigned)localPosition.x <= window.getSize().x / 1.2 && (unsigned)(localPosition.x) >= window.getSize().x / 2 && (unsigned)localPosition.y <= window.getSize().y / 1.15 && (unsigned)localPosition.y >= window.getSize().y / 1.3) {
											boutton = 1;
											game = 4;
											play = 0;
											if (playmusic == 1) {
												music.play();//On démarre la musique
												music.setLoop(true);
											}
											break;
										}
										//Retour
										if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1 && localPosition.y >= window.getSize().y / 1.3) {
											boutton = 0;
											game = 3;
											play = 1;
											lan = 0;
											clientDecision = " ";
											scoreJ1 = 0;
											scoreJ2 = 0;
											nbDejoueurs = 1;
											break;

										}

									}
								}
							}
						}
						game = 0;
					}
				}
			}
			//Si selection multijoueur
			if (boutton == 2) {
				nbDejoueurs = 2;
				bot = -1;
				boutton = 1;
			}
			//Si selection menu option
			if (boutton == 3) {
				Menu.Menuoption(window,font,boutton,playmusic,fond,figure1,figure2,botsave,music,bot);
			}
			//Si selection quitter
			if (boutton == 4) {
				return 0;
			}
			//Si selection mode lan
			if (boutton == 5) {//On crée le mode lan
				clicbarre = 0;
				sf::Text text;
				Menu.CreationTexte(text, font, 44, "Retour", sf::Color::Black, (float)(window.getSize().x / 15), (float)(window.getSize().y / 1.25));
				sf::Text text2;
				Menu.CreationTexte(text2, font, 44, "Client ?('oui' pour client 'non' pour serveur) :", sf::Color::Black, (float)(window.getSize().x / 3), (float)(window.getSize().y / 1.25));
				sf::Text text3;
				Menu.CreationTexte(text3, font, 44, "Connected", sf::Color::Black, (float)(window.getSize().x / 3), (float)(window.getSize().y / 2));
				sf::Texture texture4;
				if (!texture4.loadFromFile("fondlan.png"))
				{
					// erreur...
				}
				sf::Sprite sprite4;
				sprite4.setTexture(texture4);
				sprite4.scale(window.getSize().x / 1024.f, window.getSize().y / 800.f);/// Redimensionnement
				sf::RectangleShape rectangle(sf::Vector2f((float)(window.getSize().x / 3.5), (float)(window.getSize().y / 15.f)));
				rectangle.setFillColor(sf::Color::Black);
				rectangle.setPosition((float)(window.getSize().x / 1.5), (float)(window.getSize().y / 1.1));
				sf::Text text9;
				Menu.CreationTexte(text9, font, 44, "", sf::Color::White, (float)(window.getSize().x / 1.5), (float)(window.getSize().y / 1.11));
				sf::Event event;
				tailleEnTexte = " ";
				nbdecardansstring = 0;
				clientDecision = " ";
				game = 1;
				//On demande si le pc est client ou serveur
				while (clientDecision != "oui" && clientDecision != "non") {
					while (window.pollEvent(event))
					{
						sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
						if (event.type == sf::Event::MouseButtonReleased)//modifier ailleurs
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1 && localPosition.y >= window.getSize().y / 1.3) {
									game = 3;
									boutton = 0;
									break;

								}
								if (localPosition.x <= window.getSize().x / 1.15 && localPosition.x >= window.getSize().x / 1.5 && localPosition.y <= window.getSize().y / 1.03 && localPosition.y >= window.getSize().y / 1.1) {
									clicbarre = 1;
									tailleEnTexte.at(nbdecardansstring) = '|';
									tempsSave += elapsed_seconds;
									start = std::chrono::system_clock::now();
								}
							}
						}
						if (clicbarre == 1) {
							end = std::chrono::system_clock::now();
							elapsed_seconds = (int)(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());//On obtient le temps depuis le start
							if (elapsed_seconds > 0.5 && tailleEnTexte.at(nbdecardansstring) == '|') {//Si cela fais plus de 0.5 seconde on enlève 
								tailleEnTexte.at(nbdecardansstring) = ' ';
								start = std::chrono::system_clock::now();
							}
							else if (elapsed_seconds > 0.5) {//Si cela fais plus de 1 seconde on ajoute
								tailleEnTexte.at(nbdecardansstring) = '|';
								start = std::chrono::system_clock::now();
							}

						}
						Menu.WriteResponseServeur(event, clicbarre, tailleEnTexte, nbdecardansstring,clientDecision);
						text9.setString(tailleEnTexte);
						if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && (unsigned)localPosition.y >= window.getSize().y / 1.3) {
							text.setFillColor(sf::Color::Red);
						}
						else {
							text.setFillColor(sf::Color::Black);
						}
						window.clear();
						//Draw fond d'écran
						window.draw(sprite4);
						window.draw(rectangle);
						window.draw(text);
						window.draw(text2);
						window.draw(text9);
						window.display();
						for (unsigned int i = 0; i < clientDecision.size(); i++) {
							clientDecision[i] = tolower(clientDecision[i]);
						}
					}
					if (game == 3) {
						break;
					}
				}
				if (game == 3) {
					break;
				}

				clicbarre = 0;
				tailleEnTexte = " ";
				nbdecardansstring = 0;
				//Si le pc est client on demande l'adresse ip du serveur
				if (clientDecision == "oui") {
					text2.setString("Adresse du serveur :");
					// Ask for the server address
					while (server == sf::IpAddress::None)
					{
						while (window.pollEvent(event))
						{
							sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
							if (event.type == sf::Event::MouseButtonReleased)//modifier ailleurs
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1 && localPosition.y >= window.getSize().y / 1.3) {
										game = 3;
										boutton = 0;
										break;

									}
									if (localPosition.x <= window.getSize().x / 1.15 && localPosition.x >= window.getSize().x / 1.5 && localPosition.y <= window.getSize().y / 1.03 && localPosition.y >= window.getSize().y / 1.1) {
										clicbarre = 1;
										tailleEnTexte.at(nbdecardansstring) = '|';
										tempsSave += elapsed_seconds;
										start = std::chrono::system_clock::now();
									}
								}
							}
							if (clicbarre == 1) {
								end = std::chrono::system_clock::now();
								elapsed_seconds = (int)(std::chrono::duration_cast<std::chrono::seconds>(end - start).count());//On obtient le temps depuis le start
								if (elapsed_seconds > 0.5 && tailleEnTexte.at(nbdecardansstring) == '|') {//Si cela fais plus de 0.5 seconde on enlève 
									tailleEnTexte.at(nbdecardansstring) = ' ';
									start = std::chrono::system_clock::now();
								}
								else if (elapsed_seconds > 0.5) {//Si cela fais plus de 1 seconde on ajoute
									tailleEnTexte.at(nbdecardansstring) = '|';
									start = std::chrono::system_clock::now();
								}

							}
							Menu.WriteIpServeur(event, clicbarre, tailleEnTexte, nbdecardansstring, server);
							text9.setString(tailleEnTexte);
							if ((unsigned)localPosition.x <= window.getSize().x / 5 && (unsigned)localPosition.x >= window.getSize().x / 100 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && (unsigned)localPosition.y >= window.getSize().y / 1.3) {
								text.setFillColor(sf::Color::Red);
							}
							else {
								text.setFillColor(sf::Color::Black);
							}
							window.clear();
							//Draw fond d'écran
							window.draw(sprite4);
							window.draw(rectangle);
							window.draw(text);
							window.draw(text2);
							window.draw(text9);
							window.display();
						}
						if (game == 3) {
							break;
						}
					}
					if (game == 3) {
						break;
					}
					window.clear();
					//Draw fond d'écran
					window.draw(sprite4);
					window.display();
					// Connect to the server
					if (socket.connect(server, port) != sf::Socket::Done)
						break;
					window.clear();
					//Draw fond d'écran
					window.draw(sprite4);
					window.draw(text3);
					window.display();
					const char out[] = " ";
					if (socket.send(out, sizeof(out)) != sf::Socket::Done)
						return 0;

					// Receive a message back from the client
					char in[128];
					std::size_t received;
					if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
						return 0;
					modeDeJeu = in[0];
				}
			
			if ( clientDecision == "non") {
				sf::Text text5;
				Menu.CreationTexte(text5, font, 44, "Mode de jeu :", sf::Color::Black, (float)(window.getSize().x / 5), (float)(window.getSize().y / 1.25));
				sf::Text text6;
				Menu.CreationTexte(text6, font, 44, "Puissance 5(Morpion) ", sf::Color::Black, (float)(window.getSize().x / 2), (float)(window.getSize().y / 1.25));
				sf::Text text7;
				Menu.CreationTexte(text7, font, 44, "Gomoku ", sf::Color::Black, (float)(window.getSize().x / 2), (float)(window.getSize().y / 1.1));
				/// Launch a server, wait for an incoming connection
				//Affichage de l'ip pour le client
				string ip = sf::IpAddress::getLocalAddress().toString();
				text3.setString("Ip :"+ip+" Waiting for connections...");
				// Listen to the given port for incoming connections
				if (listener.listen(port) != sf::Socket::Done)
					return 0;
				window.clear();
				//Draw fond d'écran
				window.draw(sprite4);
				window.draw(text3);
				window.display();
				// Wait for a connection
				if (listener.accept(socket) != sf::Socket::Done)
					break ;
				text3.setString("Connected");
				modeDeJeu = 0;
				while (modeDeJeu == 0) {
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::MouseButtonReleased)
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window est un sf::Window
								if ((unsigned)localPosition.x <= window.getSize().x / 1.2 && (unsigned)localPosition.x >= window.getSize().x / 2 && (unsigned)localPosition.y <= window.getSize().y / 1.1 && (unsigned)localPosition.y >= window.getSize().y / 1.35) {
									modeDeJeu = 1;
									break;
								}
								if ((unsigned)localPosition.x <= window.getSize().x / 1.2 && (unsigned)localPosition.x >= window.getSize().x / 2 && (unsigned)localPosition.y <= window.getSize().y / 1 && (unsigned)localPosition.y > window.getSize().y / 1.1) {
									modeDeJeu = 2;
									break;
								}
							}
						}
						window.clear();
						//Draw fond d'écran
						window.draw(sprite4);
						window.draw(text3);
						window.draw(text5);
						window.draw(text6);
						window.draw(text7);
						window.display();
					}
				}
				char x3 = modeDeJeu;
				const char out[1] = { x3 };
				if (socket.send(out, sizeof(out)) != sf::Socket::Done)
					return 0;
				std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;
				// Receive a message back from the client
				char in[128];
				std::size_t received;
				if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
					return 0;
			}
			//Mode de jeu égal à local
			lan = 1;
			joueur = 1;
			boutton = 1;
			taille2 = 20;
			nbDejoueurs = 1;
			if (clientDecision == "non") {
				nomJ1 = "Your";
				nomJ2 = "His";
			}
			else {
				nomJ2 = "Your";
				nomJ1 = "His";
			}
			}
		}
	}

	return 0;
}
