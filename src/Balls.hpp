#ifndef __Balls__
#define __Balls__
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

class Balls
{
    public:
                    Balls(u_int16_t, u_int16_t);
        int         update();
        sf::CircleShape get_item(int i);
        int         get_count() { return count; }
        
    private:
        u_int16_t   radius;
        u_int16_t   count;
        std::vector<sf::CircleShape*> ball;
        
        std::uint8_t    distribution_generator();
        sf::Color       random_color();
        sf::RenderWindow    _window;

};
#endif