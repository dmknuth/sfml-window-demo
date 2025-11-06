#include "Window.hpp"
#include "Shapes.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Angle.hpp>
#include <random>
#include <iostream>
#include <numbers>
#include <cmath>
#include <memory>

//----------------------------------------------------------------------------------------
void
Shapes::generate()
{
    srand(time(0));
    for(int i = 0; i < count; ++i)
    {
//        sf::RectangleShape* new_shape = new sf::RectangleShape;
        auto new_shape = std::make_unique<sf::RectangleShape>();
//        new_shape -> setRadius(size);
//        size += ((rand() % 2) == 0 ? (float(rand() % 100) / 100.0) : (float(rand() % 100) / -100.0));
        new_shape -> setSize({(float)size, (float)size});
        new_shape -> setOrigin({size * 0.5f, size * 0.5f});
        float x = (x_max - 2 * size) / 2.0;
        float y = (y_max - 2 * size) / 2.0;
        new_shape -> setPosition({x, y});
        float speed = (float)(rand() % 50000 + 100) / 100000.0;
//        std::cout << "speed " << speed << std::endl;
        float heading = (float)(rand() % 360);
//        std::cout << "heading " << heading << std::endl;
        sf::Color color;
        if(heading > 180.0)
            color = sf::Color::Green;
        else
            color = sf::Color::Red;
 //       new_shape -> setFillColor(color);
        new_shape -> setFillColor(random_color());
        shape.push_back(std::move(new_shape)); 
        velocity.push_back(shape_struct(heading, speed));
    }
}

//----------------------------------------------------------------------------------------
void
Shapes::set_size(u_int16_t s)
{
    size = s;
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
//    return *dynamic_cast<sf::RectangleShape*>(shape[i]);
    return *shape[i];
//    return *dynamic_cast<sf::RectangleShape*>(shape[i]);
}

//----------------------------------------------------------------------------------------
/*
int
Shapes::update()
{
    const float k360Degrees = 360.0f;
    const float kTwoPi = 2.0f * std::numbers::pi;
    const float d = size / 2.0f;

    for(int i = 0; i < count; ++i)
    {
        sf::Vector2f pos = shape[i]->getPosition();
        
//        velocity[i].speed *= 0.99999;
        velocity[i].speed *= 1.00001;
        if(velocity[i].speed < 0.0)
            velocity[i].speed = 0.0;
        float s = velocity[i].speed;
        int dir = rand() % 2;
//        s += (dir == 1 ? (float(rand() % 100) / 100.0) : (float(rand() % 100) / -100.0));
        float h = velocity[i].heading;
        
        pos.x += (s * cos(h * kTwoPi / k360Degrees));
        pos.y += (s * sin(h * kTwoPi / k360Degrees));
        
        if((pos.x < d) || ((pos.x + d) > x_max))
        {
            velocity[i].heading = k360Degrees / 2.0 - h;
            if(pos.x < d)
                pos.x = d + s * cos(velocity[i].heading * kTwoPi / k360Degrees);
            else
                pos.x = x_max - d - s * cos(velocity[i].heading * kTwoPi / k360Degrees);
        }
        
        if((pos.y < d) || ((pos.y + d) > y_max))
        {
            velocity[i].heading = k360Degrees - h;
            if(pos.y < d)
                pos.y = d + s * sin(velocity[i].heading * kTwoPi / k360Degrees);
            else
                pos.y = y_max - d - s * sin(velocity[i].heading * kTwoPi / k360Degrees);
        }
        shape[i] -> setPosition(pos);
        sf::Angle r = shape[i] -> getRotation();
        using namespace sf::Literals;
        if(h > 180.0)
        {
            r -= 1.0_deg;
//            std::cout << "-";
        }
        else
        {
            r += 1.0_deg;
//            std::cout << "+";
        }
        shape[i] -> setRotation(r);
        sf::Color new_color = shape[i] -> getFillColor();
        switch(i % 3)
        {
            case 0:
                new_color.r++;
                break;

            case 1:
                new_color.g++;
                break;

            case 2:
                new_color.b++;
                break;
        }
//        shape[i] -> setFillColor(new_color);
    }
    return 0;
}
*/

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

//----------------------------------------------------------------------------------------
int Shapes::update()
{
    constexpr float kTwoPiOver360 = 2.0f * std::numbers::pi / 360.0f; // precomputed constant
    const float d = size * 0.5f;

    // Precompute reciprocal bounds once
    const float xBound = x_max - d;
    const float yBound = y_max - d;

    for (int i = 0; i < count; ++i)
    {
        auto shp = shape[i];                  // cache pointer
        auto& vel = velocity[i];               // reference for readability
        sf::Vector2f pos = shp->getPosition(); // local copy

        // Adjust speed (slightly faster growth)
        vel.speed *= 1.00001f;
        if (vel.speed < 0.0f)
            vel.speed = 0.0f;

        const float s = vel.speed;
        const float h = vel.heading;
        const float angleRad = h * kTwoPiOver360;

        // Compute displacement once
        const float dx = s * cos(angleRad);
        const float dy = s * sin(angleRad);

        pos.x += dx;
        pos.y += dy;

        // Bounce horizontally
        if (pos.x < d || pos.x + d > x_max)
        {
            vel.heading = 180.0f - h;
            const float newAngleRad = vel.heading * kTwoPiOver360;
            pos.x = (pos.x < d)
                ? d + s * cos(newAngleRad)
                : xBound - s * cos(newAngleRad);
        }

        // Bounce vertically
        if (pos.y < d || pos.y + d > y_max)
        {
            vel.heading = 360.0f - h;
            const float newAngleRad = vel.heading * kTwoPiOver360;
            pos.y = (pos.y < d)
                ? d + s * sin(newAngleRad)
                : yBound - s * sin(newAngleRad);
        }

        shp->setPosition(pos);

        // Rotation update (same logic)
        sf::Angle r = shp->getRotation();
        using namespace sf::Literals;
        r += (h > 180.0f ? -1.0_deg : 1.0_deg);
        shp->setRotation(r);

        /*
        // Color update (unchanged behavior)
        if (i % 3 == 0)
            shp->setFillColor({std::uint8_t(std::min(255, shp->getFillColor().r + 1)),
                               shp->getFillColor().g,
                               shp->getFillColor().b});
        else if (i % 3 == 1)
            shp->setFillColor({shp->getFillColor().r,
                               std::uint8_t(std::min(255, shp->getFillColor().g + 1)),
                               shp->getFillColor().b});
        else
            shp->setFillColor({shp->getFillColor().r,
                               shp->getFillColor().g,
                               std::uint8_t(std::min(255, shp->getFillColor().b + 1))});
        */
    }

    return 0;
}