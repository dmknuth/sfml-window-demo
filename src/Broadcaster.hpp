#ifndef __Broadcaster__
#define __Broadcaster__

#include <zmq.hpp>
#include <string>

//#include <nlohmann/json.hpp>

class Broadcaster
{
    public:
        Broadcaster(const int);
    
        int         run();
        void        send(std::string msg);
    
    private:
        std::unique_ptr<zmq::socket_t> publisher;
        std::unique_ptr<zmq::context_t> context;
};
#endif