#pragma once
#include <assert.h>
#include <sstream>
#include "Structs.h"
#include "Objects.h"
#include "SFML/Graphics.hpp"
void::GameController::KeyHandler() {
	gcd.deltatime = gcd.clock.getElapsedTime().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && gcd.paused == false && gcd.deltatime > gcd.rate) {
		gcd.clock.restart();
		gcd.paused = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && gcd.paused == true && gcd.deltatime > gcd.rate) {
		gcd.paused = false;
		gcd.clock.restart();
	}
	if (gcd.paused == false) {
		gcd.bullet.setPosition(lastpos, gcd.ypos);
		gcd.spaceship.setPosition(gcd.shipxpos, 550);
		if (gcd.shooting != true)
			gcd.bullet.setColor(sf::Color::Transparent);
		else if (gcd.shooting == true) {
			gcd.bullet.setColor(sf::Color(244, 255, 191));
			gcd.ypos -= 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			gcd.shipxpos -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			gcd.shipxpos += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gcd.shooting == false) {
			gcd.shooting = true;
			lastpos = gcd.shipxpos;
			tirito.play();
		}
	}
}
void::GameController::PointerMovement() {
	gcd.deltatime = gcd.clock.getElapsedTime().asSeconds();
	if (gcd.ptrypos > lowestButton && gcd.deltatime > gcd.rate)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			gcd.ptrypos -= 50;
			gcd.clock.restart();
		}
	if (gcd.ptrypos < highestButton)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && gcd.deltatime > gcd.rate) {
			gcd.ptrypos += 50;
			gcd.clock.restart();
		}
}
void GameController::HandleInput(char key)
{
	int MaxCharacter = 12;
	if (getName == true) {
		if (sf::Keyboard::isKeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !word.empty())
			{
				//Erases last character
				if (gcd.charcounter < MaxCharacter)
				{
					word.erase(word.size() - 1);
					gcd.charcounter = gcd.charcounter - 2;
				}
				else if (gcd.charcounter >= MaxCharacter) {
					word.erase(word.size() - 1);
					gcd.charcounter = gcd.charcounter - 2;
				}
			}
			//Lets the name to be separated by spaces
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				space = " ";
				word += space;
				if (gcd.charcounter < MaxCharacter)
					gcd.charcounter--;
			}
			//Limits the number of characters to 12
			if (gcd.charcounter < MaxCharacter) {
				gcd.charcounter++;
				if ((isdigit(key) || isalpha(key)))
				{
					word += static_cast<char>(key);
				}
			}
		}
	}
}
void  GameController::AskPlayerName()
{
	string msg = "What is your name? \n";
	msg += word;
	sf::Text txt(msg, gcd.instructionsFont, 30);
	txt.setFillColor(sf::Color(32, 46, 23));
	txt.setOutlineColor(sf::Color(152, 199, 5));
	txt.setOutlineThickness(5);
	txt.setPosition(200,100);
	sf::Text txt2("Once you finish press enter", gcd.instructionsFont, 25);
	txt2.setFillColor(sf::Color(152, 199, 5));
	txt2.setOutlineColor(sf::Color(32, 46, 23));
	txt2.setOutlineThickness(5);
	txt2.setPosition(300,400);
	gcd.pWindow->draw(txt);
	gcd.pWindow->draw(txt2);
}