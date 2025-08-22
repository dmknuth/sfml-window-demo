#include "Window.hpp"
#include "Balls.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

//----------------------------------------------------------------------------------------
Window*
Window::configure
(
    u_int16_t   x,
    u_int16_t   y,
    float       anti_alias
)
{
    size_x = x;
    size_y = y;
    settings.antiAliasingLevel = anti_alias;
    return this;
}

//----------------------------------------------------------------------------------------
Window*
Window::create()
{
    _window = sf::RenderWindow(sf::VideoMode({size_x, size_y}), "Window Demo", sf::Style::Close, sf::State::Windowed, settings);
    return this;
}

//----------------------------------------------------------------------------------------
void
Window::add_content(Balls* c)
{   
    content = c;
    if(content != nullptr)
        content -> update();
    else
        std::cout << "No content" << std::endl;
}

//----------------------------------------------------------------------------------------
void
Window::update_content()
{
    if(content != nullptr)
        content -> update();
    else
        exit(-2);
}

//----------------------------------------------------------------------------------------
int
Window::process_events()
{
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
        
        _window.clear(sf::Color::White);
        update_content();
        for(int i = 0; i < content -> get_count(); ++i)
            _window.draw(content->get_item(i));
        _window.display();
    }
    return 0;
}