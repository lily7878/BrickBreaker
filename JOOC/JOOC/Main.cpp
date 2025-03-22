#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Player.h"
#include "Brick.h"
#include "Ball.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "My window");

    Player p(Vector2f(250.f, 30.f));
    p.bar.setFillColor(Color(70, 129, 137));
    p.bar.setPosition(Vector2f(835.f, 1000.f));

    Ball o(20);
    o.setPosition(Vector2f(940.f, 800.f));
    o.Velocity = 500;

    Clock clk;
    Brick brM[20][20] = {};
    vector<Color> v = { Color(188, 16, 125), Color(44, 166, 164), Color(234, 158, 141), Color(208, 239, 177) };

    int nrR = 10;
    int nrC = 8;

    float x = 0, y = 0;
    bool gamePaused = true;  

    Brick::CreateBrickMatrix(brM, nrR, nrC);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (Keyboard::isKeyPressed(Keyboard::Scan::Left) && !gamePaused)
                {
                    p.Velocity = -1000;
                }
                if (Keyboard::isKeyPressed(Keyboard::Scan::Right) && !gamePaused)
                {
                    p.Velocity = 1000;
                }
                if (event.key.code == Keyboard::Space && gamePaused)
                {
                    gamePaused = false;  
                    x = 0;
                    y = 1; 
                    o.setPosition(Vector2f(940.f, 800.f));
                    p.bar.setPosition(Vector2f(835.f, 1000.f));
                }
            }
            if (event.type == Event::KeyReleased)
            {
                p.Velocity = 0;
            }
            if (event.type == Event::Closed)
                window.close();
        }

        if (!gamePaused)
        {
            float deltaTime = clk.restart().asSeconds();
            p.Move(p.Velocity * deltaTime);

            for (int i = 0; i < nrR; i++)
            {
                for (int j = 0; j < nrC; j++)
                {
                    if (brM[i][j].NrShell != 0 && o.TouchBrick(brM[i][j]) == true)
                    {
                        brM[i][j].NrShell--;
                        if (brM[i][j].NrShell >= 1)
                        {
                            brM[i][j].setFillColor(v[brM[i][j].NrShell - 1]);
                        }
                        o.AfterHitBrick(x, y, brM[i][j]);
                    }
                }
            }

            if (o.HitPlayer(p) && o.Velocity != 0)
            {
                p.NrHit++;
                o.AfterHitPlayer(x, y, p);
            }

            if (o.HitWall())
            {
                o.AfterHitWall(x, y);
            }

            if (o.HitVoid(p))
            {

                o.setPosition(Vector2f(940.f, 800.f));
                p.bar.setPosition(Vector2f(835.f, 1000.f));
                Brick::CreateBrickMatrix(brM, nrR, nrC);
                x = 0;
                y = 0;
                gamePaused = true;  


                window.clear(Color(0, 23, 31));
                Brick::DrawBrickMatrix(brM, nrR, nrC, window);
                window.draw(p.bar);
                window.draw(o);
                window.display();

                cout << "Press Space to Restart\n";
            }


            o.Move(x, y, o.Velocity * deltaTime);
        }
        else
        {
   
            clk.restart();
        }

        window.clear(Color(0, 23, 31));
        Brick::DrawBrickMatrix(brM, nrR, nrC, window);
        window.draw(p.bar);
        window.draw(o);
        window.display();
    }

    return 0;
}
