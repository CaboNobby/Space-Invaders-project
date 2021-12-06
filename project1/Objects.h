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
		if (!porongabuffer.loadFromFile("data/poronga.wav"))
			assert(false);
		poronga.setBuffer(porongabuffer);
		if (!explosionbuffer.loadFromFile("data/explosion.ogg"))
			assert(false);
		explosion.setBuffer(explosionbuffer);
	};
	void Update();
	bool capullo = false;
private:
	GD& cgd;
	float xpeed = 0.3f;
	float timesDefeated = 0;
	int enemieskilled = 44;
	int enemy = 4;
	int xEdge = 0;
	int yEdge = 0;
	int xMaxEdge = 800;
	int collision = 550;
	bool negative = false;
	bool colliding = false;
	sf::Vector2f newBulletPos;
	sf::Sound poronga;
	sf::SoundBuffer porongabuffer;
	sf::Sound explosion;
	sf::SoundBuffer explosionbuffer;
};
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
	int lowestButton = 250;
	int highestButton = 400;
};
class Spaceship {
 public:
	 Spaceship(GD& gd) :sgd(gd){ sgd.spaceship.setPosition(sgd.shipxpos, 550); 
	  sgd.bullet.setPosition(sgd.shipxpos + 6, 550);
	  if (!playertxt.loadFromFile("data/SpaceInvaders.png"))
		  assert(false);
	 };
	void Render();
 private:
	 GD& sgd;
	 sf::Texture playertxt;
};
void GameController::Init() {
	if (!tiritobuffer.loadFromFile("data/chuk.wav"))
		assert(false);
	tirito.setBuffer(tiritobuffer);
}
void Spaceship::Render() {
	sgd.spaceship.setTexture(playertxt);
	sgd.spaceship.setTextureRect(sf::IntRect(67, 0, 10, 14));
	sgd.spaceship.setScale(2, 2);
	sgd.pWindow->draw(sgd.spaceship);
	sgd.bullet.setTexture(playertxt);
	sgd.bullet.setTextureRect(sf::IntRect(38, 0, 2, 14));
	sgd.bullet.setScale(2, 2);
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
			newBulletPos.y += 1.8f;
		cgd.enemyBullet.setPosition(newBulletPos.x,newBulletPos.y);
		if (newBulletPos.y >= 600)
			cgd.enemyShot = false;
		if (newBulletPos.x >= cgd.spaceship.getPosition().x && newBulletPos.x < cgd.spaceship.getPosition().x + cgd.spaceship.getGlobalBounds().width && newBulletPos.y >= 540) {
			cgd.enemyShot = false;
			cgd.points -= 50;
		}
		if (cgd.spaceship.getPosition().x > newBulletPos.x && newBulletPos.x + cgd.enemyBullet.getGlobalBounds().width >= cgd.spaceship.getPosition().x && newBulletPos.y >= 540) {
			cgd.enemyShot = false;
			cgd.points -= 50;
		}
		if (cgd.spaceship.getPosition().x < xEdge)
			cgd.shipxpos = 0;
		if (cgd.spaceship.getPosition().x > GDC::SCREEN_RES.x - cgd.spaceship.getGlobalBounds().width)
			cgd.shipxpos = GDC::SCREEN_RES.x - cgd.spaceship.getGlobalBounds().width;
		if (cgd.bullet.getPosition().y < yEdge) {
			cgd.ypos = 540;
			cgd.shooting = false;
		}
		if (negative == false && cgd.paused == false)
			cgd.xpeed += xpeed;
		else if (negative == true && cgd.paused == false)
			cgd.xpeed -= xpeed;
		cgd.spr = 0;
		for (int enemyType(0); enemyType < enemy; enemyType++) {
			for (int onScreen(0); onScreen < cgd.enemyNumber; onScreen++) {
				if (cgd.enemyspr[onScreen + cgd.spr].getPosition().x > cgd.bullet.getPosition().x && (cgd.bullet.getPosition().x + cgd.bullet.getGlobalBounds().width) >= (cgd.enemyspr[onScreen + cgd.spr].getPosition().x - cgd.enemyspr[onScreen + cgd.spr].getGlobalBounds().width) && (cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getPosition().y) && (cgd.enemyspr[onScreen + cgd.spr].getPosition().y - cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getRadius())) {
					if (cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent && cgd.shooting != false) {
						cgd.shooting = false;
						explosion.play();
						cgd.enemyspr[onScreen + cgd.spr].setColor(sf::Color::Transparent);
						cgd.ypos = 540;
						cgd.enemies++;
						cgd.points += 10;
					}
				}
				if (cgd.enemyspr[onScreen + cgd.spr].getPosition().x < cgd.bullet.getPosition().x && (cgd.bullet.getPosition().x) <= (cgd.enemyspr[onScreen + cgd.spr].getPosition().x + cgd.enemyspr[onScreen + cgd.spr].getGlobalBounds().width) && (cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getPosition().y) && (cgd.enemyspr[onScreen + cgd.spr].getPosition().y - cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getRadius())) {
					if (cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent && cgd.shooting != false) {
						cgd.shooting = false;
						explosion.play();
						cgd.enemyspr[onScreen + cgd.spr].setColor(sf::Color::Transparent);
						cgd.ypos = 540;
						cgd.enemies++;
						cgd.points += 10;
					}
				}
				if ((cgd.enemyspr[onScreen + cgd.spr].getPosition().x + cgd.enemyspr[onScreen + cgd.spr].getGlobalBounds().width) > xMaxEdge && cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent) {
					negative = true;
					if (colliding == false && cgd.paused == false) {
						cgd.newypos += 50;
						colliding = true;
						xpeed += 0.1f;
					}
				}
				if (cgd.enemyspr[onScreen + cgd.spr].getPosition().x < xEdge +10 && cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent) {
					negative = false;
					if (colliding == true && cgd.paused == false) {
						cgd.newypos += 50;
						colliding = false;
						xpeed += 0.1f;
					}
				}
				if (cgd.enemyspr[onScreen + cgd.spr].getPosition().y >= collision && cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent) {
					capullo = true;
					cgd.newypos = 0;
					cgd.enemies = 44;
					cgd.paused = true;
					poronga.play();
				}
			}
			cgd.spr += 11;
		}
		if (cgd.enemies >= enemieskilled) {
			cgd.newypos = 0;
			cgd.xpos = 0;
			if (capullo == true) {
				cgd.xpeed = 0;
				xpeed =0.3f;
			}
			else {
				timesDefeated += 0.1f;
				xpeed = 0.3f + timesDefeated;
				cgd.xpeed = 0;
			}
			cgd.paused = true;
			cgd.resetColor = true;
		}
	}
}
class enemy {
public:
	enemy(GD& eGD) :egd(eGD){
		if (!enemytxt.loadFromFile("data/SpaceInvaders.png"))
			assert(false);
	};
	void RenderEnemies();
	void Colour();
	void Init();
private:
	GD& egd;
	sf::Texture enemytxt;
	int noEnemies = 0;
	int randomNumber;
	sf::IntRect micum{ 35, 19, 6, 10 };
	
};
void::enemy::Init() {
	egd.enemyBullet.setTexture(enemytxt);
	egd.enemyBullet.setTextureRect(micum);
	egd.enemyBullet.setScale(3, 3);
}
void::enemy::Colour() {
	if (egd.resetColor == true) {
		for (egd.enemies; egd.enemies > noEnemies; egd.enemies--) {
			egd.enemyspr[egd.enemies - 1].setColor(sf::Color(154, 217, 65));
		}
		egd.resetColor = false;
	}
}
void::enemy::RenderEnemies()
{
	if(egd.enemyShot !=true)
	randomNumber = rand() % 11;
	int y = 0;
	int enemyNumber= 4;
	egd.spr = 0;
	for (int enemyType(0); enemyType < enemyNumber; enemyType++) {
		for ( int onScreen(0); onScreen < egd.enemyNumber; onScreen++) {
			egd.enemyspr[onScreen + egd.spr].setTexture(enemytxt);
			egd.enemyspr[onScreen + egd.spr].setScale(3, 3);
			egd.enemyspr[onScreen + egd.spr].setTextureRect(egd.rect[enemyType]);
			egd.enemyspr[onScreen + egd.spr].setPosition(egd.xpos + egd.xpeed, y + egd.newypos);
			egd.circle[onScreen + egd.spr].setRadius(12);
			egd.circle[onScreen + egd.spr].setFillColor(sf::Color::Transparent);
			egd.circle[onScreen + egd.spr].setOutlineColor(sf::Color::Red);
			egd.circle[onScreen + egd.spr].setOutlineThickness(1);
			egd.circle[onScreen + egd.spr].setPosition(egd.xpos+4 + egd.xpeed, y + egd.newypos);
			egd.xpos += 50;
			egd.pWindow->draw(egd.circle[onScreen + egd.spr]);
			egd.pWindow->draw(egd.enemyspr[onScreen + egd.spr]);
		}
		if (egd.spr >= 33) {
			egd.bulletPos = egd.enemyspr[egd.spr + randomNumber].getPosition();
			egd.pWindow->draw(egd.enemyBullet);
		}
		egd.spr += 11;
		y += 50;
		egd.xpos = 50;
	}
}