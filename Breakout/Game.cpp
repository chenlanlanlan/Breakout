#include "Game.h"

#define FONTSIZE 24

Game::Game() : game_window(VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Breakout!", Style::Close),
player(),
ball(),
font(),
lifeCount()
{
	this->game_window.setVerticalSyncEnabled(true);
	this->game_window.setFramerateLimit(60);
	//set background
	background_texture.loadFromFile(BG_TEXTURE_PATH);
	background_texture.setSmooth(true);
	background.setTexture(background_texture);
	lifeCount = 3;
	scoreCount = 0;
	brickCount = 0;
	level = 1;
	setText(gameName, 36, Vector2f(100.f, 200.f), "230 - BREAKOUT! ");
	setText(instruction, 18, Vector2f(100.f, 250.f), "Press Space to Start,\nand Press Space or \nclick left mouse button to lanuch the ball!");
	setText(scoreTitle, FONTSIZE, Vector2f(100.f, 5.f), "Score: ");
	setText(score, FONTSIZE, Vector2f(230.f, 5.f), std::to_string(scoreCount));
	setText(lifeTitle, FONTSIZE, Vector2f(400.f, 5.f), "Life: ");
	setText(life, FONTSIZE, Vector2f(500.f, 5.f), std::to_string(lifeCount));
	setText(winMsg, FONTSIZE, Vector2f(50.f, 300.f), "You Win! \nPress Space or \nclick left mouse button to lanuch the ball!");
	setText(lostMsg, FONTSIZE, Vector2f(50.f, 300.f), "GAME OVER!\nPress Space or \nclick left mouse button to restart!");

	startSound_buffer.loadFromFile(STARTSOUND_PATH);
	start_sound.setBuffer(startSound_buffer);

	launchSound_buffer.loadFromFile(LAUNCHSOUND_PATH);
	lanuch_sound.setBuffer(launchSound_buffer);

	lostLife_buffer.loadFromFile(LOSTLIFESOUND_PATH);
	lostlife_sound.setBuffer(launchSound_buffer);

	gameStat = MENU;

	isGameStart = false;

}

void Game::runGame() 
{
	Clock clock;
	while (game_window.isOpen())
	{
		Time deltaTime = clock.restart();
		handleUserInput(deltaTime);
		
		if (isGameStart) {
			ball.move(deltaTime);
			ball.checkCollisionWithWindow(WINDOWWIDTH, WINDOWHEIGHT);
			//check losing life??
			Vector2f ball_pos = ball.ball.getPosition();
			if (ball_pos.y + ball.ball.getRadius() >= WINDOWHEIGHT) {
				//lose life
				lifeCount--;
				life.setString(std::to_string(lifeCount));
				std::cout << "lost life! \n";
				std::cout << lifeCount;
				lostlife_sound.play();
				reset();
			}
			if (lifeCount == 0) {
				gameStat = GAMEOVER;
				restartGame();
			}
			//check collide with paddle
			if (isCollide(ball.ball, player.paddle)) {
				ballCollideWithPaddle(ball, player);
			}
			//check collide with bricks
			for (int i = 0; i < brick_Array.size(); i++) {
				if (isCollide(ball.ball, brick_Array[i].brick))
					ballCollideWithBrick(ball, brick_Array[i]);
	
			}
			if (brickCount == brick_Array.size()) {
				level++;
				ball.setSpeed(25.f);
				gameStat = NEXTLEVEL;
				isGameStart = false;
				brickCount = 0;
			}
		}
		renderGame();
	}
	return;
}

void Game::setText(Text& txt, int fontsize, Vector2f pos, String str)
{
	//set font 
	font.loadFromFile(FONT);
	txt.setCharacterSize(fontsize);
	txt.setFont(font);
	txt.setPosition(pos);
	txt.setFillColor(Color::White);
	txt.setString(str);	
}

void Game::renderGame()
{
	game_window.clear();
	game_window.draw(background);
	switch (gameStat)
	{
	case MENU:
		game_window.draw(gameName);
		game_window.draw(instruction);
		break;
	case PLAYING:
		game_window.draw(scoreTitle);
		game_window.draw(score);
		game_window.draw(lifeTitle);
		game_window.draw(life);
		for (auto brick : brick_Array) {
			brick.drawBrick(game_window);
		}
		player.drawPaddle(game_window);
		ball.drawBall(game_window);
		break;
	case NEXTLEVEL:
		game_window.draw(winMsg);
		break;
	case GAMEOVER:
		game_window.draw(lostMsg);
		break;
	}

	game_window.display();
}

void Game::createLevel()
{
	start_sound.play();
	gameStat = PLAYING;
	std::cout << "Hey! Create! \n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			if ((i + 1) % level == 0 || (j + 1) % level == 1) {
				Brick* brick = new Brick(Vector2f(i * 64, j * 32 + 32), 1);
				brick->setHitCount(1);
				brick_Array.push_back(*brick);
			}
			else if ((j + 1) % level == 0 || (i + 1) % level == 1) {
				Brick* brick = new Brick(Vector2f(i * 64, j * 32 + 32), 2);
				brick->setHitCount(2);
				brick_Array.push_back(*brick);
			}
			else if((i + 1) % level == 2 || (i + 1) % level == 3){
				Brick* brick = new Brick(Vector2f(i * 64, j * 32 + 32), 3);
				brick->setHitCount(3);
				brick_Array.push_back(*brick);
			}
			else {
				Brick* brick = new Brick(Vector2f(i * 64, j * 32 + 32), 4);
				brick->setHitCount(4);
				brick_Array.push_back(*brick);
			}
		}
	}
}

