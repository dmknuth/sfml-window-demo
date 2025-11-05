#include "Window.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include "FpsCounter.hpp"


const   bool    k_quit = false;

//----------------------------------------------------------------------------------------
Window*
Window::configure
(
    const struct arg_struct* args
)
{
    width = args -> width;
    height = args -> height;
    settings.antiAliasingLevel = args -> anti_alias;
    count = args -> count;
    size = args -> size;
    position.x = args -> pos_x;
    position.y = args -> pos_y;
    grid = args -> grid;
    return this;
}

//----------------------------------------------------------------------------------------
void
Window::create_grid()
{
    const int kGridSpacing = 50;
    int mid_x = width / 2;
    int mid_y = height / 2;
    sf::VertexArray lines(sf::PrimitiveType::Lines, 2);
    for(int x = mid_x; x < width; x += kGridSpacing)
    {
        lines[0].position = sf::Vector2f(x, 0);
        lines[1].position = sf::Vector2f(x, height);
        lines[0].color = lines[1].color = sf::Color(sf::Color(0, 128, 128, 32));
        grid_lines.push_back(lines);
        lines[0].position = sf::Vector2f(x - mid_x, 0);
        lines[1].position = sf::Vector2f(x - mid_x, height);
        lines[0].color = lines[1].color = sf::Color(sf::Color(0, 128, 128, 32));
        grid_lines.push_back(lines);
    }
    for(int y = mid_y; y < height; y += kGridSpacing)
    {
        lines[0].position = sf::Vector2f(0, y);
        lines[1].position = sf::Vector2f(width, y);
        lines[0].color = lines[1].color = sf::Color(sf::Color(0, 128, 128, 32));
        grid_lines.push_back(lines);
        lines[0].position = sf::Vector2f(0, y - mid_y);
        lines[1].position = sf::Vector2f(width, y - mid_y);
        lines[0].color = lines[1].color = sf::Color(sf::Color(0, 128, 128, 32));
        grid_lines.push_back(lines);
    }
}

//----------------------------------------------------------------------------------------
Window*
Window::create()
{
    _window = sf::RenderWindow(sf::VideoMode({width, height}), "Window Demo", sf::Style::Close, sf::State::Windowed, settings);
    _window.setPosition(position);
    if (!font.openFromFile("/snap/gnome-42-2204/202/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"))
        std::cerr << "Could not load font." << std::endl;
    font.setSmooth(true);
    create_grid();
    return this;
}

//----------------------------------------------------------------------------------------
void
Window::add_content(std::unique_ptr<Shapes> c)
{   
    content = std::move(c);
    assert(content != nullptr);
    content -> update();
}

//----------------------------------------------------------------------------------------
void
Window::update_content()
{
    assert(content != nullptr);
    content -> update();
}

//----------------------------------------------------------------------------------------
void
Window::draw_grid()
{
    for(auto i : grid_lines)
    {
        _window.draw(i);      
    }
}

//----------------------------------------------------------------------------------------
void
Window::display_instrumentation(double fps)
{
    const float k_leading = 12.0;
    const int k_font_size = 14;
    sf::Vector2f    pos({10.0f, 10.0f});

    // Count
    {
        std::ostringstream i_count;
        i_count << "Count: " << count;
        sf::Text count_str(font, i_count.str(), k_font_size);
        count_str.setFillColor(sf::Color::Black);
        count_str.setPosition(pos);
//        sf::FloatRect gb = count_str.getGlobalBounds();
//      std::cout << "g.pos(" << gb.position.x << ", " << gb.position.y << ")" << std::endl;
//      std::cout << "g.size(" << gb.size.x << ", " << gb.size.y << ")" << std::endl;
        _window.draw(count_str);
    }
    // Radius
    {
        std::ostringstream i_size;
        i_size << "Size: " << size;
        sf::Text size_str(font, i_size.str(), k_font_size);
        size_str.setFillColor(sf::Color::Black);
        pos.y += k_leading;
        size_str.setPosition(pos);
        _window.draw(size_str);
    }
    // Frame Rate
    {
        
        std::ostringstream frame_time;
      
        frame_time << std::setprecision(3) << "FPS: " << fps;
        sf::Text framerate(font, frame_time.str(), k_font_size);
        framerate.setFillColor(sf::Color::Black);
        pos.y += k_leading;
        framerate.setPosition(pos);
        _window.draw(framerate);
    }
 //   usleep(1);
}

//----------------------------------------------------------------------------------------
bool
Window::handle_keystrokes()
{
    while (const std::optional event = _window.pollEvent())
    {
         if (event->is<sf::Event::Closed>() ||
            (event->is<sf::Event::KeyPressed>() &&
            (event->getIf<sf::Event::KeyPressed>()->code) == sf::Keyboard::Key::Escape))
        {
            return false;
        }
    }
    return true;
}

//----------------------------------------------------------------------------------------
int
Window::process_events()
{
    FpsCounter fpsCounter;
    while (_window.isOpen())
    {
        if(handle_keystrokes() == k_quit)
        {
            _window.close();
            return -1;
        }
        else
        {
            _window.clear(sf::Color::White);
            if(grid)
                draw_grid();
            update_content();
            for(int i = 0; i < content -> get_count(); ++i)
            {
                _window.draw(content->get_item(i));
            }
            double fps = fpsCounter.update();
            display_instrumentation(fps);
            _window.display();
        }
    }
    return 0;
}