#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

using namespace sf;
using namespace std;

static vector<Color> v = { Color(188, 16,125) , Color(44, 166, 164) , Color(234, 158, 141) , Color(208, 239, 177) };


class Brick : public RectangleShape
{
public:
	int NrShell = 1;
	Color clr;
	
	Brick(Vector2f x) : RectangleShape(x) 
	{
		clr = v[0];
		NrShell = 1;
		this->setFillColor(clr);
	}
	Brick(Vector2f x, int lvl) : RectangleShape(x) 
	{
		clr = v[lvl];
		NrShell = lvl + 1;
		this->setFillColor(clr);
	}
	Brick() : Brick(Vector2f(0, 0)) {};

	static void CreateBrickMatrix(Brick m[][20], int NrRow, int NrCol);
	static void DrawBrickMatrix(Brick m[][20], int NrRow, int NrCol, RenderWindow& W);

};
