#include "Window.hpp"

int main()
{
    Window* window = new Window();
    window -> configure(1920, 1080, 8.0);
    window -> create();
    window -> process_events();
    delete window;
    return 0;
}
