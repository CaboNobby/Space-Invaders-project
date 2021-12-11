#pragma once
#include <assert.h>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "stdlib.h"
using namespace std;
//Checks when the bullet collides with the aliens and when the aliens do so with the player
class Collision {
public:
	Collision(GD& gd) :cgd(gd) {
		if (!porongaBuffer.loadFromFile("data/poronga.wav"))
			assert(false);
		poronga.setBuffer(porongaBuffer);
		if (!explosionBuffer.loadFromFile("data/explosion.ogg"))
			assert(false);
		explosion.setBuffer(explosionBuffer);
	};
	void Update();
	bool  gameOver = false;
	bool quit = false;
private:
	void onCollisionWithEnemy();
	void onCollisionWithPlayer();
	GD& cgd;
	float xpeed = 0.1f;
	float timesDefeated = 0;
	int enemieskilled = 44;
	int enemy = 4;
	int xEdge = 0;
	int yEdge = 0;
	int xMaxEdge = 800;
	int collision = 550;
	int roundPoints = 50;
	bool negativeSpeed = false; //check aliens direction
	bool colliding = false;
	sf::Vector2f newBulletPos;
	sf::Sound poronga;
	sf::SoundBuffer porongaBuffer;
	sf::Sound explosion;
	sf::SoundBuffer explosionBuffer;
};
void::Collision::onCollisionWithPlayer() {
	if (cgd.lastAlien > 22)
		cgd.points -= 20;
	else
		cgd.points -= 50;
	cgd.enemyShot = false;
}
void::Collision::onCollisionWithEnemy() {

		cgd.shooting = false;
		explosion.play();
		cgd.yPos = 540;
		cgd.enemies++;
		cgd.points += 10;
	
}
//Its job is to manage game inputs
class GameController {
public:
	GameController(GD& gd) :gcd(gd) {}
	//Game's menu pointer movement
	void PointerMovement();
	void KeyHandler();
	void Init();
	void AskPlayerName();
	//Get player name
	void HandleInput(char);
	bool getName = false;
	string word;
private:
	GD& gcd;
	string space;
	sf::Sound tirito;
	sf::SoundBuffer tiritobuffer;
	int lastpos;
	/*string msg = "What is your name? \n";*/
	int MaxCharacter = 12;
	int lowestButton = 250;
	int highestButton = 400;
};
class Spaceship {
 public:
	 Spaceship(GD& gd) :sgd(gd){};
	void Render();
	void Init();
 private:
	 GD& sgd;
	 sf::Texture playerTexture;
};
void::Spaceship::Init() {
	if (!playerTexture.loadFromFile("data/SpaceInvaders.png"))
		assert(false);
	sgd.spaceship.setTexture(playerTexture);
	sgd.spaceship.setTextureRect(sf::IntRect(67, 0, 10, 14));
	sgd.spaceship.setScale(2, 2);
	sgd.bullet.setTexture(playerTexture);
	sgd.bullet.setTextureRect(sf::IntRect(38, 0, 2, 14));
	sgd.bullet.setScale(2, 2);
	sgd.bullet.setPosition(sgd.shipXPos + 6, 550);
	sgd.spaceship.setPosition(sgd.shipXPos, 550);
}
void Spaceship::Render() {
	sgd.pWindow->draw(sgd.spaceship);
	sgd.pWindow->draw(sgd.bullet);
}
void Collision::Update() {
	if (cgd.paused == false) {
		if (cgd.enemyShot != true) {
			newBulletPos.x = cgd.bulletPos.x + 5;
			newBulletPos.y = cgd.bulletPos.y + 10;
			cgd.enemyShot = true;
		}
		else
			newBulletPos.y += 0.8f;
		cgd.enemyBullet.setPosition(newBulletPos.x,newBulletPos.y);
		if (newBulletPos.y >= 600)
			cgd.enemyShot = false;
		//Collision between spaceship and enemy's bullet in case bullet x position is bigger
		if (newBulletPos.x >= cgd.spaceship.getPosition().x && newBulletPos.x < cgd.spaceship.getPosition().x + cgd.spaceship.getGlobalBounds().width && newBulletPos.y >= 540) 
			onCollisionWithPlayer();
		//Collision between spaceship and enemy's bullet in case spaceship x position is bigger
		if (cgd.spaceship.getPosition().x > newBulletPos.x && newBulletPos.x + cgd.enemyBullet.getGlobalBounds().width >= cgd.spaceship.getPosition().x && newBulletPos.y >= 540) 
			onCollisionWithPlayer();
		if (cgd.spaceship.getPosition().x < xEdge)
			cgd.shipXPos = 0;
		if (cgd.spaceship.getPosition().x > GDC::SCREEN_RES.x - cgd.spaceship.getGlobalBounds().width)
			cgd.shipXPos = GDC::SCREEN_RES.x - cgd.spaceship.getGlobalBounds().width;
		if (cgd.bullet.getPosition().y < yEdge) {
			cgd.yPos = 540;
			cgd.shooting = false;
		}
		if (negativeSpeed == false && cgd.paused == false)
			cgd.xpeed += xpeed;
		else if (negativeSpeed == true && cgd.paused == false)
			cgd.xpeed -= xpeed;
		cgd.spr = 0;
		for (int enemyType(0); enemyType < enemy; enemyType++) {
			for (int onScreen(0); onScreen < cgd.enemyNumber; onScreen++) {
				if (cgd.enemyspr[onScreen + cgd.spr].getPosition().x > cgd.bullet.getPosition().x && (cgd.bullet.getPosition().x + cgd.bullet.getGlobalBounds().width) >= (cgd.enemyspr[onScreen + cgd.spr].getPosition().x - cgd.enemyspr[onScreen + cgd.spr].getGlobalBounds().width) && (cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getPosition().y) && (cgd.enemyspr[onScreen + cgd.spr].getPosition().y - cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getRadius())) {
					if (cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent && cgd.shooting != false) {
						onCollisionWithEnemy();
						cgd.enemyspr[onScreen + cgd.spr].setColor(sf::Color::Transparent);
					}
				}
				if (cgd.enemyspr[onScreen + cgd.spr].getPosition().x < cgd.bullet.getPosition().x && (cgd.bullet.getPosition().x) <= (cgd.enemyspr[onScreen + cgd.spr].getPosition().x + cgd.enemyspr[onScreen + cgd.spr].getGlobalBounds().width) && (cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getPosition().y) && (cgd.enemyspr[onScreen + cgd.spr].getPosition().y - cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getRadius())) {
					if (cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent && cgd.shooting != false) {
						onCollisionWithEnemy();
						cgd.enemyspr[onScreen + cgd.spr].setColor(sf::Color::Transparent);
					}
				}
				if ((cgd.enemyspr[onScreen + cgd.spr].getPosition().x + cgd.enemyspr[onScreen + cgd.spr].getGlobalBounds().width) > xMaxEdge && cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent) {
					negativeSpeed = true;
					if (colliding == false && cgd.paused == false) {
						cgd.newYPos += 50;
						colliding = true;
						xpeed += 0.01f;
					}
				}
				if (cgd.enemyspr[onScreen + cgd.spr].getPosition().x < xEdge +10 && cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent) {
					negativeSpeed = false;
					if (colliding == true && cgd.paused == false) {
						cgd.newYPos += 50;
						colliding = false;
						xpeed += 0.01f;
					}
				}
				if (cgd.enemyspr[onScreen + cgd.spr].getPosition().y >= collision && cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent) {
					gameOver = true;
					cgd.newYPos = 0;
					cgd.enemies = 44;
					cgd.paused = true;
					poronga.play();
				}
			}
			cgd.spr += 11;
		}
		if (cgd.enemies >= enemieskilled) {
			cgd.newYPos = 0;
			cgd.xPos = 0;
			cgd.lastAlien = 44;
			if (gameOver == true) {
				cgd.xpeed = 0;
				xpeed =0.1f;
			}
			else if (gameOver != true  && quit != true){
				timesDefeated += 0.1f;
				xpeed = 0.1f + timesDefeated;
				cgd.xpeed = 0;
				cgd.points += roundPoints;
				roundPoints += 50;
			}
			else if (quit == true) {
				cgd.xpeed = 0;
				xpeed = 0.1f;
				quit = false;
			}
			cgd.paused = true;
			cgd.resetColor = true;
		}
	}
}
class Enemy {
public:
	Enemy(GD& eGD) :egd(eGD){
		if (!enemyTexture.loadFromFile("data/SpaceInvaders.png"))
			assert(false);
	};
	void RenderEnemies();
	void Colour();
	void Init();
private:
	GD& egd;
	sf::Texture enemyTexture;
	int noEnemies = 0;
	int randomNumber;
	int enemyNumber = 4;
	sf::IntRect bulletRect{ 35, 19, 6, 10 };
	
};
void::Enemy::Init() {
	egd.enemyBullet.setTexture(enemyTexture);
	egd.enemyBullet.setTextureRect(bulletRect);
	egd.enemyBullet.setScale(3, 3);
	for (int enemyType(0); enemyType < enemyNumber; enemyType++) {
		for (int onScreen(0); onScreen < egd.enemyNumber; onScreen++) {
			egd.enemyspr[onScreen + egd.spr].setTexture(enemyTexture);
			egd.enemyspr[onScreen + egd.spr].setScale(3, 3);
			egd.enemyspr[onScreen + egd.spr].setTextureRect(egd.enemyRect[enemyType]);
			egd.circle[onScreen + egd.spr].setRadius(12);
			egd.circle[onScreen + egd.spr].setFillColor(sf::Color::Transparent);
			egd.circle[onScreen + egd.spr].setOutlineColor(sf::Color::Red);
			egd.circle[onScreen + egd.spr].setOutlineThickness(1);
		}
		egd.spr += 11;
	}
}
void::Enemy::Colour() {
	if (egd.resetColor == true) {
		for (egd.enemies; egd.enemies > noEnemies; egd.enemies--) {
			egd.enemyspr[egd.enemies -1].setColor(sf::Color(154, 217, 65));
		}
		egd.resetColor = false;
		egd.enemyBullet.setColor(sf::Color(244, 255, 191));
	}
}
void::Enemy::RenderEnemies()
{
	int y = 0;
	//if(egd.enemyShot !=true)
	//lastAlien = rand() % 44;
	egd.spr = 0;
	for (int enemyType(0); enemyType < enemyNumber; enemyType++) {
		for ( int onScreen(0); onScreen < egd.enemyNumber; onScreen++) {
			egd.enemyspr[onScreen + egd.spr].setPosition(egd.xPos + egd.xpeed, y + egd.newYPos);
			egd.circle[onScreen + egd.spr].setPosition(egd.xPos+4 + egd.xpeed, y + egd.newYPos);
			egd.xPos += 50;
			egd.pWindow->draw(egd.circle[onScreen + egd.spr]);
			egd.pWindow->draw(egd.enemyspr[onScreen + egd.spr]);
		}
		egd.spr += 11;
		y += 50;
		egd.xPos = 50;
	}
	if (egd.enemyspr[egd.lastAlien].getColor() != sf::Color::Transparent) {
		egd.bulletPos = egd.enemyspr[egd.lastAlien].getPosition();
		egd.pWindow->draw(egd.enemyBullet);
	}
	else if (egd.lastAlien > 0) {
		egd.lastAlien--;
		egd.bulletPos = egd.enemyspr[egd.lastAlien].getPosition();
		if (egd.lastAlien < 23)
			egd.enemyBullet.setColor(sf::Color(255, 100, 100));
		egd.pWindow->draw(egd.enemyBullet);
	}
}