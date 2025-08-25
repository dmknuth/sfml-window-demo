#ifndef __Shapes__
#define __Shapes__
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

struct shape_struct
{
    float   heading;
    float   speed;
};

class Shapes
{
    public:
        void            set_size(u_int16_t);
        void            set_count(u_int16_t);
        void            set_boundaries(u_int16_t, u_int16_t);
        void            generate();
        int             update();
        sf::RectangleShape get_item(int i);
        int             get_count() { return count; }
        
    private:
        std::vector<std::unique_ptr<sf::RectangleShape>> shape;
        std::vector<shape_struct>       velocity;

        sf::RenderWindow                _window;
        u_int16_t                       radius;
        u_int16_t                       count;
        u_int16_t                       x_max;
        u_int16_t                       y_max;
        
        sf::Color                       random_color();
};
#endif