#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

//----------------------------------------------------------------------------------------
int
Window::configure
(
    u_int16_t   x,
    u_int16_t   y,
    float       anti_alias
)
{
    size_x = {x};
    size_y = {y};
    settings.antiAliasingLevel = anti_alias;
    return 0;
}

//----------------------------------------------------------------------------------------
int
Window::create()
{
    _window = sf::RenderWindow(sf::VideoMode({size_x, size_y}), "Window Demo", sf::Style::Close, sf::State::Windowed, settings);
    return 0;
}

//----------------------------------------------------------------------------------------
int
Window::process_events()
{
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color::Cyan);

    while (_window.isOpen())
    {
        while (const std::optional event = _window.pollEvent())
        {
             if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                (event->getIf<sf::Event::KeyPressed>()->code) == sf::Keyboard::Key::Escape))
            {
                _window.close();
            }
        }

//        update_shape(shape);
        _window.clear(sf::Color::White);
        _window.draw(shape);
        _window.display();
    }
    return 0;
}