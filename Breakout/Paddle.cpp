#include "Paddle.h"

Paddle::Paddle()
{
	paddleSize = Vector2f(PADDLEHEIGHT, PADDLEWIDTH);
	paddle.setSize(paddleSize);
	origin = paddleSize / 2.f;
	paddleTexture.loadFromFile(PADDLE_TEXTURE_PATH);
	paddle.setTexture(&paddleTexture);
	position = Vector2f(PADDLE_X, PADDLE_Y);
	paddle.setPosition(position);
}

void Paddle::drawPaddle(RenderWindow& window)
{
	window.draw(paddle);
}

