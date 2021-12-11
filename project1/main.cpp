#include <assert.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Structs.h"
#include "Objects.h"
#include "GameController.h"

using namespace std;
/*
In charge of running the game and loading the different game modes 
*/
class Game {
public:
	Game() :myspaceship(mgd),myenemy(mgd),mycollision(mgd),mygamecontroller(mgd) {
		mgd.pWindow = &window;
	};
	void Run();                                                 //Program beggining
private:
	void RenderBackground();
	void GameMenu();
	//It loads the game state we are in
	void GameState();
	void UpdateGameState();
	void GameInstructions();
	//Display players scores and names
	void ScoreTable();
	//Compare players score and hold the higher one at higherScore
	//Set the player name
	void Scores();
	void GameOver();
	//Displayes player score while is playing
	void Counter();
	//setup
	void Init();
	State state = TITLE_SCREEN;
	sf::RenderWindow window;
	sf::Event event;                             //Process events
	GD mgd;                                      //Shared game data
	GameController mygamecontroller;
	Collision mycollision;
	Spaceship myspaceship;
	Enemy myenemy;
	sf::Texture bgTexture;
	sf::Texture ttlTexture;
	sf::Text scoreText;
	sf::Text nameText;
	sf::Sprite ptrSprite;
	sf::Texture ptrTexture;
	sf::Sprite bgSprite;
	sf::Sprite goSprite;
	sf::Sprite ttlSprite;
	sf::Texture insTexture;
	sf::Texture goTexture;
	sf::Sprite insSprite;
	sf::Music music;
	string PlayerName[5];
	string PlayerScore[5];
	bool playing = false;
	int scoreArray[5] = {};
	int gapNumber = 4;     //Keeps the gaps available to be filled up by players
	int gap = 0;           //Last gap to be filled up
	int higherScore = 0;
	int instructions = 250;
	int play = 300;
	int player = 0;
	int leaderBoard = 350;
	int exit = 400;

};
void ::Game::Counter() {
	std::ostringstream numberToString;
	numberToString << mgd.points;
	mgd.score.setFont(mgd.instructionsFont);
	mgd.score.setString(numberToString.str());
	window.draw(mgd.score);

}
void::Game::Scores() {
	if (mgd.points > higherScore) {
		higherScore = mgd.points;
		//Once game is played the fifth time reorganize the scores
		if(player > 4){
			for (gapNumber = 4; gapNumber > gap; gapNumber--)
			{
				scoreArray[gapNumber ] = scoreArray[gapNumber -1];
				PlayerName[gapNumber] = PlayerName[gapNumber -1];
		    }
		}
		PlayerName[gapNumber] = mygamecontroller.word;
		scoreArray[gapNumber] = mgd.points;
		if (gapNumber > gap)
			gapNumber--;
		player++;
	}
}
void::Game::ScoreTable() {
	int y = 0;
	int MaxName = 5;
	sf::Text tabText;
	tabText.setFont(mgd.arcadeFont);
	tabText.setString("High Score");
	tabText.setScale(1.5f, 1.5f);
	tabText.setPosition(280, 20);
	window.draw(tabText);
	//Only five people can be on the ScoreTable
	for (int i(0); i < MaxName; i++)
	{
		PlayerScore[i] = std::to_string(scoreArray[i]);
		nameText.setString(PlayerName[i]);
		nameText.setPosition(150, 200 + y);
		scoreText.setString(PlayerScore[i]);
		scoreText.setPosition(400, 200 + y);
		window.draw(nameText);
		window.draw(scoreText);
		y += 20;
	}
}
void::Game::GameOver() {
	goSprite.setTexture(goTexture);
	window.draw(goSprite);
}
void::Game::Init() {
	scoreText.setFont(mgd.arcadeFont);
	nameText.setFont(mgd.arcadeFont);
	if (!ttlTexture.loadFromFile("data/titlescreen.png"))
		assert(false);
	if (!mgd.instructionsFont.loadFromFile("data/fonts/comic.ttf"))
		assert(false);
	if (!mgd.arcadeFont.loadFromFile("data/fonts/ARCADECLASSIC.ttf"))
		assert(false);
	if (!insTexture.loadFromFile("data/gameinstructions.png"))
		assert(false);
	if (!goTexture.loadFromFile("data/gameover.png"))
		assert(false);
	if (!ptrTexture.loadFromFile("data/LargeAlien.png"))
		assert(false);
	if (!bgTexture.loadFromFile("data/background.png"))
		assert(false);
	if (!music.openFromFile("data/Cantina.ogg"))
		assert(false);
}
void::Game::GameMenu() {
	sf::Text menuText;
	int ypos = 250;
	const int textnumber = 4;
	string text[textnumber] = { "Instructions","Play","Leaderboard" ,"Exit" };     //Holds the name of the different game modes
	menuText.setFont(mgd.arcadeFont);
	for (int textdisplayed(0); textdisplayed < textnumber; textdisplayed++) {
		menuText.setString(text[textdisplayed]);
		menuText.setPosition(330, ypos);
		window.draw(menuText);
		ypos += 50;
	}
	ptrSprite.setTexture(ptrTexture);
	ptrSprite.setScale(0.04f, 0.04f);
	ptrSprite.setPosition(280, mgd.ptrYPos);
	window.draw(ptrSprite);
}
void::Game::GameInstructions() {
	insSprite.setTexture(insTexture);
	insSprite.setPosition(-250, 0);
	window.draw(insSprite);
}
void::Game::GameState() {
	RenderBackground();
	switch (state) {
	case State::GAME_PLAYING:
		myspaceship.Render();
		myenemy.RenderEnemies();
		myenemy.Colour();
		Counter();
		if (playing == false) {
			music.play();
			playing = true;
		}
		break;
	case State::EXIT:
		break;
	case State::TITLE_SCREEN:
		ttlSprite.setTexture(ttlTexture);
		window.draw(ttlSprite);
		break;
	case State::GAME_OVER:
		GameOver();
		break;
	case State::MAIN_MENU:
		GameMenu();
		break;
	case State ::GAME_INSTRUCTIONS:
		GameInstructions();
		break;
	case State ::LEADER_BOARD:
		ScoreTable();
		break;
	case State::GET_NAME:
		mygamecontroller.AskPlayerName();
		mygamecontroller.getName = true;
		break;
	default:
		assert(false);
	}

}
void::Game::UpdateGameState() {
	mgd.deltatime = mgd.clock.getElapsedTime().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		state = State::EXIT;
	switch (state) {

	case State::GAME_PLAYING:
		mygamecontroller.KeyHandler();
		mycollision.Update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			state = State::MAIN_MENU;
			Scores();
			mgd.enemies = 44;
			mycollision.quit = true;
		}
		if (mycollision.gameOver == true) {
			state = State::GAME_OVER;
			mycollision.gameOver = false;
		}
		break;
	case State::EXIT:
		window.close();
		break;
	case State::TITLE_SCREEN:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mgd.deltatime > mgd.rate) {
			state = State::MAIN_MENU;
			mgd.clock.restart();
		}
		break;
	case State::GAME_OVER:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mgd.deltatime > mgd.rate) {
			Scores();
			state = State::MAIN_MENU;
			mgd.clock.restart();
		}
		if (playing == true)
			music.stop();
		break;
	case State::MAIN_MENU:
		//Clears word and resets the character counter for the next player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mgd.ptrYPos == play && mgd.deltatime > mgd.rate) {
			state = State::GET_NAME;
			mgd.ptrYPos = 250;
			mgd.clock.restart();
			mygamecontroller.word.clear();
			mgd.charCounter = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mgd.ptrYPos == instructions && mgd.deltatime > mgd.rate) {
			state = State::GAME_INSTRUCTIONS;
			mgd.clock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mgd.ptrYPos == leaderBoard)
			state = State::LEADER_BOARD;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mgd.ptrYPos == exit)
			state = State::EXIT;
		mygamecontroller.PointerMovement();
		break;
	case State::GAME_INSTRUCTIONS:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			state = State::MAIN_MENU;
		break;
	case State::LEADER_BOARD:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			state = State::MAIN_MENU;
		break;
	case State::GET_NAME:
		//Reset game counter
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && mgd.deltatime > mgd.rate) {
			state = State::GAME_PLAYING;
			mgd.charCounter--;
			mgd.points = 0;
			mygamecontroller.getName = false;
		}
		break;
	default:
		assert(false);

	}
}
void Game::RenderBackground() {
	int tilesInX = 19; //tiles to draw in a row
	int tilesInY = 12; //tiles to draw in a column
	float x = 0;
	float y = 0;
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
}

void Game::Run() {
	Init();
	myenemy.Init();
	myspaceship.Init();
	mygamecontroller.Init();
	window.create(sf::VideoMode(GDC::SCREEN_RES.x, GDC::SCREEN_RES.y),"Space Invaders");
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered)
			mygamecontroller.HandleInput(static_cast<char>(event.text.unicode));
				
		}
		window.clear();
		GameState();
		UpdateGameState();
		window.display();
	}
}
//Where it all starts
int main()
{
	srand(time(NULL));
	Game g;
	g.Run();
	return EXIT_SUCCESS;
}
