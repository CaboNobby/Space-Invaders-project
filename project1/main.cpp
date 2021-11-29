#include <assert.h>
#include "SFML/Graphics.hpp"
#include "Structs.h"
#include "Objects.h"

using namespace std;
//Where the fun starts
class Game {
public:
	Game() :myspaceship(mgd),myenemy(mgd),mycollision(mgd) {
		mgd.pWindow = &window;
	};
	void Run();                                                 //Initialize the program
	void Render();
	void Update();
	void GameState();
	void GameOver();
	void Init();

private:
	State state = /*GAME_PLAYING*/MAIN_MENU;
	sf::RenderWindow window;
	sf::Event event;
	GD mgd;
	Collision mycollision;
	spaceship myspaceship;
	enemy myenemy;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Sprite goSprite;
	sf::Sprite menuSprite;
	char key = GDC::NO_KEY;//current key press 
};
void::Game::GameOver() {
	sf::Texture bgtxt;
	if (!bgtxt.loadFromFile("data/gameover.png"))
		assert(false);
	goSprite.setTexture(bgtxt);
	window.draw(goSprite);
}
void::Game::Init() {
	if (!bgTexture.loadFromFile("data/titlescreen.png"))
		assert(false);
	menuSprite.setTexture(bgTexture);
	window.draw(menuSprite);
}
void::Game::GameState() {
	switch (state) {
	case State::GAME_PLAYING:
		Render();
		mycollision.Update();
		break;
	case State::EXIT:
		window.close();
		break;
	case State::MAIN_MENU:
		Init();
		break;
	case State::GAME_OVER:
		GameOver();
		break;
	default:
		assert(false);
	}

}
void::Game::Update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		state = State::EXIT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		state = State::MAIN_MENU;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	state = State::GAME_PLAYING;
	if (mycollision.capullo == true) {
		state = State::GAME_OVER;
		mycollision.capullo = false;
	}
}
void Game::Render() {
	int tilesInX = 19;
	int tilesInY = 12;
	float x = 0;
	float y = 0;
	if (!bgTexture.loadFromFile("data/background.png"))
		assert(false);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(2, 2);
	for (int tiles(0); tiles < tilesInX; tiles++) {
		for (int ytiles(0); ytiles < tilesInY; ytiles++)
		{
			bgSprite.setPosition(64 * tiles, y);
			window.draw(bgSprite);
			y = y + 64;
		}
		y = 0;
	}
	myspaceship.Render();
	myenemy.RenderEnemies();
}

void Game::Run() {
	mycollision.Init();
	window.create(sf::VideoMode(GDC::SCREEN_RES.x, GDC::SCREEN_RES.y),"Space Invaders");
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			/*if (event.type == sf::Event::TextEntered)
				if (event.text.unicode < GDC::ASCII_RANGE) {
					TextEntered(static_cast<char>(event.text.unicode));
				}*/
		}
		window.clear();
		GameState();
		Update();
		/*myenemy.Update();*/
		window.display();
	}
}
int main()
{
	Game g;
	g.Run();
	return EXIT_SUCCESS;
}
