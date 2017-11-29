#ifndef _BLOCK_H
#define _BLOCK_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Block {

private:
	int x, y;
	int startX, startY;
	bool isFilled;
	sf::RectangleShape shape;
public:
	static const int SIZE = 50;
	Block();
	Block(int startX, int startY, bool isFilled, const sf::Color& color);
	void setFilled(bool isFilled);
	bool getIsFilled() const;
	int getX() const;
	int getY() const;
	void setX(int newX);
	void setY(int newY);
	int getStartX();
	int getStartY();
	void setStartX(int newStartX);
	void setStartY(int newStartY);
	void draw(sf::RenderWindow& window);
	bool isEqual(const Block& block) const;
};

#endif