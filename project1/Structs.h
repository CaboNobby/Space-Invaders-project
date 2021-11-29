#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"

//dimensions in 2D that are whole numbers
struct Vec2i
{
	int x, y;
};

//dimensions in 2D that are floating point numbers
struct Vec2f
{
	float x, y;
};


//GDC="GameDataConstants" - a box for all  magic numbers
namespace GDC
{
	const Vec2i SCREEN_RES{ 800,600 };	//desired resolution
	const char ESCAPE_KEY{ 27 };		//ASCII code
	const sf::Uint32 ASCII_RANGE{ 127 };//google an ASCII table, after 127 we don't care
	const float PLAY_SPIN_SPD{ 100.f };	//how fast to spin
	const char ENTER_KEY{ 13 };
	const char NO_KEY = 0;
}

//keep important shared information "GameData" in one accessible object and pass it around
struct GD
{
	sf::Font font;				//a shared font to use everywhere
	sf::RenderWindow* pWindow;	//can't render anything without this
	sf::Sprite spaceShip;
	sf::Sprite bullet;
	sf::Sprite enemyspr[44];
	sf::IntRect rect[4] = { (sf::IntRect(2, 3, 12, 10)),(sf::IntRect(19, 3, 12, 10)),(sf::IntRect(2, 19, 11, 10)),(sf::IntRect(19, 19, 11, 10)) };
	sf::CircleShape circle[44];
	int enemyNumber = 11;
	int newypos = 0;
	float xpos = 50;
	int spr = 0; // the sprite we are currently in
	float xpeed = 0;
	/*string playerName;*/			//the player's name is needed by different objects
};
enum State {
	GAME_PLAYING,
	MAIN_MENU,
	GAME_OVER,
	EXIT
};
