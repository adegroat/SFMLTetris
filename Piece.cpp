#include "Piece.h"

Piece::Piece() {
	createPiece(L_TYPE);
}

Piece::Piece(int type, int startX, int startY) {
	createPiece(type);
	shiftX(startX);
	shiftY(startY);
}

void Piece::createPiece(int type) {
	this->type = type;
	blocks.clear();
	switch(type) {
		case L_TYPE:
			blocks.push_back(Block(0, 0, true, sf::Color::White));
			blocks.push_back(Block(-1, 0, true, sf::Color::White));
			blocks.push_back(Block(1, 0, true, sf::Color::White));
			blocks.push_back(Block(-1, 1, true, sf::Color::White));
			break;
		case O_TYPE:
			blocks.push_back(Block(0, 0, true, sf::Color::Yellow));
			blocks.push_back(Block(1, 0, true, sf::Color::Yellow));
			blocks.push_back(Block(0, 1, true, sf::Color::Yellow));
			blocks.push_back(Block(1, 1, true, sf::Color::Yellow));
			break;
		case T_TYPE:
			blocks.push_back(Block(0, 0, true, sf::Color::Magenta));
			blocks.push_back(Block(-1, 0, true, sf::Color::Magenta));
			blocks.push_back(Block(1, 0, true, sf::Color::Magenta));
			blocks.push_back(Block(0, 1, true, sf::Color::Magenta));
			break;
		case S_TYPE:
			blocks.push_back(Block(0, 0, true, sf::Color::Red));
			blocks.push_back(Block(1, 0, true, sf::Color::Red));
			blocks.push_back(Block(0, 1, true, sf::Color::Red));
			blocks.push_back(Block(-1, 1, true, sf::Color::Red));
			break;
		case Z_TYPE:
			blocks.push_back(Block(0, 0, true, sf::Color::Green));
			blocks.push_back(Block(-1, 0, true, sf::Color::Green));
			blocks.push_back(Block(0, 1, true, sf::Color::Green));
			blocks.push_back(Block(1, 1, true, sf::Color::Green));

			break;
		case J_TYPE:
			blocks.push_back(Block(0, 0, true, sf::Color::Blue));
			blocks.push_back(Block(-1, 0, true, sf::Color::Blue));
			blocks.push_back(Block(1, 0, true, sf::Color::Blue));
			blocks.push_back(Block(1, 1, true, sf::Color::Blue));

			break;
		case I_TYPE:
		default:
			blocks.push_back(Block(0, 0, true, sf::Color::Cyan));
			blocks.push_back(Block(-1, 0, true, sf::Color::Cyan));
			blocks.push_back(Block(-2, 0, true, sf::Color::Cyan));
			blocks.push_back(Block(1, 0, true, sf::Color::Cyan));
			break;
	}
}

void Piece::draw(sf::RenderWindow& window) {
	for(int i = 0; i < blocks.size(); i++) {
		blocks.at(i).draw(window);
	}
}

void Piece::shiftX(int amount){
	for(int i = 0; i < blocks.size(); i++) {
		blocks[i].setX(blocks[i].getX() + amount);
	}
}

void Piece::shiftY(int amount){
	for(int i = 0; i < blocks.size(); i++) {
		blocks[i].setY(blocks[i].getY() + amount);
	}
}

void Piece::rotate() {
	if(type == O_TYPE) return;

	for(int i = 0; i < blocks.size(); i++) {
		int rotatedX = blocks[i].getStartY() * -1;
		int rotatedY = blocks[i].getStartX();
		blocks[i].setStartX(rotatedX);
		blocks[i].setStartY(rotatedY);

		blocks[i].setX(blocks[0].getX() + rotatedX * Block::SIZE);
		blocks[i].setY(blocks[0].getY() + rotatedY * Block::SIZE);
	}
}

std::vector<Block> Piece::getBlocks() {
	return blocks;
}

int Piece::getType(){
	return type;
}