#ifndef __Application__
#define __Application__
#include "Shapes.hpp"

struct arg_struct
{
    u_int16_t   width;
    u_int16_t   height;
    float       anti_alias;
    u_int16_t   count;
    u_int16_t   radius;
    bool        grid;
};

class Application
{
    public:
        Application(int argc, char* argv[]);
        bool        process_args(int, char*[], struct arg_struct*  arg_list);
        void        init_arg_struct(struct arg_struct&);
        std::unique_ptr<Shapes> create_shapes(const struct arg_struct*);
        int         run();
        
    private:
        bool        quit = false;
        struct arg_struct arg_list;
};
#endif