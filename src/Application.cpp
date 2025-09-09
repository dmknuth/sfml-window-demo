#include "Application.hpp"
#include "Window.hpp"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <cassert>

const   u_int16_t   k_width = 800;
const   u_int16_t   k_height = 600;
const   u_int16_t   k_pos_x = 50;
const   u_int16_t   k_pos_y = 50;
const   float       k_anti_alias = 1.1;
const   u_int16_t   k_count = 10;
const   u_int16_t   k_size = 20;
const   bool        k_grid = false;

//----------------------------------------------------------------------------------------
// Return true to continue running the application.
// Return false to exit the application.

bool
Application::process_args
(
    int                 argc,
    char*               argv[],
    struct arg_struct*  arg_list
)
{
    for(;;)
    {
        switch(getopt(argc, argv, "a:c:ghr:s:vw:x:y:"))
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
        
            case 's':
              arg_list -> size = std::atoi(optarg);
//              std::cout << "size " << size << std::endl;
              continue;
        
            case 'v':
              {
                  std::string version{"0.1.0"};
//                  std::cout << "Version " << version << std::endl;
                  return false;
              }
        
            case 'w':
              arg_list -> width = std::atoi(optarg);
//              std::cout << "size_x " << size_x << std::endl;
              continue;
        
            case 'h':
              arg_list -> height = std::atoi(optarg);
//              std::cout << "size_y " << size_y << std::endl;
              continue;
        
            case 'x':
              arg_list -> pos_x = std::atoi(optarg);
//              std::cout << "pos_x " << pos_x << std::endl;
              continue;
        
            case 'y':
              arg_list -> pos_y = std::atoi(optarg);
//              std::cout << "size_y " << size_y << std::endl;
              continue;
        
            case '?':
            default :
                std::cout << "usage:" << std::endl;
                std::cout << "-a set the antialias amount.  The higher the number, the fuzzier the edges of the objects. The default is " << k_anti_alias << "." << std::endl;
                std::cout << "-c set the number of objects to create. The default is " << k_count << "." << std::endl;
                std::cout << "-g to display a grid. The default is no grid." << std::endl;
                std::cout << "-h or any other character to display this message." << std::endl;
                std::cout << "-r set the size of the objects. The default is " << k_size << "." << std::endl;
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
Application::init_arg_struct(struct arg_struct& arg_list)
{
    arg_list.width = k_width;
    arg_list.height = k_height;
    arg_list.anti_alias = k_anti_alias;
    arg_list.count = k_count;
    arg_list.size = k_size;
    arg_list.pos_x = k_pos_x;
    arg_list.pos_y = k_pos_y;
    arg_list.grid = k_grid;
}

//----------------------------------------------------------------------------------------
std::unique_ptr<Shapes>
Application::create_shapes(const struct arg_struct* arg_list)
{
//    Shapes* shape_vector = new Shapes();
    auto shape_vector = std::make_unique<Shapes>();
    assert(shape_vector != nullptr);
    shape_vector -> set_size(arg_list -> size);
    shape_vector -> set_count(arg_list -> count);
    shape_vector -> set_boundaries(arg_list -> width, arg_list -> height);
    shape_vector -> generate();
    return shape_vector;
}

//----------------------------------------------------------------------------------------
Application::Application(int argc, char* argv[])
{
    init_arg_struct(arg_list);

    if(process_args(argc, argv, &arg_list) != true)
        quit = true;
}

//----------------------------------------------------------------------------------------
int
Application::run()
{  
    if(quit)
        return -1;
    auto window = std::make_unique<Window>();
    assert(window != nullptr);

    window -> configure(&arg_list) -> create();
    std::unique_ptr<Shapes> shape_vector = std::move(create_shapes(&arg_list));
    assert(shape_vector != nullptr);

    window -> add_content(std::move(shape_vector));
    window -> process_events();

    return 0;
}
