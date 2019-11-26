#include "Ball.h"
#include <iostream>

Ball::Ball()
{
	this->direction = Vector2f(0.f, 2.f); //goes up 
	this->radius = 15.f;
	this->position = Vector2f(PADDLE_X + 50.f, PADDLE_Y - radius);
	this->origin = Vector2f(radius, radius);
	this->ball_texture.loadFromFile(BALL_TEXTURE_PATH);
	this->speed = 300.f;
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
	ball.setPosition(pos.x + PADDLEWIDTH/2, pos.y - radius);
}

void Ball::move(Time elaspedTime)
{
	float offsetX, offsetY;
	Vector2f pos = ball.getPosition();
	offsetX = speed * direction.x * elaspedTime.asSeconds();
	offsetY = speed * direction.y * elaspedTime.asSeconds();
	ball.move(offsetX, offsetY);

}

void Ball::normalize(float windowX, float windowY)
{
	Vector2f pos = ball.getPosition();
	Vector2f ballDir = Vector2f(windowX / 2 - pos.x, windowY / 2 - pos.y);
	float mag = sqrtf(ballDir.x * ballDir.x + ballDir.y * ballDir.y);
	this->direction.x = ballDir.x / mag;
	this->direction.y = ballDir.y / mag;
}

void Ball::reversX()
{
	this->direction.x = -this->direction.x;
}
void Ball::reversY()
{
	this->direction.y = -this->direction.y;
}

void Ball::checkCollisionWithWindow(float windowX, float windowY)
{
	Vector2f pos = ball.getPosition();
	if (pos.x - radius < 0) {
		ball.setPosition(radius, pos.y);
		onCollision(WALL_SOUND_PATH);
		reversX();
	}
	else if (pos.x + radius >= windowX) {
		ball.setPosition(windowX - radius, pos.y);
		onCollision(WALL_SOUND_PATH);
		reversX();
	}
	if (pos.y - radius < 24) {
		ball.setPosition(pos.x, 24 + radius);
		onCollision(WALL_SOUND_PATH);
		reversY();
	}
}

void Ball::onCollision(String path)
{
	this->sb.loadFromFile(path);
	this->hit_Sound.setBuffer(sb);
	hit_Sound.play();
}

void Ball::setBallDirection(float num)
{
		direction.x = num;
}

void Ball::setSpeed(float acc)
{
	speed = speed + acc;
}

int Ball::getBallRadius()
{
	return radius;
}

int Ball::getBallD()
{
	return radius * 2;
}

Vector2f Ball::getBallPosition()
{
	return ball.getPosition();
}
