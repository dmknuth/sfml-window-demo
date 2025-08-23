#include "Window.hpp"
#include "Balls.hpp"
#include <SFML/Window/Event.hpp>
#include <random>
#include <iostream>
#include <numbers>
#include <cmath>

//----------------------------------------------------------------------------------------
void
Balls::generate()
{
    srand(time(0));
    for(int i = 0; i < count; ++i)
    {
        sf::CircleShape* circle = new sf::CircleShape;
        ball.push_back(circle); 
        ball[i] -> setRadius(radius);
        ball[i] -> setFillColor(random_color());
        float x = (x_max - 2 * radius) / 2.0;
        float y = (y_max - 2 * radius) / 2.0;
        ball[i] -> setPosition({x, y});
        float speed = 0.1;
        float heading = (float)(i * 30.0); //(float)(rand() % 360);
        velocity.push_back(ball_struct(heading, speed));
    }
}

//----------------------------------------------------------------------------------------
void
Balls::set_size(u_int16_t r)
{
    radius = r;
}

//----------------------------------------------------------------------------------------
void
Balls::set_count(u_int16_t c)
{
    count = c;
}

//----------------------------------------------------------------------------------------
void
Balls::set_boundaries(u_int16_t x, u_int16_t y)
{
    x_max = x;
    y_max = y;
}

//----------------------------------------------------------------------------------------
sf::CircleShape
Balls::get_item(int i)
{
    return *ball[i];
}

//----------------------------------------------------------------------------------------
int
Balls::update()
{
    for(int i = 0; i < count; ++i)
    {
        sf::Vector2f pos = ball[i]->getPosition();
        float s = velocity[i].speed;
        float h = velocity[i].heading;
        pos.x += (s * std::cosf(h * 2.0 * std::numbers::pi / 360.0));
        pos.y += (s * std::sinf(h * 2.0 * std::numbers::pi/  360.0));
        if((pos.x < 0) || ((pos.x + (2.0 * radius)) > x_max))
        {
            velocity[i].heading = 180.0 - h;
            if(pos.x < 0)
                pos.x = s * std::cosf(velocity[i].heading * 2.0 * std::numbers::pi / 360.0);
            else
                pos.x = x_max - 2.0 * radius - s * std::cosf(velocity[i].heading * 2.0 * std::numbers::pi / 360.0);
        }
        if((pos.y < 0) || ((pos.y + (2.0 * radius)) > y_max))
        {
            velocity[i].heading = 360.0 - h;
            if(pos.y < 0)
                pos.y = s * std::sinf(velocity[i].heading * 2.0 * std::numbers::pi / 360.0);
            else
                pos.y = y_max - 2.0 * radius - s * std::sinf(velocity[i].heading * 2.0 * std::numbers::pi / 360.0);
        }
        ball[i]->setPosition(pos);
    }
    return 0;
}

//----------------------------------------------------------------------------------------
sf::Color
Balls::random_color()
{
    int c = rand() % 8;
    sf::Color color;
    switch(c)
    {
        case 0:
            color = sf::Color::Red;
            break;

        case 1:
            color = sf::Color::Yellow;
            break;

        case 2:
            color = sf::Color::Blue;
            break;

        case 3:
            color = sf::Color::Green;
            break;

        case 4:
            color = sf::Color(0, 0, 128);
            break;

        case 5:
            color = sf::Color(0, 128, 0);
            break;

        case 6:
            color = sf::Color::Cyan;
            break;

        case 7:
            color = sf::Color::Magenta;
            break;
    }
    color.a = 128;
    return(color);
}
