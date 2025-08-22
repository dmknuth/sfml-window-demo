#include "Window.hpp"
#include <cstdlib>
#include <iostream>

//----------------------------------------------------------------------------------------
bool
process_args
(
    int         argc,
    char*       argv[],
    u_int16_t&  x,
    u_int16_t&  y,
    float&      anti_alias
)
{
    switch (argc)
    {
        case 4:
            anti_alias = std::strtof(argv[3], 0);
        case 3:
            y = std::atoi(argv[2]);
        case 2:
            x = std::atoi(argv[1]);
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

    if(process_args(argc, argv, x, y, anti_alias) == true)
    {
    
        Window* window = new Window();
        window -> configure(x, y, anti_alias) -> create();
        Balls* ball_machine = new Balls(10, 20);
        if(ball_machine == nullptr)
        {
            std::cout << "ball_machine is NULL" << std::endl;
            return -1;
        }

        window -> add_content(ball_machine);
        window -> process_events();
        delete window;
        return -1;
    }
    return 0;
}
