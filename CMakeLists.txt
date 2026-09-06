cmake_minimum_required(VERSION 3.25)

project(Rpgmaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# Dependencies
# =========================

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# =========================
# Executable
# =========================

add_executable(Rpgmaker
src/main.cpp

src/engine/Engine.cpp
src/engine/Engine.h

src/graphics/Tileset.cpp
src/graphics/Tileset.h

src/assets/AssetManager.cpp
src/assets/AssetManager.h
        src/map/Map.cpp
        src/map/Map.h
        src/editors/EditorUI.cpp
        src/editors/EditorUI.h
        src/editors/MapEditor.cpp
        src/editors/MapEditor.h
)

# =========================
# Libraries
# =========================

target_link_libraries(Rpgmaker PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        imgui::imgui
        fmt::fmt
        nlohmann_json::nlohmann_json
        tinyxml2::tinyxml2
)

# =========================
# Project root
# =========================

target_compile_definitions(Rpgmaker PRIVATE
RPGMAKER_PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)