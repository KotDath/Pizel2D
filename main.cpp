#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "ImGui-SFML Example");
    
    // Initialize ImGui with SFML
    ImGui::SFML::Init(window);

    // ImGui variables for demonstrating the interface
    bool showDemoWindow = true;intelliSenseEngine

    // Main loop
    sf::Clock deltaClock;
    while (window.isOpen()) {
        // Poll events
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Start a new ImGui frame
        ImGui::SFML::Update(window, deltaClock.restart());

        // Show ImGui demo window
        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);

        // Clear the window
        window.clear();
        
        // Render ImGui UI
        ImGui::SFML::Render(window);

        // Display everything
        window.display();
    }

    // Cleanup ImGui
    ImGui::SFML::Shutdown();
    return 0;
}
