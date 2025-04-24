# Configuration for third-party libraries
# All libraries are included as Git submodules

# SFML
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SFML/CMakeLists.txt")
    add_subdirectory(SFML)
else()
    message(FATAL_ERROR "SFML submodule not initialized. Run 'git submodule update --init --recursive'")
endif()

# Dear ImGui
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h")
    set(IMGUI_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    )
    add_library(imgui STATIC ${IMGUI_SOURCES})
    target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
else()
    message(FATAL_ERROR "ImGui submodule not initialized. Run 'git submodule update --init --recursive'")
endif()

# ImGui-SFML
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui-sfml/CMakeLists.txt")
    set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
    option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
    option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" OFF)
    add_subdirectory(imgui-sfml)
else()
    message(FATAL_ERROR "ImGui-SFML submodule not initialized. Run 'git submodule update --init --recursive'")
endif()

# nlohmann-json
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/json/CMakeLists.txt")
    add_subdirectory(json EXCLUDE_FROM_ALL)
else()
    message(FATAL_ERROR "nlohmann-json submodule not initialized. Run 'git submodule update --init --recursive'")
endif()
