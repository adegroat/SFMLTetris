#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main(){
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Tetris");

	Game game(&window);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			game.handleEvents(event);
		}

		game.update();
		
		window.clear();
		game.draw();
		window.display();
	}

	return 0;
}