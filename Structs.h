#pragma once
#include "sfwdraw.h"

const float	screenWidth = 800, screenHeight = 600;
float		xAcc = 0, yAcc = 0;			//acceleration
float		xVel = 0, yVel = 0;			//velocity
int			score[2] = { 0, 0 };


struct	Walls
{
	//wall Position
	float x1 = 0;
	float x2 = 799;
	float y1 = 1;
	float y2 = 599;
};
int		barrierBox(Walls box) {

	//draw barrier box
	sfw::drawLine(box.x1, box.y1,	screenWidth, box.y1);	//top
	sfw::drawLine(box.x1, box.y2,	screenWidth, box.y2);	//bottom
	sfw::drawLine(box.x1, box.y1,	box.x1,	screenHeight);	//left
	sfw::drawLine(box.x2, box.y1,	box.x2,	screenHeight);	//right

	return 0;
}

struct	Player {
	//layout paddle shapes
	float xBack		=	0;
	float xFront	=	10;
	float yTop		=	0;
	float yBottom	=	100;
	//player position
	float xPos		=	0;
	float yPos		=	0;
	//movement speed
	float speed		=	500;
};
int		drawPlayer(Player player)
{
	//draw player
	sfw::drawLine(player.xBack  + player.xPos, player.yBottom + player.yPos, player.xBack  +	 player.xPos, player.yTop +		player.yPos);//back
	sfw::drawLine(player.xFront + player.xPos, player.yBottom + player.yPos, player.xFront +	 player.xPos, player.yTop +		player.yPos);//front
	sfw::drawLine(player.xBack  + player.xPos, player.yTop +	player.yPos, player.xFront + 1 + player.xPos, player.yTop +		player.yPos);//top
	sfw::drawLine(player.xBack  + player.xPos, player.yBottom + player.yPos, player.xFront + 1 + player.xPos, player.yBottom +  player.yPos);//bottom

	return 0;
}

struct	Ball {

	float x = 400;
	float y = 300;
	float r = 5;
	float xSpeed = 0;
	float ySpeed = 0;
};
int		drawBall(Ball ball) {

	//draws ball
	sfw::drawCircle(ball.x, ball.y, ball.r);

	return 0;
}

int		gameDraw(Ball ball, Player player1, Player player2) {

	drawBall(ball);
	drawPlayer(player1);	//player1
	drawPlayer(player2);	//player2

	return 0;
}