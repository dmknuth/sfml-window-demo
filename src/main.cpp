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
// Return true to continue running the application.
// Return false to exit the application.

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
        switch(getopt(argc, argv, "a:c:ghr:vx:y:"))
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
        
            case 'v':
              {
                  std::string version{"0.1.0"};
                  std::cout << "Version " << version << std::endl;
                  return false;
              }
        
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
                std::cout << "-a set the antialias amount.  The higher the number, the fuzzier the edges of the objects. The default is " << k_anti_alias << "." << std::endl;
                std::cout << "-c set the number of objects to create. The default is " << k_count << "." << std::endl;
                std::cout << "-g to display a grid. The default is no grid." << std::endl;
                std::cout << "-h or any other character to display this message." << std::endl;
                std::cout << "-r set the radius of the objects. The default is " << k_radius << "." << std::endl;
                std::cout << "-v display version of this application." << std::endl;
                std::cout << "-x set the width of the window to create. The default is " << k_x << "." << std::endl;
                std::cout << "-y set the height of the window to create. The default is " << k_y << "." << std::endl;
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
        if(window != nullptr)
        {
            window -> configure(x, y, anti_alias, grid) -> create();
            Shapes* shape_vector = new Shapes();
            if(shape_vector == nullptr)
            {
                std::cerr << "shape_vector could not be created" << std::endl;
                return -1;
            }
            shape_vector -> set_size(radius);
            shape_vector -> set_count(count);
            shape_vector -> set_boundaries(x, y);
            shape_vector -> generate();
            window -> add_content(shape_vector);
            window -> process_events();
            delete window;
        }
        else
        {
            std::cerr << "window could not be created" << std::endl;
            return -1;
        }
        
    }
    return 0;
}
