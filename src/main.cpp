#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

#include "Window.h"

int main()
{
    // Create an SFML window
    Window window;
    window.Run();
    return 0;
}
