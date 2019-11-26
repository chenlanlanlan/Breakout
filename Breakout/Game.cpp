#include "Game.h"

#define FONTSIZE 24

Game::Game() : game_window(VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Breakout!", Style::Close),
player(),
ball(),
font()
{
	this->game_window.setVerticalSyncEnabled(true);
	this->game_window.setFramerateLimit(60);
	//set background
	//background_texture.loadFromFile(BG_TEXTURE_PATH);
	//background_texture.setSmooth(true);
	//background.setTexture(background_texture);
	//background.setTextureRect(IntRect(0, 0, 640, 500));
	setFont();

	startSound_buffer.loadFromFile(STARTSOUND_PATH);


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

void Game::setFont()
{
	//set font 
	font.loadFromFile(FONT);
	
	scoreTitle.setCharacterSize(FONTSIZE);
	scoreTitle.setFont(font);
	scoreTitle.setPosition(100.f, 10.f);
	scoreTitle.setFillColor(Color::White);
	scoreTitle.setString("Score: ");
	
	score.setCharacterSize(FONTSIZE);
	score.setFont(font);
	score.setPosition(230.f, 10.f);
	score.setFillColor(Color::White);
	score.setString("0");
	
	lifeTitle.setCharacterSize(FONTSIZE);
	lifeTitle.setFont(font);
	lifeTitle.setPosition(400.f, 10.f);
	lifeTitle.setFillColor(Color::White);
	lifeTitle.setString("Life: ");

	life.setCharacterSize(FONTSIZE);
	life.setFont(font);
	life.setPosition(500.f, 10.f);
	life.setFillColor(Color::White);
	life.setString("0");
}

void Game::renderGame()
{
	game_window.clear();
	player.drawPaddle(game_window);
	ball.drawBall(game_window);
	game_window.draw(scoreTitle);
	game_window.draw(score);
	game_window.draw(lifeTitle);
	game_window.draw(life);
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
					if (event.key.code == Keyboard::Space) {

					}
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





