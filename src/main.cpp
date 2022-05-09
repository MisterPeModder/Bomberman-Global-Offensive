#include <iostream>
#include "raylib/Window.hpp"
#include <unistd.h>

int main()
{
    raylib::Window window;

    window.open(1200, 800, "hell oworld");
    sleep(5);
    window.close();
}
