#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <cmath>
#include <numbers>
#include <unistd.h>

const int max_x = 1920u;
const int max_y = 1080u;

void update_shape(sf::CircleShape& shape)
{
    static float x = max_x / 2.0;
    static float y = max_y / 2.0;
    static float a = 0.0;
    static float r = 2.0;
    static float i = 0.5;
    static float d = 0.01;
    
    shape.setRadius(40.f);
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color::Red);
    x = (max_x / 2.0) + (r * std::cos(a / (2.0 * std::numbers::pi)));
    if ((x > max_x) || (x < 0.0))
        x = max_x / 2.0;
    y = (max_y / 2.0) + (r * std::sin(a / (2.0 * std::numbers::pi)));
    if ((y > max_y) || (y < 0.0))
        y = max_y / 2.0;
        
//    a += rand() % 5;
    a += d;
    if(a > 360.0)
        a = 0.0;
    if(a < 0.0)
        a = 360.0;
    r += i;
    if((r > std::fmin(max_x / 2.0, max_y / 2.0)) || (r < 0.0))
        i *= -1;
//    std::cout << "x " << x << "   y " << y << "   a " << a << "   r " << r << std::endl;
}

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8.0;
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Window Demo", sf::Style::Close, sf::State::Windowed, settings);
    window.setFramerateLimit(144);

    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
             if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                (event->getIf<sf::Event::KeyPressed>()->code) == sf::Keyboard::Key::Escape))
            {
                window.close();
            }
        }

        update_shape(shape);
        window.clear(sf::Color::White);
        window.draw(shape);
        window.display();
    }
}
