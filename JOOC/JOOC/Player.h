#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

using namespace sf;

class Player
{
public:
	RectangleShape bar;
	int Score = 0;
	float Velocity = 0;
	int NrHit = 0;


	Player(Vector2f x)
	{
		bar = RectangleShape(x);
	}
	Player() {};

	void Move(float dist);
};
