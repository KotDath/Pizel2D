#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "ConfigReader.h"
#include "DebugWindow.h"
#include "MovingImage.h"
#include "Text.h"
#include "imgui-SFML.h"

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

#endif  // WINDOW_H
