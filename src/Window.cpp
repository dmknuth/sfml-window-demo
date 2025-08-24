#include "Window.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

//----------------------------------------------------------------------------------------
Window*
Window::configure
(
    u_int16_t   x,
    u_int16_t   y,
    float       anti_alias,
    bool        g
)
{
    size_x = x;
    size_y = y;
    settings.antiAliasingLevel = anti_alias;
    grid = g;
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
Window::add_content(Shapes* c)
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
void
Window::draw_grid()
{
    const int kGridSpacing = 50;
    int mid_x = size_x / 2;
    int mid_y = size_y / 2;
    sf::VertexArray lines(sf::PrimitiveType::Lines, 2);
    for(int x = mid_x; x < size_x; x += kGridSpacing)
    {
        lines[0].position = sf::Vector2f(x, 0);
        lines[1].position = sf::Vector2f(x, size_y);
        lines[0].color = lines[1].color = sf::Color(sf::Color(0, 128, 128, 32));
        _window.draw(lines);        
        lines[0].position = sf::Vector2f(x - mid_x, 0);
        lines[1].position = sf::Vector2f(x - mid_x, size_y);
        lines[0].color = lines[1].color = sf::Color(sf::Color(0, 128, 128, 32));
        _window.draw(lines);        
    }
    for(int y = mid_y; y < size_y; y += kGridSpacing)
    {
        lines[0].position = sf::Vector2f(0, y);
        lines[1].position = sf::Vector2f(size_x, y);
        lines[0].color = lines[1].color = sf::Color(sf::Color(0, 128, 128, 32));
        _window.draw(lines);        
        lines[0].position = sf::Vector2f(0, y - mid_y);
        lines[1].position = sf::Vector2f(size_x, y - mid_y);
        lines[0].color = lines[1].color = sf::Color(sf::Color(0, 128, 128, 32));
        _window.draw(lines);        
    }
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
        if(grid)
            draw_grid();
        update_content();
        for(int i = 0; i < content -> get_count(); ++i)
        {
            _window.draw(content->get_item(i));
/*
            sf::FloatRect temp;
            temp = content->get_item(i).getGlobalBounds();
            sf::RectangleShape rect;
            rect.setSize(temp);
            _window.draw(temp);
*/
        }
        _window.display();
    }
    return 0;
}