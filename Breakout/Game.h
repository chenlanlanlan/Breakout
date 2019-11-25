#pragma once
#include <iostream>
#include "Ball.h"
#include "Paddle.h"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 500
#define BG_TEXTURE_PATH "images/background.png"


using namespace sf;

class Game
{
public:
	Game();
	void runGame();

private:
	RenderWindow game_window;
	Texture background_texture;
	Sprite background;
	Ball ball;
	Paddle player;
	Text score;
	Font font;
	SoundBuffer startSound_buffer;
	bool isGameover;
	bool isGameStart;
	void renderGame();
	void handleUserInput(Time deltaTime);
	void restartGame();
};

