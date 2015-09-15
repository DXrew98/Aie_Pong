#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "sfwdraw.h"
#include "structs.h"


void setupPlayer(Player& player, int x, int y);
void randomDirection(Ball& ball);

int playerMove(Player& player, char one, char two);
int playerLock(Player& player1, Player& player2, Walls box);

int ballMove(Ball& ball);
int ballLock(Ball& ball, Walls box, Player player1, Player player2);

int playerScore(Ball& ball, Walls box, Player& player1, Player& player2);
int gameReset(Ball& ball, Player player1, Player player2);

int main() {
	Walls box;
	Ball ball;
	Player player1;
	Player player2;

	char choice;

	float delayTime = 0;
	srand(time(NULL));

	//promt player 
	std::cout << "Pong!" << std::endl;
	std::cout << "Player 1 uses the \"W\" and \"S\" keys to play" << std::endl;
	std::cout << "Player 2 uses the \"I\" and \"K\" keys to play" << std::endl;
	std::cout << "Cast the other player's paddle into oblivion to win!" << std::endl << std::endl;
	std::cout << "Press \"b\" and the enter to begin!" << std::endl;
	std::cin >> choice;
	while (choice == 'b') {

		//initialize game 
		sfw::initContext(screenWidth, screenHeight, "Pong");


		//setup game board		
		setupPlayer(player1, 10, 250);
		setupPlayer(player2, 780, 250);
		randomDirection(ball);
		//make game wait so player can ready
		delayTime = 2;



		while (sfw::stepContext())
		{
			if (delayTime <= 0) {
				delayTime = playerScore(ball, box, player1, player2);

				playerMove(player1, 'w', 's');
				playerMove(player2, 'i', 'k');
				playerLock(player1, player2, box);

				ballMove(ball);
				ballLock(ball, box, player1, player2);
			}

			else {
				delayTime -= sfw::getDeltaTime();
				if (delayTime <= 0) { gameReset(ball, player1, player2); }
			}

			barrierBox(box);
			gameDraw(ball, player1, player2);


			if (player1.yBottom <= 0 || player2.yBottom <= 0) {
				//terminate game
				player1.yBottom = 100;
				player2.yBottom = 100;
				sfw::termContext();
				break;
			}
		}
	system("cls");
	for (int i = 0; i < 2; ++i) {
		std::cout << "Player " << i + 1 << " Score = " << score[i] << std::endl;
	}

	if (score[0] > score[1]) { std::cout << std::endl << "Player 1 wins!!!!" << std::endl; }
	else { std::cout << std::endl << "Player 2 wins!!!!" << std::endl; }
	std::cout << std::endl;

	std::cout << "Press \"b\" and the enter to play again!" << std::endl;
	std::cout << "Press \"x\" and the enter to exit!" << std::endl;
	std::cin >> choice;
	if (choice == 'b') continue;

	//system("pause");
	}
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

int playerLock(Player& player1, Player& player2, Walls box){

	//keep paddels within boundrys
	if (player1.yPos + player1.yBottom > box.y2)	{ player1.yPos = box.y2 - player1.yBottom; }
	if (player1.yPos - 2 < box.y1)		{ player1.yPos = box.y1; }
	if (player2.yPos + player2.yBottom > box.y2)	{ player2.yPos = box.y2 - player2.yBottom; }
	if (player2.yPos - 2  < box.y1)		{ player2.yPos = box.y1; }

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
		ball.xSpeed *= -1; //flip ball direction
		if (ball.xSpeed > 900) { ball.xSpeed = 900; } //limit ball speed

	}
	//bounce off right paddle
	if (ball.x > playerR.xPos &&
		ball.x > playerR.xPos + playerR.xBack &&
		ball.y > playerR.yPos + playerR.yTop &&
		ball.y < playerR.yPos + playerR.yBottom) {
		ball.xSpeed += 50;
		ball.xSpeed *= -1; //flip ball direction
		if (ball.xSpeed < -900) { ball.xSpeed = -900; } //limit ball speed
	}
	return 0;
}

int playerScore(Ball& ball, Walls box, Player& player1, Player& player2) {

	//check for p1 to score
	if (ball.x > box.x2) {
		player2.yBottom -= 25;
		player1.yBottom += 10;
		score[0] += 1;
		return 2;
	}

	//check for p2 to score
	if (ball.x < box.x1) {
		player1.yBottom -= 25;
		player2.yBottom += 10;
		score[1] += 1;
		return 2;
	}

	
	return 0;
}

int gameReset(Ball& ball, Player player1, Player player2) {

	setupPlayer(player1, 10, 250);
	setupPlayer(player2, 780, 250);
	ball.x = 400;
	ball.y = 300;
	randomDirection(ball);

	return 0;
}

void randomDirection(Ball& ball) {

	//std::cout << rand() << " ";

	float finalXSpeed = 0;
	float finalYSpeed = 0;

	//// 60Deg Constraint
	//int ballDirection = (rand() % 60) - 30;
	//int playerPick = rand() % 2;

	//if (playerPick == 1) { ballDirection += 180; }

	//ballDirection *= PI / 180;

	//finalXSpeed += 200 * cos(ballDirection);
	//finalYSpeed += 200 * sin(ballDirection);

	//// apply the final speed to the ball
	//ball.xSpeed = finalXSpeed;
	//ball.ySpeed = finalYSpeed;

	// calculate variances
	finalXSpeed = (rand() % 200 + 140);
	finalYSpeed = (rand() % 100 + 50);

	if ((rand() % 2) == 1)
		finalXSpeed *= -1;
	if ((rand() % 2) == 1)
		finalYSpeed *= -1;


	// apply the speeds
	ball.xSpeed = finalXSpeed;
	ball.ySpeed = finalYSpeed;
}

