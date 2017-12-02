#include "Game.h"

Game::Game(sf::RenderWindow *window) {
	this->window = window;
	srand(time(0));
	fallWait = 350;
	playTimeStr = "0";
	if(!font.loadFromFile("Squared.ttf")) {
		std::cerr << "Error loading font!" << std::endl;
	}
	newGame();
}

void Game::newGame() {
	board.clear();
	shift = 0;
	left = false;
	right = false;
	rotate = false;
	shouldFall = true;
	playTimeClock.restart();
	generateCurrentPiece();
	gameState = IN_GAME;
}

void Game::gameOver() {
	gameState = GAME_OVER;
	int playTime = static_cast<int>(playTimeClock.getElapsedTime().asSeconds());
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << playTime;
	playTimeStr = ss.str() + " sec";
}

void Game::draw() {
	if(gameState == GAME_OVER) {
		drawText("Game Over", 35, 70, 75);
		drawText("Time played: " + sf::String(playTimeStr), 60, 200, 30);
	}

	if(gameState == MAIN_MENU) {
		drawText("Tetris", 25, 70, 110);
	}

	if(gameState == IN_GAME) {
		for(int i = 0; i < board.size(); i++) {
			board.at(i).draw(*window);
		}
		currentPiece.draw(*window);		
	}
	
	if (gameState != IN_GAME) {
		drawText("Press \"Enter\" to play", 65, 300);
		drawText("Press \"q\" to quit", 110, 380);
	}
}

void Game::update() {
	if(gameState == IN_GAME) {
		if(left || right) {
			currentPiece.shiftX(shift * Block::SIZE);
			left = false;
			right = false;
		}
				
		if(rotate) {
			currentPiece.rotate();
			rotate = false;
		}

		handleCollisions();
		checkForFullLines();

		// Shift piece down after FALL_WAIT ms
		if(clock.getElapsedTime().asMilliseconds() > FALL_WAIT) {
			if(shouldFall){
				currentPiece.shiftY(Block::SIZE);
				collisionClock.restart();
			}
			clock.restart();
		}
	}
}

void Game::checkForFullLines(){
	for(int y = 0; y < HEIGHT; y += Block::SIZE) {
		std::vector<int> toBeDeletedIndex;

		// Loop through each possible y and store location of blocks with same y val
		for(int i = 0; i < board.size(); i++) {
			if(board.at(i).getY() == y) toBeDeletedIndex.push_back(i);
		}

		// Check if there is a full line
		if(toBeDeletedIndex.size() * Block::SIZE == WIDTH) {
			for(int i = 0; i < toBeDeletedIndex.size(); i++) {
				board.at(toBeDeletedIndex.at(i)) = Block();
			}

			// Shift blocks down
			for(int i = 0; i < board.size(); i++) {
				if(board.at(i).getIsFilled() && board.at(i).getY() < y) {
					board.at(i).setY(board.at(i).getY() + Block::SIZE);
				}
			}
		}
	}
}

void Game::handleCollisions(){
	for(int i = 0; i < currentPiece.getBlocks().size(); i++) {
		Block cb = currentPiece.getBlocks().at(i);

		// Prevent leaving the screen
		if(cb.getX() < 0) currentPiece.shiftX(Block::SIZE);
		if(cb.getX() + Block::SIZE > WIDTH) currentPiece.shiftX(-Block::SIZE);		

		// Lock in piece if it touches the ground
		bool blockOnGround = cb.getY() + Block::SIZE == HEIGHT;
		if(blockOnGround) {
			lockInCurrentPiece();
			break;
		}

		for(int j = 0; j < board.size(); j++) {
			Block b = board.at(j);

			if(b.getIsFilled()) {
				if(cb.getX() == b.getX() && (cb.getY() + Block::SIZE == b.getY() || blockOnGround)) {
					shouldFall = false;

					lockInCurrentPiece();

					if(cb.getY() <= 0) {
						gameOver();
						return;
					}
				} else shouldFall = true;

				if(cb.getY() == b.getY() && cb.getX() == b.getX()) {
					currentPiece.shiftX(-shift * Block::SIZE);
					break;
				}
			}
		}
	}
}

void Game::lockInCurrentPiece(){
	if(collisionClock.getElapsedTime().asMilliseconds() < COLLISION_TIME) return;

	shouldFall = false;
	for(int i = 0; i < currentPiece.getBlocks().size(); i++) {
		board.push_back(currentPiece.getBlocks().at(i));
	}
	generateCurrentPiece();
	collisionClock.restart();
	shouldFall = true;
}

void Game::handleEvents(sf::Event event) {
	switch(event.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Left) {
				left = true;
				shift = -1;
			}
			if(event.key.code == sf::Keyboard::Right) {
				right = true;
				shift = 1;
			}
			if(event.key.code == sf::Keyboard::Up) { 
				rotate = true;
			}
			break;
		case sf::Event::KeyReleased:
			if(event.key.code == sf::Keyboard::Left) {
				shift = 0;
				left = false;
			}
			if(event.key.code == sf::Keyboard::Right) {
				shift = 0;
				right = false;
			}
			if(event.key.code == sf::Keyboard::Up) {
				rotate = false;
			}
			// Menu options
			if(event.key.code == sf::Keyboard::Return && gameState != IN_GAME) {
				newGame();
			}
			if(event.key.code == sf::Keyboard::Q && gameState != IN_GAME) {
				window->close();
			}
			break;
	}
}

void Game::generateCurrentPiece(){
	int randType = rand() % Piece::NUM_TYPES;
	currentPiece.createPiece(randType);
	currentPiece.shiftX(4 * Block::SIZE);
}

void Game::drawText(const sf::String& text, int x, int y, int size) {
	sf::Text sfText(text, font, size);
	sfText.setColor(sf::Color::White);
	sfText.setPosition(x, y);
	window->draw(sfText);
}