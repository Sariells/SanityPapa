#include "Engine.h"

#include <fmt/core.h>

Engine::Engine(
        const std::filesystem::path& projectRoot
)
        : assets(projectRoot)
{
}

Engine::~Engine()
{
    shutdown();
}

bool Engine::initialize()
{
    // ---------------------------------------------------------
    // SDL
    // ---------------------------------------------------------

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        fmt::print(
                "SDL_Init failed: {}\n",
                SDL_GetError()
        );

        return false;
    }

    // ---------------------------------------------------------
    // Window
    // ---------------------------------------------------------

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

    // ---------------------------------------------------------
    // Renderer
    // ---------------------------------------------------------

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

    // ---------------------------------------------------------
    // Load tileset
    // ---------------------------------------------------------

    const auto tilesetPath =
            assets.data(
                    "tilesets/punyworld-overworld-tiles.tsx"
            );

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

    // ---------------------------------------------------------
    // Engine ready
    // ---------------------------------------------------------

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
        // -----------------------------------------------------
        // Events
        // -----------------------------------------------------

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        // -----------------------------------------------------
        // Update
        // -----------------------------------------------------


        // -----------------------------------------------------
        // Render
        // -----------------------------------------------------

        SDL_SetRenderDrawColor(
                renderer,
                255,
                255,
                255,
                255
        );

        SDL_RenderClear(renderer);

        // Тестовый тайл.
        tileset.draw(
                renderer,
                0.0f,
                0.0f
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
