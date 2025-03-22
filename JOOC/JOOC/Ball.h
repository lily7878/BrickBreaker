#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Player.h"
#include "Brick.h"



using namespace sf;
using namespace std;

class Ball : public CircleShape
{
public:
	Color clr;
	float Velocity = 0;

	Ball() : CircleShape(0) {}
	Ball(float r) : CircleShape(r) 
	{ 
		clr = Color(167, 153, 255);
		this->setFillColor(clr);
	}

	void Move(float x, float y, float v);
	bool HitPlayer(Player x);
	bool TouchBrick(Brick a);
	bool HitWall();
	bool HitVoid(Player x);

	void AfterHitPlayer(float& x, float& y, Player a);
	void AfterHitBrick(float& x, float& y, Brick a);
	void AfterHitWall(float& x, float& y);
	void AfterHitVoid(float& x, float& y);

};