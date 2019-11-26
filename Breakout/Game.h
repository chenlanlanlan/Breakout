#pragma once
#include <iostream>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

#define WINDOWWIDTH 640.f
#define WINDOWHEIGHT 700.f
#define BG_TEXTURE_PATH "images/bg.png"
#define STARTSOUND_PATH "assets/gameStart1.wav"
#define LAUNCHSOUND_PATH "assets/launch1.wav"
#define LOSTLIFESOUND_PATH "assets/lifeLost4.wav"
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
	Text gameName, instruction, scoreTitle, score, lifeTitle, life, winMsg, lostMsg;
	Font font;
	SoundBuffer startSound_buffer, launchSound_buffer, lostLife_buffer;
	Sound start_sound, lanuch_sound, lostlife_sound;
	std::vector <Brick> brick_Array;
	int level, lifeCount, scoreCount, brickCount;
	bool isGameStart;
	
	enum states{MENU, PLAYING, NEXTLEVEL, GAMEOVER};
	int gameStat;

	void setText(Text& txt, int fontsize, Vector2f pos, String str);
	void renderGame();
	void createLevel();
	void lanuchBall();
	void reset();
	void restartGame();
	void handleUserInput(Time deltaTime);
	void ballCollideWithPaddle(Ball& ball, Paddle& player);
	void ballCollideWithBrick(Ball& ball, Brick& brick);
	bool isCollide(CircleShape s1, RectangleShape s2);
};

