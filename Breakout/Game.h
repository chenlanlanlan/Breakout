#pragma once
#include <iostream>
#include "Ball.h"
#include "Paddle.h"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 500
#define BG_TEXTURE_PATH "images/background.png"
#define STARTSOUND_PATH "assets/gameStart1.wav"
#define FONT "assets/KenPixel Square.ttf"

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
	Text scoreTitle, score, lifeTitle, life;
	Font font;
	SoundBuffer startSound_buffer;
	Sound start_sound;
	bool isGameover;
	bool isGameStart;
	void setFont();
	void renderGame();
	void handleUserInput(Time deltaTime);
	void restartGame();
};

