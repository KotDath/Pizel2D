#include "Window.h"

#include "ConfigReader.h"

Window::Window() {
  m_config = ConfigReader::LoadConfig(CONFIG_PATH);
  m_window.create(sf::VideoMode({m_config.width, m_config.height}), "Pizel2D");

  auto desktop = sf::VideoMode::getDesktopMode();
  m_window.setPosition({(int)(desktop.size.x / 2 - m_config.width / 2),
                        (int)(desktop.size.y / 2 - m_config.height / 2)});

  m_window.setFramerateLimit(144);

  ImGui::SFML::Init(m_window);

  ImGui::GetStyle().ScaleAllSizes(1.0f);
  // ImGui::GetIO().FontGlobalScale = 2.0f;

  Initialize();
}

void Window::Initialize() {
  // Все эти дефолтные данные надо будет прочитать из конфигурационного файла
  auto m_rect = std::make_shared<MovingImage>();
  std::filesystem::path imagePath = m_config.logos[0];
  m_rect->LoadImage(imagePath);
  m_rect->SetPosition({100.0f, 10.0f});
  m_rect->SetSpeed(m_config.speed, m_config.angle);
  m_rect->SetScale(m_config.scale);

  std::filesystem::path fontPath =
      std::filesystem::path(ASSET_DIR) / "fonts" / "Minecraft.ttf";

  auto m_text = std::make_shared<Text>(fontPath, L"PAUSE", 24);
  float xPos = m_window.getSize().x / 2;
  float yPos = m_window.getSize().y / 2 - (float)m_text->GetCharacterSize();
  m_text->SetPosition({xPos, yPos});

  DebugData newData;
  newData.speedValue = m_config.speed;
  newData.items = m_config.logos;
  newData.sizeValue = m_config.scale;
  newData.color[0] = m_config.rColor;
  newData.color[1] = m_config.gColor;
  newData.color[2] = m_config.bColor;

  m_debug.setDebugData(newData);

  m_objects.push_back(m_rect);
  m_objects.push_back(m_text);
}

void Window::Run() {
  while (m_isRun) {
    sf::Time delta = m_deltaClock.restart();
    ImGui::SFML::Update(m_window, delta);

    UpdateUserInput();
    UpdateLogic();
    UpdateGui();
    Render();
  }

  m_window.close();
  ImGui::SFML::Shutdown();
}

void Window::UpdateUserInput() {
  while (const std::optional event = m_window.pollEvent()) {
    ImGui::SFML::ProcessEvent(m_window, *event);

    if (event->is<sf::Event::Closed>()) {
      m_isRun = false;
    } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      std::wcout
          << L"Key pressed with code = "
          << sf::Keyboard::getDescription(keyPressed->scancode).toWideString()
          << "\n";

      if (keyPressed->code == sf::Keyboard::Key::Space) {
        for (const auto& object : m_objects) {
          object->SwitchPause();
        }
      }
      if (keyPressed->code == sf::Keyboard::Key::Escape) {
        m_isRun = false;
      }
    }
  }
}

void Window::UpdateLogic() {
  for (const auto& object : m_objects) {
    object->Update(m_window);
  }
}

void Window::UpdateGui() {
  auto rect = std::static_pointer_cast<MovingImage>(m_objects[0]);
  auto text = std::static_pointer_cast<Text>(m_objects[1]);
  m_debug.Render(rect, text);
}

void Window::Render() {
  m_window.clear();

  for (const auto& object : m_objects) {
    object->Draw(m_window);
  }

  ImGui::SFML::Render(m_window);
  m_window.display();
}
