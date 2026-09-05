#include "Engine.h"


#include <fmt/core.h>

Engine::Engine(const std::filesystem::path &projectRoot, Map map)
        : assets(projectRoot), map(map) {
}

Engine::~Engine()
{
    shutdown();
}

bool Engine::initialize()
{
    // SDL

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        fmt::print(
                "SDL_Init failed: {}\n",
                SDL_GetError()
        );

        return false;
    }

    // Window

    window = SDL_CreateWindow(
            "RpgMaker",
            1280,
            720,
            SDL_WINDOW_RESIZABLE
    );

    if (!window)
    {
        fmt::print(
                "SDL_CreateWindow failed: {}\n",
                SDL_GetError()
        );

        SDL_Quit();

        return false;
    }

    // Renderer

    renderer = SDL_CreateRenderer(
            window,
            nullptr
    );

    if (!renderer)
    {
        fmt::print(
                "SDL_CreateRenderer failed: {}\n",
                SDL_GetError()
        );

        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_Quit();

        return false;
    }

    // Load tileset

    const auto tilesetPath = assets.data("tilesets/punyworld-overworld-tiles.tsx");

    if (!tileset.load(
            renderer,
            tilesetPath
    ))
    {
        fmt::print(
                "Failed to load TileSet!\n"
        );

        shutdown();

        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if(!ImGui_ImplSDL3_InitForSDLRenderer(window, renderer)){
        fmt::print("ImGui SDL3 init error\n");
        return false;
    }
    if(!ImGui_ImplSDLRenderer3_Init(renderer)){
        fmt::print("ImGui SDL3Render init error\n");
        return  false;
    }


    // Engine ready


    running = true;

    fmt::print(
            "Engine initialized successfully!\n"
    );

    return true;
}

void Engine::run()
{
    SDL_Event event;

    while (running)
    {
        // Events

        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        //IMGUI NEW FRAME
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        //GUI
        ImGui::Begin("Map Editor");
        ImGui::Text("Hello");
        ImGui::End();
        // Game Render

        SDL_SetRenderDrawColor(
                renderer,
                255,
                255,
                255,
                255
        );

        SDL_RenderClear(renderer);

        // Тестовый тайл.
        map.draw(renderer, tileset);

        //IMGUI RENDER
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(
                ImGui::GetDrawData(),
                renderer
                );

        SDL_RenderPresent(renderer);
    }
}

void Engine::shutdown()
{
    running = false;

    tileset.unload();

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}
