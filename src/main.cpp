#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "Window.h"
#include "ecs/FilterBuilder.h"
#include "ecs/Movement/C_Movement.h"
#include "ecs/Transform/C_Transform.h"
#include "ecs/World.h"

int main() {
  // Create an SFML window
  /*
  Window window;
  window.Run();
  */

  World world;
  const int player = world.CreateEntity();
  auto& positionsStorage = world.GetStorage<C_Transform>();
  positionsStorage.Add(player, C_Transform(4, 3));

  const int player2 = world.CreateEntity();
  auto& positionsStorage2 = world.GetStorage<C_Transform>();
  positionsStorage2.Add(player2, C_Transform(5, 6));

  world.RemoveEntity(player);

  Filter filter =
      FilterBuilder(world).With<C_Transform>().Build();
  auto& positionComponents = world.GetStorage<C_Transform>();
  
  for (const auto& entity : filter) {
    auto& cPosition = positionComponents.Ref(entity);
    cPosition.x += 1;
    std::cout << entity << ": " << "(" << cPosition.x << ", " << cPosition.y << ")" << std::endl;
  }
  return 0;
}
