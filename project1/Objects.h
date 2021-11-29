#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"
class Collision {
public:
	Collision(GD& gd) :cgd(gd) {};
	void Update();
	void Init();
	bool capullo = false;
private:
	GD& cgd;
	int lastpos;
	float x2pos = 400.f;
	bool shooting = false;
	float ypos = 530.f;
	int enemieskilled = 0;
	bool negative;
};
class spaceship {
 public:
	 spaceship(GD& gd) :sgd(gd){};
	void Render();
 private:
	 GD& sgd;
};
void Collision::Init() {
	cgd.spaceShip.setPosition(x2pos, 550);
	cgd.bullet.setPosition(x2pos + 6, 500);
}
void spaceship::Render() {

	sf :: Texture playertxt;
	if (!playertxt.loadFromFile("data/SpaceInvaders.png"))
		assert(false);
	sgd.spaceShip.setTexture(playertxt);
	sgd.spaceShip.setTextureRect(sf::IntRect(67, 0, 10, 14));
	sgd.spaceShip.setScale(2, 2);
	sgd.pWindow->draw(sgd.spaceShip);
	sgd.bullet.setTexture(playertxt);
	sgd.bullet.setTextureRect(sf::IntRect(38, 0, 2, 14));
	sgd.bullet.setScale(2, 2);
	sgd.pWindow->draw(sgd.bullet);
}
void Collision::Update() {
	cgd.bullet.setPosition(lastpos, ypos);
	if (shooting != true)
		cgd.bullet.setColor(sf::Color::Transparent);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		x2pos -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		x2pos += 1;
	}
	if (cgd.spaceShip.getPosition().x < 0)
		x2pos = 0;
	if (cgd.spaceShip.getPosition().x > GDC::SCREEN_RES.x - cgd.spaceShip.getGlobalBounds().width)
		x2pos = GDC::SCREEN_RES.x - cgd.spaceShip.getGlobalBounds().width;
	if (cgd.bullet.getPosition().y < 0) {
		ypos = 540;
		shooting = false;
	}	cgd.spaceShip.setPosition(x2pos, 550);
	if(shooting!= true)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		shooting = true;
		lastpos = x2pos;
	}
	if (shooting == true){
		cgd.bullet.setColor(sf::Color(244,255,191));
		ypos-= 5;
    }
	cgd.spr = 11;
	for (int enemyType(0); enemyType < 4; enemyType++) {
		if ((cgd.enemyspr[cgd.spr].getPosition().x + cgd.enemyspr[cgd.spr].getGlobalBounds().width) > 800) {
			cgd.xpos = 800;
			cgd.newypos += 50;
			negative = true;
		}
		cgd.spr += 10;
	}
	cgd.spr = 1;
	for (int enemyType(0); enemyType < 4; enemyType++) {
		if (cgd.enemyspr[cgd.spr].getPosition().x < 10) {
			cgd.xpos = 0;
			negative = false;
			cgd.newypos += 50;
		}
		cgd.spr += 10;
	}
	if (negative == false)
		cgd.xpeed += 0.5f;
	else
		cgd.xpeed -= 0.5f;
	cgd.spr = 0;
	for (int enemyType(0); enemyType < 4; enemyType++) {
		for (int onScreen(0); onScreen < cgd.enemyNumber; onScreen++) {
			if (cgd.enemyspr[onScreen+ cgd.spr].getPosition().x > cgd.bullet.getPosition().x && (cgd.bullet.getPosition().x + cgd.bullet.getGlobalBounds().width) >= (cgd.enemyspr[onScreen + cgd.spr].getPosition().x - cgd.enemyspr[onScreen + cgd.spr].getGlobalBounds().width) && (cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getPosition().y) && (cgd.enemyspr[onScreen + cgd.spr].getPosition().y - cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getRadius())) {
				if (cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent && shooting != false) {
					shooting = false;
					cgd.enemyspr[onScreen + cgd.spr].setColor(sf::Color::Transparent);
					ypos = 540;
					enemieskilled++;
				}
			}
			if (cgd.enemyspr[onScreen + cgd.spr].getPosition().x < cgd.bullet.getPosition().x && (cgd.bullet.getPosition().x) <= (cgd.enemyspr[onScreen + cgd.spr].getPosition().x + cgd.enemyspr[onScreen + cgd.spr].getGlobalBounds().width) && (cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getPosition().y) && (cgd.enemyspr[onScreen+ cgd.spr].getPosition().y - cgd.bullet.getPosition().y < cgd.circle[onScreen + cgd.spr].getRadius())) {
				if (cgd.enemyspr[onScreen + cgd.spr].getColor() != sf::Color::Transparent && shooting != false) {
					shooting = false;
					cgd.enemyspr[onScreen + cgd.spr].setColor(sf::Color::Transparent);
					ypos = 540;
					enemieskilled++;
				}
			}
			if (cgd.enemyspr[onScreen + cgd.spr].getPosition().y >= 540) {
				capullo = true;
				cgd.newypos = 0;
			}
			if(enemieskilled>=44)
			for (enemieskilled;enemieskilled > 0; enemieskilled--) {
				cgd.enemyspr[enemieskilled -1].setColor(sf::Color(154, 217, 65));
					cgd.newypos = 0;
			}
		}
		cgd.spr += 11;
	}
}
class enemy {
public:
	enemy(GD& eGD) :egd(eGD){};
	void RenderEnemies();
	void Update();
private:
	GD& egd;
	sf::Texture enemytxt;
};
void::enemy::RenderEnemies()
{
	int y = 50;
	egd.spr = 0;
	if (!enemytxt.loadFromFile("data/SpaceInvaders.png"))
		assert(false);
	for (int enemyType(0); enemyType < 4; enemyType++) {
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
		egd.spr += 11;
		y += 50;
		egd.xpos = 50;
	}
}