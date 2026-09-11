//
// Created by user on 10.09.2026.
//

#include "ToolPanel.h"

bool ToolPanel::initialize(SDL_Renderer *renderer,
                           const AssetManager& assets) {

    if (!renderer) {
        fmt::print(
                "Failed to load TileSet: renderer is null\n"
        );
        return false;
    }

    const auto imagePath = assets.data("Icon/brush.png");

    fmt::print(
            "Loading Icon: {}\n",
            imagePath.string()
    );

    SDL_Surface *surface = IMG_Load(imagePath.string().c_str());
    if (!surface)
    {
        fmt::print(
                "Failed to load brush icon: {}\n",
                SDL_GetError());

        return false;
    }

    brushIcon = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_DestroySurface(surface);

    if (!brushIcon)
    {
        fmt::print(
                "Failed to create brush texture: {}\n",
                SDL_GetError());

        return false;
    }

    return true;
}


void ToolPanel::drawUI(EditorState& editorState)
{
    ImGui::Begin("Tools");

    if (brushIcon)
    {
        if (ImGui::ImageButton(
                "Brush",
                reinterpret_cast<ImTextureID>(brushIcon),
                ImVec2{48.0f, 48.0f}))
        {
            editorState.currentTool = EditorTools::Brush;
        }
    }

    ImGui::End();
}