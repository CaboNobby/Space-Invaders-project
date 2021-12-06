#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"

//dimensions in 2D that are whole numbers
struct Vec2i
{
	int x, y;
};
//GDC="GameDataConstants" - a box for all  magic numbers
namespace GDC
{
	const Vec2i SCREEN_RES{ 800,600 };	//desired resolution
}

//keep important shared information "GameData" in one accessible object and pass it around
struct GD
{
	sf::Clock clock;
	sf::Font arcadeFont;
	sf::Font instructionsFont;
	sf::RenderWindow* pWindow;	//allows objects rendering
	sf::Sprite spaceship;
	sf::Text score;
	sf::Sprite bullet;
	sf::Sprite enemyBullet;
	sf::Sprite enemyspr[44];
	sf::IntRect rect[4] = { (sf::IntRect(2, 3, 12, 10)),(sf::IntRect(19, 3, 12, 10)),(sf::IntRect(2, 19, 11, 10)),(sf::IntRect(19, 19, 11, 10)) };
	sf::CircleShape circle[44];
	sf::Vector2f bulletPos;
	int enemyNumber = 11;
	int newypos = 0;  //For the aliens 
	int ptrypos = 250;
	int points = 0;
	int enemies = 0;
	float shipxpos = 400.f;
	int charcounter = 0;
	float rate = 0.15f; //For the keys input
	float xpos = 50;    //For the alien
	float ypos = 530.f; //For the bullet
	int spr = 0; // the sprite we are currently in
	float xpeed = 0; //Aliens speed on the x axis
	float deltatime;
	bool enemyShot = false;
	bool paused = true;
	bool shooting = false;
	bool resetColor = false;
};
//Group up the different states game has
enum State {
	GAME_PLAYING,
	GET_NAME,
	TITLE_SCREEN,
	GAME_INSTRUCTIONS,
	LEADER_BOARD,
	MAIN_MENU,
	GAME_OVER,
	EXIT
};
