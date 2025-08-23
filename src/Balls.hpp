#ifndef __Balls__
#define __Balls__
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

struct ball_struct
{
    float   direction;
    float   speed;
};

class Balls
{
    public:
        void        set_size(u_int16_t);
        void        set_count(u_int16_t);
        void        set_boundaries(u_int16_t, u_int16_t);
        void        generate();
        int         update();
        sf::CircleShape get_item(int i);
        int         get_count() { return count; }
        
    private:
        u_int16_t   radius;
        u_int16_t   count;
        u_int16_t   x_max;
        u_int16_t   y_max;
        std::vector<sf::CircleShape*> ball;
        std::vector<ball_struct> velocity;
        
        std::uint8_t    distribution_generator();
        sf::Color       random_color();
        sf::RenderWindow    _window;

};
#endif