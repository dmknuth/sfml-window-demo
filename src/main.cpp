#include "Window.hpp"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

const   u_int16_t   k_width = 640;
const   u_int16_t   k_height = 480;
const   float       k_anti_alias = 1.1;
const   u_int16_t   k_count = 1;
const   u_int16_t   k_radius = 20;
const   bool        k_grid = false;

struct arg_struct
{
    u_int16_t   width;
    u_int16_t   height;
    float       anti_alias;
    u_int16_t   count;
    u_int16_t   radius;
    bool        grid;
};

//----------------------------------------------------------------------------------------
// Return true to continue running the application.
// Return false to exit the application.

bool
process_args
(
    int                 argc,
    char*               argv[],
    struct arg_struct*  arg_list
)
{
    for(;;)
    {
        switch(getopt(argc, argv, "a:c:ghr:vx:y:"))
        {
            case 'a':
              arg_list -> anti_alias = std::strtof(optarg, 0);
//              std::cout << "anti_alias " << anti_alias << std::endl;
              continue;
        
            case 'c':
              arg_list -> count = std::atoi(optarg);
//              std::cout << "count " << count << std::endl;
              continue;
        
            case 'g':
              arg_list -> grid = true;
              continue;
        
            case 'r':
              arg_list -> radius = std::atoi(optarg);
//              std::cout << "radius " << radius << std::endl;
              continue;
        
            case 'v':
              {
                  std::string version{"0.1.0"};
//                  std::cout << "Version " << version << std::endl;
                  return false;
              }
        
            case 'x':
              arg_list -> width = std::atoi(optarg);
//              std::cout << "size_x " << size_x << std::endl;
              continue;
        
            case 'y':
              arg_list -> height = std::atoi(optarg);
//              std::cout << "size_y " << size_y << std::endl;
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
                std::cout << "-x set the width of the window to create. The default is " << k_width << "." << std::endl;
                std::cout << "-y set the height of the window to create. The default is " << k_height << "." << std::endl;
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
void
init_arg_struct(struct arg_struct& arg_list)
{
    arg_list.width = k_width;
    arg_list.height = k_height;
    arg_list.anti_alias = k_anti_alias;
    arg_list.count = k_count;
    arg_list.radius = k_radius;
    arg_list.grid = k_grid;
}

//----------------------------------------------------------------------------------------
std::unique_ptr<Shapes>
create_shapes(const struct arg_struct* arg_list)
{
//    Shapes* shape_vector = new Shapes();
    auto shape_vector = std::make_unique<Shapes>();
    if(shape_vector == nullptr)
    {
        std::cerr << "shape_vector could not be created" << std::endl;
        return nullptr;
    }
    shape_vector -> set_size(arg_list -> radius);
    shape_vector -> set_count(arg_list -> count);
    shape_vector -> set_boundaries(arg_list -> width, arg_list -> height);
    shape_vector -> generate();
    return shape_vector;
}

//----------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{

    struct arg_struct arg_list;
    init_arg_struct(arg_list);
    
    if(process_args(argc, argv, &arg_list) == true)
    {
       auto window = std::make_unique<Window>();
        if(window != nullptr)
        {
            window -> configure(arg_list.width, arg_list.height, arg_list.anti_alias, arg_list.count, arg_list.radius, arg_list.grid) -> create();
            std::unique_ptr<Shapes> shape_vector = std::move(create_shapes(&arg_list));
            if(shape_vector != nullptr)
            {
                window -> add_content(std::move(shape_vector));
                window -> process_events();
            }
            else
            {
                std::cerr << "shapes could not be created" << std::endl;
                return -1;
            }
        }
        else
        {
            std::cerr << "window could not be created" << std::endl;
            return -1;
        }
    }
    return 0;
}
