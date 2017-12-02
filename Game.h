#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Block.h"
#include "Piece.h"

class Game {
public:
	static const int WIDTH = 10 * Block::SIZE;
	static const int HEIGHT = 13 * Block::SIZE;

	static const int IN_GAME = 0;
	static const int MAIN_MENU = 1;
	static const int GAME_OVER = 2;

	static const int COLLISION_TIME = 250;
	static const int FALL_WAIT = 300;

	Game(sf::RenderWindow *window);
	void draw();
	void update();
	void handleEvents(sf::Event event);
private:
	sf::RenderWindow *window;
	sf::Clock clock, collisionClock, playTimeClock;
	sf::Font font;
	std::vector<Block> board;
	bool left, right, rotate, shouldFall;
	int fallWait, shift, gameState;
	Piece currentPiece;
	std::string playTimeStr;

	void checkForFullLines();
	void handleCollisions();
	void generateCurrentPiece();
	void lockInCurrentPiece();
	void drawText(const sf::String& text, int x, int y, int size = 30);
	void newGame();
	void gameOver();
};

#endif