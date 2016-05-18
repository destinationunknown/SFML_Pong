#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Player.h"
#include "Wall.h"
#include "Ball.h"
#include <boost/lexical_cast.hpp>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800 , 600 ), "Title");
    window.setFramerateLimit(60);

    sf::Event event;

    Player player1(window.getSize(), 1);
    Player player2(window.getSize(), 2);
    Ball ball(window.getSize());
    Wall top_wall(sf::Keyboard::Up, window.getSize());
    Wall bottom_wall(sf::Keyboard::Down, window.getSize());

    sf::Text score;
    sf::Font font;
    font.loadFromFile("assets/AmericanTypewriter.ttc");
    score.setFont(font);
    score.setString(boost::lexical_cast<string>(player1.score) + " | " + boost::lexical_cast<string>(player2.score) );
    score.setOrigin(score.getGlobalBounds().width/2, score.getGlobalBounds().width/2);
    score.setPosition(window.getSize().x/2, 100);


    while (window.isOpen() )
    {
        while(window.pollEvent(event))
        {
            if (event.type == event.Closed)
            {
                window.close();
            }
        }


        // Check for user input and move the paddles accordingly
        // TODO: Add "isPlaying" variable to add pause functionality

        if (sf::Keyboard::isKeyPressed(player1.up_control))
        {
            player1.MovePaddle(player1.up_control, window.getSize());
        }

        if (sf::Keyboard::isKeyPressed(player1.down_control))
        {
            player1.MovePaddle(player1.down_control, window.getSize());
        }

        if (sf::Keyboard::isKeyPressed(player2.up_control))
        {
            player2.MovePaddle(player2.up_control, window.getSize());
        }


        if (sf::Keyboard::isKeyPressed(player2.down_control))
        {
            player2.MovePaddle(player2.down_control, window.getSize());
        }

        // Check for collisions with the paddles
        // TODO: Calculate the angle of incidence and reflection for the new ballAngle
        // TODO: Check whether the paddle is moving to add spin
        // TODO: Decide what happens if the ball hits the bottom or top face of the paddle

        if (ball.DidCollide(player1))
        {
            // TODO: Add movement with left and right instead of angles
            // TODO: Find out what "Taking enum type from pointer" means

            ball.horizontal_direction = 1;
        }

        if (ball.DidCollide(player2))
        {
            ball.horizontal_direction = -1;

        }

        // Check for collisions with the walls

        if (ball.DidCollide(top_wall))
        {
            if (ball.vertical_direction == 1)
            {
                ball.vertical_direction = -1;
            }
            else
            {
                ball.vertical_direction = 1;
            }
        }

        if (ball.DidCollide(bottom_wall))
        {
            if (ball.vertical_direction == 1)
            {
                ball.vertical_direction = -1;
            }
            else
            {
                ball.vertical_direction = 1;
            }
        }
        
        
        // Check if the ball is out of bounds ( Goal scored )
        
        if (ball.ball.getPosition().x < 0)      // Player 2 has scored
        {
            player2.score ++;
            ball.ResetBall(window.getSize());
        }

        if (ball.ball.getPosition().x > window.getSize().x)      // Player 1 has scored
        {
            player1.score ++;
            ball.ResetBall(window.getSize());
        }

        // Move the ball at each frame
        ball.Move();

        // Update the score
        score.setString(boost::lexical_cast<string>(player1.score) + " | " + boost::lexical_cast<string>(player2.score) );

        // Draw all the objects to the screen

        window.clear();
        window.draw(player1.paddle);
        window.draw(player2.paddle);
        window.draw(top_wall.wall);
        window.draw(bottom_wall.wall);
        window.draw(score);
        window.draw(ball.ball);
        window.display();

    }
}

