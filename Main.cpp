#include <chrono>
#include <thread>
#include <iostream>
#include "sfwdraw.h"
#include "structs.h"


void setupPlayer(Player& player, int x, int y);
int playerMove(Player& player, char one, char two);
int playerLock(Player& player1, Player& player2);
int ballMove(Ball& ball);
int ballLock(Ball& ball, Walls box, Player player1, Player player2);
int playerScore(Ball& ball, Walls box, Player player1, Player player2);
int gameReset(Ball& ball, Player player1, Player player2);

int main() {
	Walls box;
	Ball ball;
	Player player1;
	Player player2;

	//Initialize game 
	sfw::initContext(screenWidth, screenHight, "Pong");
	
	setupPlayer(player1, 10, 250);
	setupPlayer(player2, 780, 250);

	while (sfw::stepContext())
	{
		playerScore(ball, box, player1, player2);

		playerMove(player1, 'w', 's');
		playerMove(player2, 'i', 'k');
		playerLock(player1, player2);

		ballMove(ball);
		ballLock(ball, box, player1, player2);

		barrierBox(box);
		gameDraw(ball, player1, player2);



		//if (score1 > 10 || score2 > 10)
		//{
		//	score1 = score2 = 0;
		//	setupPlayer(..);
		//	resetBall(..);
		//}
	}

	//terminate game
	sfw::termContext();
}

int playerMove(Player & player, char one, char two) {
	
	//run velocity through DeltaTime
	player.xPos += xVel * sfw::getDeltaTime();
	player.yPos += yVel * sfw::getDeltaTime();

	//get input from player
	yAcc = xAcc = 0;
	if (sfw::getKey(one)) yAcc = -player.speed;
	if (sfw::getKey(two)) yAcc = player.speed;

	//run acceleration through DeltaTime
	player.xPos += xAcc * sfw::getDeltaTime();
	player.yPos += yAcc * sfw::getDeltaTime();


	return 0;
}

int playerLock(Player& player1, Player& player2){
	Walls box;

	//keep paddels within boundrys
	if (player1.yPos + 105 > box.y2)	{ player1.yPos = box.y2 - 105; }
	if (player1.yPos - 5 < box.y1)		{ player1.yPos = box.y1 + 5; }
	if (player2.yPos + 105 > box.y2)	{ player2.yPos = box.y2 - 105; }
	if (player2.yPos - 5  < box.y1)		{ player2.yPos = box.y1 + 5; }

	return 0;
}

void setupPlayer(Player& player, int x, int y) {

	player.xPos = x;
	player.yPos = y;

}

int ballMove(Ball& ball) {
	xAcc = ball.xSpeed;
	yAcc = ball.ySpeed;

	ball.x += xVel * sfw::getDeltaTime();
	ball.y += yVel * sfw::getDeltaTime();

	ball.x += xAcc * sfw::getDeltaTime();
	ball.y += yAcc * sfw::getDeltaTime();
	
	return 0;
}

int ballLock(Ball& ball, Walls box, Player playerL, Player playerR) {
	
	if (ball.y < box.y1) { ball.ySpeed *= -1; } //bounce off floor
	if (ball.y > box.y2) { ball.ySpeed *= -1; } //bounce off ceiling

	//paddle bounce code based off noobtut's code
	//bounce off left paddle
	if (ball.x < playerL.xPos + playerL.xFront &&
		ball.x > playerL.xPos &&
		ball.y > playerL.yPos + playerL.yTop &&
		ball.y < playerL.yPos + playerL.yBottom) {
		ball.xSpeed -= 50;
		ball.xSpeed *= -1;
	}
	//bounce off right paddle
	if (ball.x > playerR.xPos &&
		ball.x > playerR.xPos + playerR.xBack &&
		ball.y > playerR.yPos + playerR.yTop &&
		ball.y < playerR.yPos + playerR.yBottom) {
		ball.xSpeed += 50;
		ball.xSpeed *= -1;
	}
	return 0;
}

int playerScore(Ball& ball, Walls box, Player player1, Player player2) {
	bool go = true;
	
	if (ball.x < box.x1) { 
		p1Score++; 
		gameReset(ball, player1, player2); 	
		go = false;
		if (go = false) {
			ball.xSpeed = 0;
			ball.ySpeed = 0;
		}
	}
	if (ball.x > box.x2) { 
		p2Score++; 
		gameReset(ball, player1, player2); }
		go = false;
		if (go = false) {
			ball.xSpeed = 0;
			ball.ySpeed = 0;
		}
	return 0;
}

int gameReset(Ball& ball, Player player1, Player player2) {

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	setupPlayer(player1, 10, 250);
	setupPlayer(player2, 780, 250);
	ball.x = 400;
	ball.y = 300;
	ball.xSpeed = -100;
	ball.ySpeed = -100;
	return 0;
}

