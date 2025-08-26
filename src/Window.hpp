#ifndef __Window__
#define __Window__
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Shapes.hpp"

class Window
{
    public:
        Window*     configure(u_int16_t, u_int16_t, float, u_int16_t, u_int16_t, bool);
        Window*     create();
        int         process_events();
        void        add_content(Shapes*);
        
    private:
        bool                grid;
        u_int16_t           size_x;
        u_int16_t           size_y;
        sf::ContextSettings settings;
        sf::RenderWindow    _window;
        Shapes*             content;
        u_int16_t           count;
        u_int16_t           radius;
        sf::Font            font;
        void        update_content();
        void        draw_grid();
        void        display_instrumentation();
};
#endif
