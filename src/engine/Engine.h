#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include "../graphics/Tileset.h"
#include "../assets/AssetManager.h"
#include "../map/Map.h"
#include "../editors/panels/EditorUI.h"


#include <filesystem>
#include <optional>

class Engine
{
public:
    explicit Engine(const std::filesystem::path &projectRoot);

    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    bool initialize();

    void run();

    void shutdown();

private:
    bool running = false;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;


    AssetManager assets;
    Tileset tileset;
    std::optional<Map> currentMap;

    EditorState editorState;
    EditorUI editorUi;


    EditorContext context{
        currentMap,
        tileset,
        editorState,
    };
};
