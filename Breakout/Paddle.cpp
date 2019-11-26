#include <iostream>
#include "Paddle.h"

Paddle::Paddle()
{
	paddleSize = Vector2f(PADDLEWIDTH, PADDLEHEIGHT);
	velocity = Vector2f(SPEED, 0.f);
	paddle.setSize(paddleSize);
	origin = paddleSize / 2.f;
	paddleTexture.loadFromFile(PADDLE_TEXTURE_PATH);
	paddle.setTexture(&paddleTexture);
	paddle.setOutlineColor(Color::Black);
	paddle.setOutlineThickness(2);
	position = Vector2f(PADDLE_X, PADDLE_Y);
	paddle.setPosition(position);
	sb.loadFromFile(PADDLE_SOUND_PATH);
	paddleSound.setBuffer(sb);
}

void Paddle::drawPaddle(RenderWindow& window)
{
	window.draw(paddle);
}

void Paddle::player_mouseInput(int x, Time dt)
{
	//Vector2i mouse_pos = Mouse::getPosition(window);
	if (x > 320) {
		//move right
		moveRight(x);
	}
	else {
		//move left
		moveLeft(x);
	}
	//std::cout << x << std::endl;
}

void Paddle::player_keyboardInput(Keyboard::Key key, Time dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		//move right 
		moveRight(dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		//move left
		moveLeft(dt);
	}
}

void Paddle::moveRight(int x) 
{
	//std::cout << "move right" << std::endl;
	paddle.setPosition(x, PADDLE_Y);
	if (isCollideRight()) {
		paddle.setPosition(640.f - (origin.x * 2), PADDLE_Y);
	}
}

void Paddle::moveRight(Time dt)
{
	velocity.x = SPEED * dt.asSeconds();
	std::cout << "move right" << std::endl;
	paddle.move(velocity.x, 0);
	if (isCollideRight()) {
		paddle.setPosition(640.f - (origin.x * 2), PADDLE_Y);
	}
}

void Paddle::moveLeft(Time dt)
{
	velocity.x = -SPEED * dt.asSeconds();
	paddle.move(velocity.x, 0);
	std::cout << "move left" << std::endl;
	if (isCollideLeft()) {
		paddle.setPosition(paddle.getOrigin().x, PADDLE_Y);
	}
}

void Paddle::moveLeft(int x)
{
	paddle.setPosition(x, PADDLE_Y);
	if (isCollideLeft()) {
		paddle.setPosition(paddle.getOrigin().x, PADDLE_Y);
	}
}

bool Paddle::isCollideLeft()
{
	Vector2f pos = paddle.getPosition();
	//std::cout << "pos_x: " << pos.x << std::endl;
	if (pos.x + origin.x < origin.x) {
		return true;
	
	}
	return false;
}

int Paddle::getHeight()
{
	return paddleSize.y;
}

int Paddle::getWidth()
{
	return paddleSize.x;
}

Vector2f Paddle::getPaddlePosition()
{
	return paddle.getPosition();
}

void Paddle::onCollision()
{
	paddleSound.play();
}

bool Paddle::isCollideRight()
{
	Vector2f pos = paddle.getPosition();
	if (pos.x + (origin.x*2) > 640) {
		return true;
	}
	return false;
}




