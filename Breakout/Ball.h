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
//#define SPEED 

class Ball
{
public:
	CircleShape ball;
	Ball();
	void drawBall(RenderWindow& window);
	void move(Paddle player);
	void reversX();
	void reversY();
	void checkCollisionWithWindow();
	void checkCollisionWithPaddle();
	void checkCollisionWithBricks();
	void calculateAngle();
	void onColision();
	void onLosePoint();
	void reset();

private:
	
	float radius;
	Color color;
	Vector2f position;
	Vector2f origin;
	Vector2f dirction; //left (-1,0) right(1,0)
	Vector2f player_position;
	Texture ball_texture;

};

