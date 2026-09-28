//
// Created by user on 06.09.2026.
//

#include "MapCreatorDialog.h"

void MapCreatorDialog::drawUI(std::optional<Map> &currentMap,  EditorState& editorState) {
    ImGui::Begin("Map Editor");

    ImGui::InputInt(
            "Width",
            &newMapWidth
            );
    ImGui::InputInt(
            "Height",
            &newMapHeight
            );
    ImGui::InputInt(
            "Layers",
            &newMapLayers
    );
    if (newMapHeight > 0 && newMapWidth > 0 && newMapLayers > 0){
        int tileCount = newMapWidth * newMapHeight;
        ImGui::Text(
                "Map size: %d x %d, Layers: %d",
                newMapWidth,
                newMapHeight,
                newMapLayers
                );
        ImGui::Text(
                "Tiles per layer: %d",
                tileCount
                );
    } else {
        ImGui::Text(
                "Invalid Map size"
                );
    }

    if(currentMap){
        ImGui::Text(
                "Current Map: %d x %d, Layers %zu",
                currentMap->getWidth(),
                currentMap->getHeight(),
                currentMap->getLayers()
                );
    }

    if(ImGui::Button("Create new Map")){
        if (newMapHeight > 0 && newMapWidth > 0 && newMapLayers > 0){
            currentMap.emplace(
                    newMapWidth,
                    newMapHeight,
                    newMapLayers
                               );
            editorState.activeLayer = 0;
        }
    }
    const std::filesystem::path mapPath = "C:\\Users\\user\\CLionProjects\\Rpgmaker\\data\\Saves\\save.json";
    if (ImGui::Button("Load Map")){
        auto loadedMap = mapIO::load(mapPath);
        if (loadedMap){
            currentMap = std::move(loadedMap);
            editorState.activeLayer = 0;
        }
        else{
            fmt::print("Failed to load map\n");
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Save Map")){
        if (currentMap){
            if (!mapIO::save(*currentMap,mapPath)){
                fmt::print("Failed to save map\n");
            }
        }
    }

    ImGui::SameLine();
    ImGui::End();
}
