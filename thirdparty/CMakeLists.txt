include(FetchContent)

set(SFML_VERSION 3.0.0)
set(IMGUI_VERSION 1.91.8)
set(IMGUI_SFML_VERSION 3.0)
set(JSON_VERSION 3.11.3)

FetchContent_Declare(
  SFML
  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

FetchContent_Declare(
  imgui
  URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)

FetchContent_Declare(
  imgui-sfml
  URL "https://github.com/SFML/imgui-sfml/archive/v${IMGUI_SFML_VERSION}.zip"
)

FetchContent_Declare(
  json
  URL "https://github.com/nlohmann/json/archive/refs/tags/v${JSON_VERSION}.zip"
)

# SFML
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" OFF)

FetchContent_MakeAvailable(imgui-sfml)

# JSON
FetchContent_MakeAvailable(json)
