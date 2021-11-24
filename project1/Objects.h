#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"

class spaceship {
 public:
	 spaceship(GD& gd) :sgd(gd){};
	 void Update();
	void Render();
	void RenderEnemys();
	void Init();
	bool capullo = false;
 private:
	 sf::Sprite spaceShip;
	 sf::Sprite bullet;
	 float xpos = 400.f;
	 float ypos = 530.f;
	 int lastpos;
	 bool shooting = false;
	 GD& sgd;
	 sf::CircleShape circle[44];
	 sf::Texture enemytxt;
	 sf::Sprite enemyspr[44];
	 sf::IntRect rect[4] = { (sf::IntRect(2, 3, 12, 10)),(sf::IntRect(19, 3, 12, 10)),(sf::IntRect(2, 19, 11, 10)),(sf::IntRect(19, 19, 11, 10)) };
	 int enemyNumber = 11;
	 int x2pos = 50;
	 int spr = 0;
	 float xpeed = 0;
	 bool negative;
	 int newypos = 0;
	 int enemieskilled = 0;
};
void spaceship::Init() {
	spaceShip.setPosition(xpos, 550);
	bullet.setPosition(xpos + 6, 500);
}
void spaceship::Render() {

	sf :: Texture playertxt;
	if (!playertxt.loadFromFile("data/SpaceInvaders.png"))
		assert(false);
	spaceShip.setTexture(playertxt);
	spaceShip.setTextureRect(sf::IntRect(67, 0, 10, 14));
	spaceShip.setScale(2, 2);
	sgd.pWindow->draw(spaceShip);
	bullet.setTexture(playertxt);
	bullet.setTextureRect(sf::IntRect(38, 0, 2, 14));
	bullet.setScale(2, 2);
	sgd.pWindow->draw(bullet);
	int y = 50;
	spr = 0;
	if (!enemytxt.loadFromFile("data/SpaceInvaders.png"))
		assert(false);
	for (int enemyType(0); enemyType < 4; enemyType++) {
		for (int onScreen(0); onScreen < enemyNumber; onScreen++) {
			enemyspr[onScreen + spr].setTexture(enemytxt);
			enemyspr[onScreen + spr].setScale(3, 3);
			enemyspr[onScreen + spr].setTextureRect(rect[enemyType]);
			enemyspr[onScreen + spr].setPosition(x2pos + xpeed, y + newypos);
			circle[onScreen + spr].setRadius(12);
			circle[onScreen + spr].setFillColor(sf::Color::Transparent);
			circle[onScreen + spr].setOutlineColor(sf::Color::Red);
			circle[onScreen + spr].setOutlineThickness(1);
			circle[onScreen + spr].setPosition(x2pos + 4 + xpeed, y + newypos);
			x2pos += 50;
			sgd.pWindow->draw(circle[onScreen + spr]);
			sgd.pWindow->draw(enemyspr[onScreen + spr]);
		}
		spr += 11;
		y += 50;
		x2pos = 50;
	}
}
void spaceship::Update() {
	bullet.setPosition(lastpos, ypos);
	if (shooting != true)
		bullet.setColor(sf::Color::Transparent);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		xpos -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		xpos += 1;
	}
	if (spaceShip.getPosition().x < 0)
		xpos = 0;
	if (spaceShip.getPosition().x > GDC::SCREEN_RES.x - spaceShip.getGlobalBounds().width)
		xpos = GDC::SCREEN_RES.x - spaceShip.getGlobalBounds().width;
	if (bullet.getPosition().y < 0) {
		ypos = 540;
		shooting = false;
	}	spaceShip.setPosition(xpos, 550);
	if(shooting!= true)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		shooting = true;
		lastpos = xpos;
	}
	if (shooting == true){
		bullet.setColor(sf::Color(244,255,191));
		ypos-= 5;
    }
	spr = 11;
	for (int enemyType(0); enemyType < 4; enemyType++) {
		if ((enemyspr[spr].getPosition().x + enemyspr[spr].getGlobalBounds().width) > 800) {
			x2pos = 800;
			newypos += 50;
			negative = true;
		}
		spr += 10;
	}
	spr = 1;
	for (int enemyType(0); enemyType < 4; enemyType++) {
		if (enemyspr[spr].getPosition().x < 10) {
			x2pos = 0;
			negative = false;
			newypos += 50;
		}
		spr += 10;
	}
	if (negative == false)
		xpeed += 0.25f;
	else
		xpeed -= 0.25f;
	spr = 0;
	for (int enemyType(0); enemyType < 4; enemyType++) {
		for (int onScreen(0); onScreen < enemyNumber; onScreen++) {
			if (enemyspr[onScreen+spr].getPosition().x > bullet.getPosition().x && (bullet.getPosition().x + bullet.getGlobalBounds().width) >= (enemyspr[onScreen +spr].getPosition().x - enemyspr[onScreen +spr].getGlobalBounds().width) && (bullet.getPosition().y < circle[onScreen +spr].getPosition().y) && (enemyspr[onScreen +spr].getPosition().y - bullet.getPosition().y < circle[onScreen +spr].getRadius())) {
				if (enemyspr[onScreen + spr].getColor() != sf::Color::Transparent && shooting != false) {
					shooting = false;
					enemyspr[onScreen + spr].setColor(sf::Color::Transparent);
					ypos = 540;
					enemieskilled++;
				}
			}
			if (enemyspr[onScreen +spr].getPosition().x < bullet.getPosition().x && (bullet.getPosition().x) <= (enemyspr[onScreen +spr].getPosition().x + enemyspr[onScreen +spr].getGlobalBounds().width) && (bullet.getPosition().y < circle[onScreen +spr].getPosition().y) && (enemyspr[onScreen+spr].getPosition().y - bullet.getPosition().y < circle[onScreen +spr].getRadius())) {
				if (enemyspr[onScreen + spr].getColor() != sf::Color::Transparent && shooting != false) {
					shooting = false;
					enemyspr[onScreen + spr].setColor(sf::Color::Transparent);
					ypos = 540;
					enemieskilled++;
				}
			}
			if (enemyspr[onScreen + spr].getPosition().y >= 540) {
				capullo = true;
				newypos = 0;
			}
			if(enemieskilled>=44)
			for (enemieskilled;enemieskilled > 0; enemieskilled--) {
				enemyspr[enemieskilled].setColor(sf::Color(154, 217, 65));
					newypos = 0;
			}
		}
		spr += 11;
	}
}
class enemy {
public:
	enemy(GD& eGD) :egd(eGD){};
	void RenderEnemies();
	void Update();
private:
	GD& egd;
	sf::CircleShape circle[44];
	sf::Texture enemytxt;
	sf::Sprite enemyspr[44];
	sf::IntRect rect[4] = { (sf::IntRect(2, 3, 12, 10)),(sf::IntRect(19, 3, 12, 10)),(sf::IntRect(2, 19, 11, 10)),(sf::IntRect(19, 19, 11, 10)) };
	int enemyNumber = 11;
	int xpos = 50;
	int spr = 0;
	float xpeed = 0;
	bool negative;
	int newypos = 0;
};
void::enemy::RenderEnemies()
{
	/*int y = 50;
	spr = 0;
	if (!enemytxt.loadFromFile("data/SpaceInvaders.png"))
		assert(false);
	for (int enemyType(0); enemyType < 4; enemyType++) {
		for ( int onScreen(0); onScreen < enemyNumber; onScreen++) {
			enemyspr[onScreen + spr].setTexture(enemytxt);
			enemyspr[onScreen + spr].setScale(3, 3);
			enemyspr[onScreen + spr].setTextureRect(rect[enemyType]);
			enemyspr[onScreen + spr].setPosition(xpos + xpeed, y +newypos);
			circle[onScreen +spr].setRadius(12);
			circle[onScreen + spr].setFillColor(sf::Color::Transparent);
			circle[onScreen + spr].setOutlineColor(sf::Color::Red);
			circle[onScreen + spr].setOutlineThickness(1);
			circle[onScreen + spr].setPosition(xpos+4 +xpeed, y +newypos);
			xpos += 50;
			egd.pWindow->draw(circle[onScreen + spr]);
			egd.pWindow->draw(enemyspr[onScreen +spr]);
		}
		spr += 11;
		y += 50;
		xpos = 50;
	}*/
}
void enemy::Update() {
	
	/*spr = 11;
	for (int enemyType(0); enemyType < 4; enemyType++) {
	 if ((enemyspr[spr].getPosition().x + enemyspr[spr].getGlobalBounds().width) > 800 ) {
    	xpos = 800;
		newypos += 50;
	    negative = true;
	 }
		spr += 10;
	}
	spr = 1;
	for (int enemyType(0); enemyType < 4; enemyType++) {
	 if (enemyspr[spr].getPosition().x < 10) {
		xpos = 0;
		negative = false;
		newypos += 50;
	 }
		spr += 10;
	}
	if (negative == false)
		xpeed+=0.5f;
	else
		xpeed-=0.5f;*/
}