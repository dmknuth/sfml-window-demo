#include <SFML/Graphics/RenderWindow.hpp>

class Window
{
    public:
        int     configure(u_int16_t, u_int16_t, float);
        int     create();
        int     process_events();
        
    private:
        u_int16_t           size_x;
        u_int16_t           size_y;
        sf::ContextSettings settings;
        sf::RenderWindow    _window;
};