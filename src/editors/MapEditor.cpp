//
// Created by user on 06.09.2026.
//

#include "MapEditor.h"

void MapEditor::drawUI(std::optional<Map> &currentMap) {
    ImGui::Begin("Map Editor");

    ImGui::InputInt(
            "Width",
            &newMapWidth
            );
    ImGui::InputInt(
            "Height",
            &newMapHeight
            );

    if(ImGui::Button("Create new Map")){
        if (newMapHeight > 0 && newMapWidth > 0){
            currentMap.emplace(newMapWidth,newMapHeight);
        }
    }

    ImGui::End();
}
