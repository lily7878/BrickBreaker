#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Brick.h"

using namespace sf;

void Brick::CreateBrickMatrix(Brick m[][20], int NrRow, int NrCol)
{
	if (NrCol > 10) NrCol = 10;
	if (NrRow > 15) NrRow = 15;

	float height = 30;
	float spaceR = 25;
	float lenght = 100;
	float spaceC = 30;

	float a = (float)NrCol * 130 - 30;
	float b = (float)NrRow * 55 - 25;

	float startX = (1920 - a) / 2;
	float startY = 100 + (600 - b) / 2;

	for (int i = 0; i < NrRow; i++)
	{
		for (int j = 0; j < NrCol; j++)
		{
			int lvl = NrRow / 4 - (i + 1) / 4;
			m[i][j] = Brick(Vector2f(lenght, height), lvl);
			m[i][j].setPosition(startX + j * (lenght + spaceC), startY + i * (height + spaceR));
		}
	} 

}

void Brick::DrawBrickMatrix(Brick m[][20], int NrRow, int NrCol, RenderWindow& W)
{
	for (int i = 0; i < NrRow; i++)
	{
		for (int j = 0; j < NrCol; j++)
		{
			if(m[i][j].NrShell > 0)
				W.draw(m[i][j]);
		}
	}
}
