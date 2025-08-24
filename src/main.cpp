#include "Window.hpp"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

const   u_int16_t   k_x = 640;
const   u_int16_t   k_y = 480;
const   float       k_anti_alias = 1.1;
const   u_int16_t   k_count = 1;
const   u_int16_t   k_radius = 20;
const   bool        k_grid = false;

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
    u_int16_t&  radius,
    bool&       grid
)
{
    for(;;)
    {
      switch(getopt(argc, argv, "a:c:ghr:x:y:"))
      {
        case 'a':
          anti_alias = std::strtof(optarg, 0);
          std::cout << "anti_alias " << anti_alias << std::endl;
          continue;
    
        case 'c':
          count = std::atoi(optarg);
          std::cout << "count " << count << std::endl;
          continue;
    
        case 'g':
          grid = true;
          continue;
    
        case 'r':
          radius = std::atoi(optarg);
          std::cout << "radius " << radius << std::endl;
          continue;
    
        case 'x':
          size_x = std::atoi(optarg);
          std::cout << "size_x " << size_x << std::endl;
          continue;
    
        case 'y':
          size_y = std::atoi(optarg);
          std::cout << "size_y " << size_y << std::endl;
          continue;
    
        case '?':
        case 'h':
        default :
        std::cout << "usage:" << std::endl;
        std::cout << "-x set the width of the window to create. The default is " << k_x << "." << std::endl;
        std::cout << "-y set the height of the window to create. The default is " << k_y << "." << std::endl;
        std::cout << "-a set the antialias amount.  The higher the number, the fuzzier the edges of the objects. The default is " << k_anti_alias << "." << std::endl;
        std::cout << "-c set the number of objects to create. The default is " << k_count << "." << std::endl;
        std::cout << "-r set the radius of the objects. The default is " << k_radius << "." << std::endl;
        std::cout << "-g to display a grid. The default is no grid." << std::endl;
        std::cout << "-h or any other character to display this message." << std::endl;
        return false;
            break;    
    
        case -1:
            break;
    }
      break;
    }
    return true;
}

//----------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    u_int16_t   x = k_x;
    u_int16_t   y = k_y;
    float       anti_alias = k_anti_alias;
    u_int16_t   count = k_count;
    u_int16_t   radius = k_radius;
    bool        grid = k_grid;
    
    if(process_args(argc, argv, x, y, anti_alias, count, radius, grid) == true)
    {
    
        Window* window = new Window();
        window -> configure(x, y, anti_alias, grid) -> create();
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
