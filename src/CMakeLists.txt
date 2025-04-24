set(TARGET_NAME main)
set(ASSET_DIR "${CMAKE_SOURCE_DIR}/assets")
set(CONFIG_PATH "${ASSET_DIR}/configs/main_config.json")
set(SOURCES main.cpp
Window.h Window.cpp
DebugWindow.h DebugWindow.cpp
ConfigReader.h ConfigReader.cpp
Text.h Text.cpp
Rectangle.h Rectangle.cpp
RenderObject.h RenderObject.cpp
MovingImage.h MovingImage.cpp
)

# Recursively find all source and header files in the ecs directory
file(GLOB_RECURSE ECS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ecs/*.cpp")
file(GLOB_RECURSE ECS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/ecs/*.h")

# Add ECS files to sources
list(APPEND SOURCES ${ECS_SOURCES} ${ECS_HEADERS})

add_executable(${TARGET_NAME} 
    ${SOURCES})

# Add ecs directory to include paths
target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ecs")
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_compile_definitions(${TARGET_NAME} PRIVATE ASSET_DIR="${ASSET_DIR}" CONFIG_PATH="${CONFIG_PATH}")
target_link_libraries(${TARGET_NAME} PUBLIC ImGui-SFML::ImGui-SFML nlohmann_json::nlohmann_json)
