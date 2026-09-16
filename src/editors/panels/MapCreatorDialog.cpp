//
// Created by user on 06.09.2026.
//

#include "MapCreatorDialog.h"

void MapCreatorDialog::drawUI(std::optional<Map> &currentMap) {
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
        }
    }

    ImGui::End();
}
