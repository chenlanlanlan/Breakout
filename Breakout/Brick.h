#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#define BRICKHEIGHT 32.F 
#define BRICKWIDTH 64.F
#define BRICKTEXTURE_1 "images/can1.png"
#define BRICKTEXTURE_2 "images/can2.png"
#define BRICKTEXTURE_3 "images/can3.png"
#define BRICKTEXTURE_4 "images/can4.png"
#define BRICKSOUND_PATH "assets/impact1.wav"

using namespace sf;

class Brick
{
public:
	RectangleShape brick; 

	Brick(Vector2f pos, int type);
	void drawBrick(RenderWindow& window);
	void setHitCount(int num);
	int getHitCount();
	void takeDamage();
	int getBrickHeight();
	int getTopY();
	int getBottomY();
	int getType();
	Vector2f getBrickPosition();

private:
	int hitCount, type;
	Vector2f brickSize;
	Vector2f origin;
	Texture texture;
	SoundBuffer brickSb;
	Sound brickSound;
};

