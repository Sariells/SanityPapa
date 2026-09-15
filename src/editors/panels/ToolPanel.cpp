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
    //Load all Icon from directory and save. In icons
    //Example "brush.png" -> icons[brush]
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
                    "Failed to load  icon: {}\n",
                    SDL_GetError());

            return false;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_DestroySurface(surface);
        if (!texture)
        {
            fmt::print(
                    "Failed to create icon texture'{}': {}\n",
                    iconName,
                    SDL_GetError());
            return false;
        }
        icons[iconName] = texture;
    }
    return true;
}

void ToolPanel::drawUI(EditorState& editorState,size_t layerCount)
{
    ImGui::Begin("Tools");
    if(layerCount > 0){
        int activeLayer = static_cast<int>(editorState.activeLayer);
        if(ImGui::SliderInt(
                "Layers",
                &activeLayer,
                0,
                static_cast<int>(layerCount) - 1)){
            editorState.activeLayer = static_cast<size_t>(activeLayer);
        }
    }
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
