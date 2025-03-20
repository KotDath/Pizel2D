#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "imgui-SFML.h"

#include "DebugWindow.h"
#include "ConfigReader.h"
#include "MovingImage.h"
#include "Text.h"

class Window {
public:
    Window();
    void Run();

private:
    void Initialize();

    void UpdateUserInput();
    void UpdateLogic();
    void UpdateGui();

    void Render();

    DebugWindow m_debug;
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;
    bool m_isRun = true;
    std::vector<std::shared_ptr<RenderObject>> m_objects;
    Config m_config;
};

#endif // WINDOW_H
