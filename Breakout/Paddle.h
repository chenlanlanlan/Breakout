#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>   
#include <time.h> 

#define SPEED 350.F
#define PADDLEHEIGHT 100.F
#define PADDLEWIDTH 20.F
#define PADDLE_TEXTURE_PATH "images/paddleImage.png"
#define PADDLE_X 334.f
#define PADDLE_Y 480.f


using namespace sf;
//paddle needs to be controlled by mouse or keyboard
//paddle stays at bottom of the screen
class Paddle
{
public:

	RectangleShape paddle;

	Paddle();
	void drawPaddle(RenderWindow& window);
	void player_mouseInput();
	void player_keyboardInput();
	void moveRight();
	void moveLeft();
	void updatePlayer();
	bool isCollideRight();
	bool isCollideleft();
	
private:

	Vector2f position;
	Vector2f origin;
	Vector2f paddleSize;
	SoundBuffer sb;
	Sound paddleSound;
	Texture paddleTexture;
};

