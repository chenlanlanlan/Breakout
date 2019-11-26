#include "Brick.h"

Brick::Brick(Vector2f pos, int type)
{
	hitCount = 0;
	brickSize = Vector2f(BRICKWIDTH, BRICKHEIGHT);
	origin = Vector2f(BRICKWIDTH / 2, BRICKHEIGHT / 2);
	brick.setPosition(pos);
	brick.setSize(brickSize);
	switch (type)
	{
	case 1:
		this->type = type;
		texture.loadFromFile(BRICKTEXTURE_1);
		break;
	case 2:
		this->type = type;
		texture.loadFromFile(BRICKTEXTURE_2);
		break;
	case 3:
		this->type = type;
		texture.loadFromFile(BRICKTEXTURE_3);
		break;
	case 4:
		this->type = type;
		texture.loadFromFile(BRICKTEXTURE_4);
		break;
	}
	
	brick.setTexture(&texture);
	brickSb.loadFromFile(BRICKSOUND_PATH);
	brickSound.setBuffer(brickSb);

}

void Brick::drawBrick(RenderWindow& window)
{
	window.draw(brick);
}

void Brick::setHitCount(int num)
{
	this->hitCount = num;
}


int Brick::getHitCount()
{
	return hitCount;
}

void Brick::takeDamage()
{
	brickSound.play();
	std::cout << hitCount << std::endl;
	hitCount--;
}

int Brick::getBrickHeight()
{
	return brickSize.y;
}

int Brick::getTopY()
{
	return brick.getPosition().y - BRICKHEIGHT / 2;
}

int Brick::getBottomY()
{
	return brick.getPosition().y + BRICKHEIGHT / 2;
}
int Brick::getType()
{
	return type;
}


Vector2f Brick::getBrickPosition()
{
	return brick.getPosition();
}