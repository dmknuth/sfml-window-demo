#include "Window.hpp"
#include "Shapes.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Angle.hpp>
#include <random>
#include <iostream>
#include <numbers>
#include <cmath>

//----------------------------------------------------------------------------------------
void
Shapes::generate()
{
    srand(time(0));
    for(int i = 0; i < count; ++i)
    {
        sf::RectangleShape* circle = new sf::RectangleShape;
//        circle -> setRadius(radius);
        circle -> setSize({(float)radius, (float)radius});
        circle -> setOrigin({radius * 0.5f, radius * 0.5f});
        circle -> setFillColor(random_color());
        float x = (x_max - 2 * radius) / 2.0;
        float y = (y_max - 2 * radius) / 2.0;
        circle -> setPosition({x, y});
        float speed = (float)(rand() % 50 + 1) / 100.0;
        float heading = (float)(rand() % 360);
        shape.push_back(circle); 
        velocity.push_back(shape_struct(heading, speed));
    }
}

//----------------------------------------------------------------------------------------
void
Shapes::set_size(u_int16_t r)
{
    radius = r;
}

//----------------------------------------------------------------------------------------
void
Shapes::set_count(u_int16_t c)
{
    count = c;
}

//----------------------------------------------------------------------------------------
void
Shapes::set_boundaries(u_int16_t x, u_int16_t y)
{
    x_max = x;
    y_max = y;
}

//----------------------------------------------------------------------------------------
sf::RectangleShape
Shapes::get_item(int i)
{
//    return *reinterpret_cast<sf::RectangleShape*>(shape[i]);
//    return *static_cast<sf::RectangleShape*>(shape[i]);
//    if(typeid((shape[i])) == sf::RectangleShape*)
        return *dynamic_cast<sf::RectangleShape*>(shape[i]);
//    return *dynamic_cast<sf::RectangleShape*>(shape[i]);
}

//----------------------------------------------------------------------------------------
int
Shapes::update()
{
    const float k360Degrees = 360.0f;
    const float kTwoPi = 2.0f * std::numbers::pi;
    const float d = radius / 2.0f;

    for(int i = 0; i < count; ++i)
//    for(auto i : shape)
    {
        sf::Vector2f pos = shape[i]->getPosition();
        
        float s = velocity[i].speed;
        float h = velocity[i].heading;
        
        pos.x += (s * std::cosf(h * kTwoPi / k360Degrees));
        pos.y += (s * std::sinf(h * kTwoPi / k360Degrees));
//        pos.x = x_max / 2.0f;
//        pos.y = y_max / 2.0f;
        
        if((pos.x < d) || ((pos.x + d) > x_max))
        {
            velocity[i].heading = k360Degrees / 2.0 - h;
            if(pos.x < d)
                pos.x = d + s * std::cosf(velocity[i].heading * kTwoPi / k360Degrees);
            else
                pos.x = x_max - d - s * std::cosf(velocity[i].heading * kTwoPi / k360Degrees);
        }
        
        if((pos.y < d) || ((pos.y + d) > y_max))
        {
            velocity[i].heading = k360Degrees - h;
            if(pos.y < d)
                pos.y = d + s * std::sinf(velocity[i].heading * kTwoPi / k360Degrees);
            else
                pos.y = y_max - d - s * std::sinf(velocity[i].heading * kTwoPi / k360Degrees);
        }
        shape[i] -> setPosition(pos);
        sf::Angle r = shape[i] -> getRotation();
        using namespace sf::Literals;
        if(h > 180.0)
            r -= 0.1_deg;
        else
            r += 0.1_deg;
        shape[i] -> setRotation(r);
    }
    return 0;
}

//----------------------------------------------------------------------------------------
sf::Color
Shapes::random_color()
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
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    color.a = rand() % 128 + 128;
    return(color);
}
