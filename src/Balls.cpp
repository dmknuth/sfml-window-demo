#include "Window.hpp"
#include "Balls.hpp"
#include <SFML/Window/Event.hpp>
#include <random>
#include <iostream>
#include <numbers>

//----------------------------------------------------------------------------------------
void
Balls::generate()
{
    std::cout << "count " << count << " radius " << radius << std::endl;
    for(int i = 0; i < count; ++i)
    {
        sf::CircleShape* circle = new sf::CircleShape;
        ball.push_back(circle); 
        ball[i]->setRadius(radius);
        ball[i]->setFillColor(random_color());
        float x = distribution_generator();
        float y = distribution_generator();
//        std::cout << "ball " << i << " pos(" << x << ", " << y << ")" << std::endl;
        ball[i]->setPosition({x, y});
        u_int16_t speed = (float)(rand() % 10);
        u_int16_t direction = (float)(rand() % 360);
        velocity.push_back(ball_struct(speed, direction));
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
        float direction = ((rand() % 2) == 0) ? -1.0 : 1.0;
        float angle = velocity[i].direction + direction * (float)(rand() % 10) / 100.0;
        float d = 0.01;
        sf::Vector2f pos = ball[i]->getPosition();
        float x = pos.x + d * cos(angle / (2 * std::numbers::pi));
        float y = pos.y + d * sin(angle / (2 * std::numbers::pi));
        if(x < 0)
        {
            x += d;
            velocity[i].direction = -velocity[i].direction;
        }
        else if(x + 2.0 * radius > x_max)
        {
            x -= d;
            velocity[i].direction = -velocity[i].direction;
        }
        if(y < 0)
        {
            y += d;
            velocity[i].direction = -velocity[i].direction;
        }
        else if(y + 2.0 * radius > y_max)
        {
            y -= d;
            velocity[i].direction = -velocity[i].direction;
        }
//        std::cout << x << ", " << y << std::endl;
        ball[i]->setPosition({x, y});
    }
    return 0;
}

//----------------------------------------------------------------------------------------
std::uint8_t
Balls::distribution_generator()
{
/*
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,255);
    return distribution(generator);
*/
    return rand() % 128;
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
