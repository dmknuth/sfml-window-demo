#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include "Broadcaster.hpp"
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//----------------------------------------------------------------------------------------
Broadcaster::Broadcaster(const int kPort)
{
    context = std::make_unique<zmq::context_t>(1);
    publisher = std::make_unique<zmq::socket_t>(*context, ZMQ_PUB);
    std::ostringstream port;
    port << "tcp://*:" << kPort;
    publisher -> bind(port.str());
    std::cout << "Broadcasting on " << port.str() << std::endl;
};

//----------------------------------------------------------------------------------------
int
Broadcaster::run()
{
    return 0;
};

//----------------------------------------------------------------------------------------
void
Broadcaster::send(std::string not_used)
{
    json msg;
    msg = {
        {"type", "mouse_up"},
        {"button", not_used.c_str()},
        {"x", 1.234},
        {"y", 2.345}
    };

    if (!msg.empty()) {
        std::string payload = msg.dump();
        zmq::message_t zmq_msg(payload.size());
        std::memcpy(zmq_msg.data(), payload.data(), payload.size());
        publisher -> send(zmq_msg, zmq::send_flags::none);
    }
}

