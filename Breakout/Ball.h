#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include "Paddle.h"


#define PI 3.14159265
#define MAXBOUNCEANGLE 5*PI/12
#define BALL_TEXTURE_PATH "images/ball.png"
#define WALL_SOUND_PATH "assets/impact2.wav"

class Ball
{
public:
	CircleShape ball;
	Vector2f direction; //left (-1,0) right(1,0)

	Ball();
	void drawBall(RenderWindow& window);
	void move(Paddle player);
	void move(Time elapsedTime);
	void normalize(float windowX, float windowY);
	void reversX();
	void reversY();
	void checkCollisionWithWindow(float windowX, float windowY);
	void onCollision(String path);
	void setBallDirection(float num);
	void setSpeed(float acc);
	int getBallRadius();
	int getBallD();
	Vector2f getBallPosition();

private:
	
	float radius, speed;
	Color color;
	Vector2f position;
	Vector2f origin;
	Vector2f player_position;
	Texture ball_texture;
	SoundBuffer sb;
	Sound hit_Sound;

};

