#include "Window.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h>

const   bool    k_quit = false;

//----------------------------------------------------------------------------------------
Window*
Window::configure
(
    u_int16_t   x,
    u_int16_t   y,
    float       anti_alias,
    u_int16_t   c,
    u_int16_t   r,
    bool        g
)
{
    width = x;
    height = y;
    settings.antiAliasingLevel = anti_alias;
    count = c;
    radius = r;
    grid = g;
    return this;
}

//----------------------------------------------------------------------------------------
Window*
Window::configure
(
    float       anti_alias,
    u_int16_t   c,
    u_int16_t   r,
    bool        g
)
{
    settings.antiAliasingLevel = anti_alias;
    count = c;
    radius = r;
    grid = g;
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
    if (!font.openFromFile("./resources/Monaco.ttf"))
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
Window::display_instrumentation()
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
        std::ostringstream i_radius;
        i_radius << "Radius: " << radius;
        sf::Text radius_str(font, i_radius.str(), k_font_size);
        radius_str.setFillColor(sf::Color::Black);
        pos.y += k_leading;
        radius_str.setPosition(pos);
        _window.draw(radius_str);
    }
    // Frame Rate
    {
        const int k_frame_max = 1000;
        static double fps = (double)k_frame_max;
        std::ostringstream frame_time;
        static int frames = 0;
        static std::chrono::time_point<std::chrono::system_clock> last_time;
        auto current_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = current_time - last_time;
        frames++;
        frame_time << "FPS: " << fps;
        if(frames >= k_frame_max)
        {
            fps = (double)k_frame_max / elapsed_seconds.count();
            last_time = current_time;
            frames = 0;
        }
        sf::Text framerate(font, frame_time.str(), k_font_size);
        framerate.setFillColor(sf::Color::Black);
        pos.y += k_leading;
        framerate.setPosition(pos);
        _window.draw(framerate);
    }
    usleep(1);
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
            display_instrumentation();
            _window.display();
        }
    }
    return 0;
}