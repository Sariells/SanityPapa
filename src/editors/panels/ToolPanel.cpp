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

    const auto IconDirectory = assets.data("Icon");

    fmt::print(
            "Loading Icon: {}\n",
            IconDirectory.string()
    );

    for(const auto& entry : std::filesystem::directory_iterator(IconDirectory)){

        const auto path = entry.path();

        if(path.extension() != ".png"){
            continue;
        }

        std::string iconName = path.stem().string();

        SDL_Surface *surface = IMG_Load(path.string().c_str());

        if (!surface)
        {
            fmt::print(
                    "Failed to load brush icon: {}\n",
                    SDL_GetError());

            return false;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_DestroySurface(surface);
        if (!texture)
        {
            fmt::print(
                    "Failed to create brush texture: {}\n",
                    SDL_GetError());

            return false;
        }
        icons[iconName] = texture;
    }
    return true;
}

void ToolPanel::drawUI(EditorState& editorState)
{
    ImGui::Begin("Tools");

    ImGui::BeginGroup();
    if (icons["brush"])
    {
        if (ImGui::ImageButton(
                "Brush",
                reinterpret_cast<ImTextureID>(icons["brush"]),
                ImVec2{48.0f, 48.0f}))
        {
            editorState.currentTool = EditorTools::Brush;
        }
    }
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::BeginGroup();
    if (icons["eraser"])
    {
        if (ImGui::ImageButton(
                "Eraser",
                reinterpret_cast<ImTextureID>(icons["eraser"]),
                ImVec2{48.0f, 48.0f}))
        {
            editorState.currentTool = EditorTools::Eraser;
        }
    }
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::BeginGroup();
    if (icons["fill_color"])
    {
        if (ImGui::ImageButton(
                "Fill_color",
                reinterpret_cast<ImTextureID>(icons["fill_color"]),
                ImVec2{48.0f, 48.0f}))
        {
            editorState.currentTool = EditorTools::Fill_Color;
        }
    }
    ImGui::EndGroup();
    ImGui::End();
}
