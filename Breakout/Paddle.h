#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>   
#include <time.h> 

#define SPEED 400.F
#define PADDLEHEIGHT 15.F
#define PADDLEWIDTH 100.F
#define PADDLE_TEXTURE_PATH "images/paddleImage.png"
#define PADDLE_SOUND_PATH "assets/impact4.wav"
#define PADDLE_X 270.f
#define PADDLE_Y 680.f


using namespace sf;
//paddle needs to be controlled by mouse or keyboard
//paddle stays at bottom of the screen
class Paddle
{
public:

	RectangleShape paddle;

	Paddle();
	void drawPaddle(RenderWindow& window);
	void player_mouseInput(int x, Time dt);
	void player_keyboardInput(Keyboard::Key key, Time dt);
	void moveRight(Time dt);
	void moveRight(int x);
	void moveLeft(Time dt);
	void moveLeft(int x);
	void onCollision();
	bool isCollideRight();
	bool isCollideLeft();
	int getHeight();
	int getWidth();
	Vector2f getPaddlePosition();

	
private:

	Vector2f position;
	Vector2f velocity;
	Vector2f origin;
	Vector2f paddleSize;
	SoundBuffer sb;
	Sound paddleSound;
	Texture paddleTexture;
};

