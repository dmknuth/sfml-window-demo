#include "Window.hpp"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

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
          printf("Help/Usage Example\n");
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
    u_int16_t   x = 640;
    u_int16_t   y = 480;
    float       anti_alias = 1.0;
    u_int16_t   count = 1;
    u_int16_t   radius = 20;
    bool        grid = false;
    
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
