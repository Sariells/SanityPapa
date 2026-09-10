//
// Created by user on 06.09.2026.
//

#include "MapCreatorDialog.h"

mapXY MapCreatorDialog::calculateMapXY(const Tileset& tileset)const {
    ImVec2 MousePosition = ImGui::GetMousePos();

    int mapX = static_cast<int>(MousePosition.x) / tileset.getTileWidth();
    int mapY = static_cast<int>(MousePosition.y) / tileset.getTileHeight();

    return{mapX,mapY};
}

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

//Алгоритм Брезенхэма
void MapCreatorDialog::paintLine(Map& map, int endX, int endY, int startX, int startY, int tileID) {
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);

    int sx = 0;
    int sy = 0;

    if (startX < endX) {
        ++sx;
    } else if (startX > endX) {
        --sx;
    }

    if (startY < endY) {
        ++sy;
    } else if (startY > endY) {
        --sy;
    }

    int error = 0;

    map.setTile(startX, startY, tileID);

    if (dx >= dy) {
        while (startX != endX || startY != endY) {
            startX += sx;
            error += dy;
            if (error >= dx) {
                startY += sy;
                error -= dx;
            }
            map.setTile(startX, startY, tileID);
        }
    } else {
        while (startX != endX || startY != endY) {
            startY += sy;
            error += dx;
            if (error >= dy) {
                startX += sx;
                error -= dy;
            }
            map.setTile(startX, startY, tileID);
        }
    }
}

void MapCreatorDialog::handleMapInput(std::optional<Map> &currentMap, const Tileset &tileset, const EditorState &editorState) {
    if(currentMap &&
    editorState.selectedTileID >= 0 &&
    !ImGui::GetIO().WantCaptureMouse &&
    ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        mapXY position = calculateMapXY(tileset);
        if(!hasLast){
            lastPaintX = position.x;
            lastPaintY = position.y;
            paintLine(*currentMap,
                        lastPaintX,
                        lastPaintY,
                      position.x,
                      position.y,
                      editorState.selectedTileID);
            hasLast = true;
        } else {
            paintLine(*currentMap,
                        lastPaintX,
                        lastPaintY,
                      position.x,
                      position.y,
                      editorState.selectedTileID);
                    lastPaintX = position.x;
                    lastPaintY = position.y;
        }
    }
    if(!ImGui::IsMouseDown(ImGuiMouseButton_Left)){
        hasLast = false;
        return;
    }
}