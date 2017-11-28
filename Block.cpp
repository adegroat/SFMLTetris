#include "Block.h"

Block::Block(){
	x = 0;
	y = 0;
	isFilled = false;
}

Block::Block(int startX, int startY, bool isFilled, const sf::Color& color) {
	x = startX * SIZE;
	y = startY * SIZE;
	this->startX = startX;
	this->startY = startY;
	this->isFilled = isFilled;
	shape.setSize(sf::Vector2f(SIZE, SIZE));
	shape.setFillColor(color);
}

void Block::setFilled(bool isFilled) {
	this->isFilled = isFilled;
}

bool Block::getIsFilled() const {
	return isFilled;
}

int Block::getX() const {
	return x;
}

int Block::getY() const {
	return y;
}

void Block::setX(int newX){
	x = newX;
}

void Block::setY(int newY){
	y = newY;
}

int Block::getStartX() {
	return startX;
}

int Block::getStartY() {
	return startY;
}

void Block::setStartX(int newStartX) {
	startX = newStartX;
}

void Block::setStartY(int newStartY) {
	startY = newStartY;
}

void Block::draw(sf::RenderWindow& window) {
	shape.setPosition(x, y);
	window.draw(shape);
}

bool Block::isCollided(const Block& block) const {
	return x + SIZE > block.getX() && x < block.getX() + SIZE && y + SIZE >= block.getY() && y <= block.getY() + SIZE;
}

bool Block::isEqual(const Block& block) const {
	return x == block.getX() && y == block.getY() && isFilled == block.getIsFilled();
}