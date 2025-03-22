
#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Ball.h"
#include "Player.h"

#define PI 3.14159265359



using namespace sf;
using namespace std;


void Ball::Move(float x, float y, float v)
{
	Vector2f a = this->getPosition();
	a.x = a.x + v * x;
	a.y = a.y + v * y;
	this->setPosition(a);
	
}

bool Ball::HitPlayer(Player x)
{
	Vector2f posM = this->getPosition();
	Vector2f posP = x.bar.getPosition();

	posM.y += 40;

	if (posM.y > 1000 && posM.x >= posP.x && posM.x <= posP.x + 250)
	{
		return 1;
	}

	return 0;
}

double clamp(double x, double lower, double upper)
{
	return min(upper, max(x, lower));
}

bool Ball::TouchBrick(Brick a)
{
	Vector2f posM = this->getPosition();
	float rad = this->getRadius();

	posM.x += rad;
	posM.y += rad;

	FloatRect boundsB = a.getGlobalBounds();

	float closeX = clamp(posM.x, boundsB.left, boundsB.left + boundsB.width);
	float closeY = clamp(posM.y, boundsB.top, boundsB.top + boundsB.height);

	float distX = posM.x - closeX;
	float distY = posM.y - closeY;

	float squareD = distX * distX + distY * distY;

	return squareD <= rad * rad;
}

void Ball::AfterHitPlayer(float& x, float& y, Player a)
{
	y = -y;

	Vector2f posB = this->getPosition();
	float rad = this->getRadius();

	FloatRect boundsP = a.bar.getGlobalBounds();

	float dist = posB.x - (boundsP.left + boundsP.width / 2);

	float normalizedDist = dist / (boundsP.width / 2);

	float angleAdjustment = normalizedDist * (PI / 4); 
	float speed = sqrt(x * x + y * y); 


	x = speed * sin(angleAdjustment);
	y = -speed * cos(angleAdjustment);

}

void Ball::AfterHitBrick(float& x, float& y, Brick a)
{
	FloatRect boundsB = a.getGlobalBounds();
	Vector2f ballCenter = this->getPosition();
	ballCenter.x += this->getRadius();
	ballCenter.y += this->getRadius();


	float overlapLeft = ballCenter.x + this->getRadius() - boundsB.left;
	float overlapRight = boundsB.left + boundsB.width - ballCenter.x;
	float overlapTop = ballCenter.y + this->getRadius() - boundsB.top;
	float overlapBottom = boundsB.top + boundsB.height - ballCenter.y;


	bool hitVertical = (overlapLeft < overlapRight && 
		                overlapLeft < overlapTop && 
		                overlapLeft < overlapBottom) ||
							(overlapRight < overlapLeft && 
							 overlapRight < overlapTop && 
							 overlapRight < overlapBottom);

	if (hitVertical) {
		x = -x; 
	}
	else {
		y = -y; 
	}
}

bool Ball::HitWall()
{
	Vector2f ballCenter = this->getPosition();
	float ballRadius = this->getRadius();
	ballCenter.x += ballRadius;
	ballCenter.y += ballRadius;
	if (ballCenter.y + ballRadius <= 100) return true;
	if (ballCenter.x - ballRadius  <= 0) return true;
	if (ballCenter.x + ballRadius >= 1920) return true;
	return false;
}

void Ball::AfterHitWall(float& x, float& y)
{
	Vector2f ballCenter = this->getPosition();
	float ballRadius = this->getRadius();
	ballCenter.x += ballRadius;
	ballCenter.y += ballRadius;
	if (ballCenter.y - ballRadius <= 100)
	{
		y = -y;
	}
	if (ballCenter.x - ballRadius <= 0 || ballCenter.x + ballRadius >= 1920)
	{
		x = -x;
	}
}

bool Ball::HitVoid(Player x)
{
	Vector2f ballCenter = this->getPosition();
	float ballRadius = this->getRadius();
	ballCenter.x += ballRadius;
	ballCenter.y += ballRadius;

	if (ballCenter.y + ballRadius > 1080 && !this->HitPlayer(x))
	{
		return true;
	}
	return false;
}