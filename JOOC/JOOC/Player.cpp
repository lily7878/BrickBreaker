#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Player.h"

using namespace sf;

void Player::Move(float dist)
{
	Vector2f a = bar.getPosition();
	if (a.x + dist <= 1670 && a.x + dist >= 0) 
	{
		this->bar.setPosition(Vector2f(a.x + dist, a.y));
	}
	
}
