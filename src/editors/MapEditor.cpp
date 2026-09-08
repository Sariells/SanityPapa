//
// Created by user on 06.09.2026.
//

#include "MapEditor.h"

mapXY MapEditor::calculateMapXY(const Tileset& tileset)const {
    ImVec2 MousePosition = ImGui::GetMousePos();

    int mapX = static_cast<int>(MousePosition.x) / tileset.getTileWidth();
    int mapY = static_cast<int>(MousePosition.y) / tileset.getTileHeight();

    return{mapX,mapY};
}

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

void MapEditor::handleMapInput(std::optional<Map> &currentMap, const Tileset &tileset, const EditorState &editorState) {
    if(currentMap &&
    editorState.selectedTileID >= 0 &&
    !ImGui::GetIO().WantCaptureMouse &&
    ImGui::IsMouseClicked(ImGuiMouseButton_Left))

    {
        mapXY position = calculateMapXY(tileset);

        currentMap->setTile(
                position.x,
                position.y,
                editorState.selectedTileID
                );
    }
}