#include "Ball.h"
#include <iostream>

Ball::Ball()
{
	this->dirction = Vector2f(0.f, 1.f); //goes up 
	this->radius = 20.f;
	this->position = Vector2f(PADDLE_X + 50.f, PADDLE_Y - radius);
	this->origin = Vector2f(radius, radius);
	this->ball_texture.loadFromFile(BALL_TEXTURE_PATH);
	
	ball.setRadius(radius);
	ball.setOrigin(origin);
	ball.setPosition(position);
	ball.setTexture(&ball_texture);
}


void Ball::drawBall(RenderWindow& window)
{
	window.draw(ball);
}

void Ball::move(Paddle player)
{
	Vector2f pos = player.paddle.getPosition();
	std::cout << "pos_x: " << pos.x << "pos_y: " << pos.y << std::endl;
	ball.setPosition(pos.x + PADDLEWIDTH/2, pos.y - radius);

}


void Ball::checkCollisionWithPaddle()
{
	
}
