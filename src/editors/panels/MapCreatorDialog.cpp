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

    if (newMapHeight > 0 && newMapWidth > 0){
        int tileCount = newMapWidth * newMapHeight;
        ImGui::Text(
                "Map size: %d x %d",
                newMapWidth,
                newMapHeight
                );
        ImGui::Text(
                "Tiles: %d",
                tileCount
                );
    } else {
        ImGui::Text(
                "InvalidMap size"
                );
    }

    if(currentMap){
        ImGui::Text(
                "Current Map: %d x %d",
                currentMap->getWidth(),
                currentMap->getHeight()
                );
    }

    if(ImGui::Button("Create new Map")){
        if (newMapHeight > 0 && newMapWidth > 0){
            currentMap.emplace(
                    newMapWidth,
                    newMapHeight
                               );
        }
    }

    ImGui::End();
}