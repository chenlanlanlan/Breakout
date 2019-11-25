#include "Game.h"

Game::Game() : game_window(VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Breakout!", Style::Close),
player(),
ball()
{
	this->game_window.setVerticalSyncEnabled(true);
	this->game_window.setFramerateLimit(60);
	
	//this->background_texture.loadFromFile("images/background.png");
	//this->background_texture.setSmooth(true);
	//std::cout << BG_TEXTURE_PATH << std::endl;
	//this->background.setTexture(background_texture);
	//this->background.setTextureRect(IntRect(0, 0, 768, 800));
	//this->background.setColor(Color::White);

	isGameover = false;
	isGameStart = false;
}

void Game::runGame() 
{
	Clock clock;
	while (game_window.isOpen())
	{
		Time deltaTime = clock.restart();
		handleUserInput(deltaTime);
		renderGame();
	}
	return;
}

void Game::renderGame()
{
	game_window.clear();
	player.drawPaddle(game_window);
	ball.drawBall(game_window);
	game_window.display();
}

void Game::handleUserInput(Time deltaTime)
{
	sf::Event event;
	while (game_window.pollEvent(event))
	{

		switch (event.type)
		{
		case Event::Closed:
			game_window.close();
			break;
		case Event::KeyPressed:
			player.player_keyboardInput(event.key.code, deltaTime);
			if (!isGameStart) {
				//ball move with paddle
					ball.move(player);
			}
			break;
		case Event::MouseMoved:
			if (!isGameStart) {
				//ball move with paddle
				ball.move(player);
			}
			player.player_mouseInput(event.mouseMove.x, deltaTime);
			break;
		}
	}
}



