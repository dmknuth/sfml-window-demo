#include "Window.hpp"
#include "Balls.hpp"
#include <SFML/Window/Event.hpp>
#include <random>
#include <iostream>

//----------------------------------------------------------------------------------------
Balls::Balls
(
    u_int16_t   c,
    u_int16_t   r
) : count(c), radius(r)
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
    }

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
        float x = rand() % 5;
        float y = rand() % 5;
//        std::cout << x << ", " << y << ")" << std::endl;
        sf::Vector2f pos = ball[i]->getPosition();
        int r = rand() % 4;
        if(r == 0)
            ball[i]->setPosition({pos.x + x, pos.y + y});
        else if(r == 1)
            ball[i]->setPosition({pos.x - x, pos.y + y});
        else if(r == 2)
            ball[i]->setPosition({pos.x + x, pos.y - y});
        else if(r == 3)
            ball[i]->setPosition({pos.x - x, pos.y - y});
        ball[i]->setFillColor(random_color());
    }
    return 0;
}

//----------------------------------------------------------------------------------------
std::uint8_t
Balls::distribution_generator()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,255);
    return distribution(generator);
}

//----------------------------------------------------------------------------------------
sf::Color
Balls::random_color()
{
    std::uint8_t r = distribution_generator();
    std::uint8_t g = distribution_generator();
    std::uint8_t b = distribution_generator();
    std::uint8_t a = 128;
    return(sf::Color(r, g, b, a));
}
