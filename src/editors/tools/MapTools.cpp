//
// Created by user on 10.09.2026.
//

#include "MapTools.h"

mapXY MapTools::calculateMapXY(const Tileset& tileset)const {
    ImVec2 MousePosition = ImGui::GetMousePos();

    int mapX = static_cast<int>(MousePosition.x) / tileset.getTileWidth();
    int mapY = static_cast<int>(MousePosition.y) / tileset.getTileHeight();

    return{mapX,mapY};
}
//Алгоритм Брезенхэма для рисование ровных линий
void MapTools::paintLine(Map& map,  int startX, int startY, int endX, int endY, int tileID) {
    int dx = std::abs(startX - endX);
    int dy = std::abs(startY - endY);

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

void MapTools::handleMapInput(std::optional<Map> &currentMap, const Tileset &tileset, const EditorState &editorState) {
    if(currentMap &&
       editorState.selectedTileID >= 0 &&
       !ImGui::GetIO().WantCaptureMouse &&
       ImGui::IsMouseDown(ImGuiMouseButton_Left)){

        mapXY position = calculateMapXY(tileset);

        if(!currentMap->isInside(position.x,position.y)){
            hasLast = false;
            return;
        }
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