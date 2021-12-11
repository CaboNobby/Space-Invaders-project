#pragma once
#include <assert.h>
#include <sstream>
#include "Structs.h"
#include "Objects.h"
#include "SFML/Graphics.hpp"

void GameController::Init() {
	if (!tiritobuffer.loadFromFile("data/chuk.wav"))
		assert(false);
	tirito.setBuffer(tiritobuffer);
}
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
		gcd.bullet.setPosition(lastpos, gcd.yPos);
		gcd.spaceship.setPosition(gcd.shipXPos, 550);
		if (gcd.shooting != true)
			gcd.bullet.setColor(sf::Color::Transparent);
		else if (gcd.shooting == true) {
			gcd.bullet.setColor(sf::Color(244, 255, 191));
			gcd.yPos -= 1.4f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			gcd.shipXPos -= 0.5f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			gcd.shipXPos += 0.5f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gcd.shooting == false) {
			gcd.shooting = true;
			lastpos = gcd.shipXPos;
			tirito.play();
		}
	}
}
void::GameController::PointerMovement() {
	gcd.deltatime = gcd.clock.getElapsedTime().asSeconds();
	if (gcd.ptrYPos > lowestButton && gcd.deltatime > gcd.rate)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			gcd.ptrYPos -= 50;
			gcd.clock.restart();
		}
	if (gcd.ptrYPos < highestButton)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && gcd.deltatime > gcd.rate) {
			gcd.ptrYPos += 50;
			gcd.clock.restart();
		}
}
void GameController::HandleInput(char key)
{
	if (getName == true) {
		if (sf::Keyboard::isKeyPressed )
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !word.empty())
			{
				//Erases last character
				if (gcd.charCounter < MaxCharacter)
				{
					word.erase(word.size() - 1);
					gcd.charCounter = gcd.charCounter - 2;
				}
				else if (gcd.charCounter >= MaxCharacter) {
					word.erase(word.size() - 1);
					gcd.charCounter = gcd.charCounter - 2;
				}
			}
			//Lets the name to be separated by spaces
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				space = " ";
				word += space;
				if (gcd.charCounter < MaxCharacter)
					gcd.charCounter--;
			}
			//Limits the number of characters to 12
			if (gcd.charCounter < MaxCharacter) {
				gcd.charCounter++;
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