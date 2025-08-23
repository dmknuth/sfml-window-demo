#ifndef __Window__
#define __Window__
#include <SFML/Graphics/RenderWindow.hpp>
#include "Balls.hpp"

class Window
{
    public:
        Window*     configure(u_int16_t, u_int16_t, float, bool);
        Window*     create();
        int         process_events();
        void        add_content(Balls*);
        
    private:
        bool                grid;
        u_int16_t           size_x;
        u_int16_t           size_y;
        sf::ContextSettings settings;
        sf::RenderWindow    _window;
        Balls*              content;
        int                 count;
        void        update_content();
        void        draw_grid();
};
#endif