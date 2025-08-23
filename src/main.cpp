#include "Window.hpp"
#include <cstdlib>
#include <iostream>

//----------------------------------------------------------------------------------------
bool
process_args
(
    int         argc,
    char*       argv[],
    u_int16_t&  size_x,
    u_int16_t&  size_y,
    float&      anti_alias,
    u_int16_t&  count,
    u_int16_t&  radius
)
{
    switch (argc)
    {
        case 6:
            radius = std::atoi(argv[5]);
        case 5:
            count = std::atoi(argv[4]);
        case 4:
            anti_alias = std::strtof(argv[3], 0);
        case 3:
            size_y = std::atoi(argv[2]);
        case 2:
            size_x = std::atoi(argv[1]);
            break;
        default:
            break;
    }
    return true;
}

//----------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    u_int16_t   x = 640;
    u_int16_t   y = 480;
    float       anti_alias = 1.0;
    u_int16_t   count = 1;
    u_int16_t   radius = 20;

    if(process_args(argc, argv, x, y, anti_alias, count, radius) == true)
    {
    
        Window* window = new Window();
        window -> configure(x, y, anti_alias) -> create();
        Balls* ball_machine = new Balls();
        if(ball_machine == nullptr)
        {
            std::cout << "ball_machine is NULL" << std::endl;
            return -1;
        }
        ball_machine -> set_size(radius);
        ball_machine -> set_count(count);
        ball_machine -> set_boundaries(x, y);
        ball_machine -> generate();

        window -> add_content(ball_machine);
        window -> process_events();
        delete window;
    }
    return 0;
}