void Game::lanuchBall()
{
	lanuch_sound.play();
	std::cout << "Start! \n";
	isGameStart = true;
	//ball move
	ball.normalize(WINDOWWIDTH, WINDOWHEIGHT);
}

void Game::reset()
{
	isGameStart = false;
	player.paddle.setPosition(PADDLE_X, PADDLE_Y);
	ball.ball.setPosition(PADDLE_X + 50.f, PADDLE_Y - ball.getBallRadius());
}

void Game::restartGame()
{
	isGameStart = false;
	lifeCount = 3;
	life.setString(std::to_string(lifeCount));
	scoreCount = 0;
	score.setString(std::to_string(scoreCount));
	brickCount = 0;
	player.paddle.setPosition(PADDLE_X, PADDLE_Y);
	ball.ball.setPosition(PADDLE_X + 50.f, PADDLE_Y - ball.getBallRadius());
}

void Game::handleUserInput(Time deltaTime)
{
	sf::Event event;
	while (game_window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			game_window.close();
			break;
		//start with mouse
		case Event::MouseButtonPressed:
			if (gameStat != PLAYING && Mouse::isButtonPressed(Mouse::Left)) {
				createLevel();
			}
			else if (!isGameStart)
			{
				//ball move with paddle
				ball.move(player);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					lanuchBall();
				}
			}
			break;
		case Event::KeyPressed:
			player.player_keyboardInput(event.key.code, deltaTime);
			if (gameStat != PLAYING && event.key.code == Keyboard::Space) {
				createLevel();
			}
			else if(!isGameStart)
			{
				//ball move with paddle
				ball.move(player);
				if (event.key.code == Keyboard::Space) {
					lanuchBall();
				}
			}
			break;
		case Event::MouseMoved:
			if (!isGameStart) {
				//ball move with paddle
				ball.move(player);
			}
			player.player_mouseInput(event.mouseMove.x, deltaTime);
			break;
		}
	}
}

void Game::ballCollideWithPaddle(Ball& ball, Paddle& player)
{
	if (ball.getBallPosition().x - 50.f < player.getPaddlePosition().x)
		ball.setBallDirection(-1);
	else if (ball.getBallPosition().x - 50.f ==  player.getPaddlePosition().x)
		ball.setBallDirection(0);
	else if (ball.getBallPosition().x > player.getPaddlePosition().x)
		ball.setBallDirection(1);
	ball.reversY();
	ball.ball.setPosition(ball.getBallPosition().x, WINDOWHEIGHT - player.getHeight() - ball.getBallRadius() - 5);
	player.onCollision();
}

void Game::ballCollideWithBrick(Ball& ball, Brick& brick)
{
	if (ball.getBallPosition().y > brick.getBottomY()) { //collision from bottom
		ball.reversY();
		ball.ball.setPosition(ball.getBallPosition().x,
			brick.getBrickPosition().y + brick.getBrickHeight() + ball.getBallRadius() + 5);
		brick.takeDamage();
	}
	else if (ball.getBallPosition().y < brick.getTopY()) { //collision from top
		ball.reversY();
		brick.takeDamage();
		ball.ball.setPosition(ball.getBallPosition().x,
			brick.getBrickPosition().y - brick.getBrickHeight() - ball.getBallRadius() - 5);
	}
	else {
		ball.reversX();
		brick.takeDamage();
	}
	if (brick.getHitCount() == 0) { //remove brick 
		//add score
		switch (brick.getType())
		{
		case 1:
			scoreCount += 5;
			break;
		case 2:
			scoreCount += 10;
			break;
		case 3:
			scoreCount += 15;
			break;
		case 4:
			scoreCount += 20;
			break;
		}
		score.setString(std::to_string(scoreCount));
		brick.brick.setPosition(-100, 0);
		brickCount++; //count the number of brick removed
	}
}

bool Game::isCollide(CircleShape s1, RectangleShape s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}
