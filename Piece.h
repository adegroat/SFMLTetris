#ifndef _PIECE_H
#define _PIECE_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Block.h"

class Piece {
private:
	std::vector<Block> blocks;
	int type;
public:
	static const int L_TYPE = 0;
	static const int O_TYPE = 1;
	static const int T_TYPE = 2;
	static const int S_TYPE = 3;
	static const int Z_TYPE = 4;
	static const int J_TYPE = 5;
	static const int I_TYPE = 6;
	static const int NUM_TYPES = 7;

	Piece();
	Piece(int type, int startX, int startY);
	void createPiece(int type);
	void draw(sf::RenderWindow& window);
	void shiftX(int amount);
	void shiftY(int amount);
	void rotate();
	std::vector<Block> getBlocks();
	int getType();
};

#endif