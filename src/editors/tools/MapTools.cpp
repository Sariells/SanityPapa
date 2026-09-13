//
// Created by user on 10.09.2026.
//

#include "MapTools.h"

void MapTools::handleMapInput(std::optional<Map> &currentMap,
                              const Tileset &tileset,
                              const EditorState &editorState) {

    switch (editorState.currentTool) {

        case EditorTools::None:
            break;

        case EditorTools::Brush:
            brush(currentMap,tileset,editorState);
            break;

        case EditorTools::Eraser:
            eraser(currentMap,tileset);
            break;
        case EditorTools::Fill_Color:
            fill_color(currentMap,tileset,editorState);
            break;
        default:
            break;
    }
}

void MapTools::brush(std::optional<Map> &currentMap,
                     const Tileset &tileset,
                     const EditorState &editorState){

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

void MapTools::eraser(std::optional<Map> &currentMap,
                      const Tileset &tileset
                      ){
    if( !currentMap ||
        ImGui::GetIO().WantCaptureMouse ||
        !ImGui::IsMouseDown(ImGuiMouseButton_Left)){
        hasLast = false;
        return;
    }
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
                      -1);
            hasLast = true;
        } else {
            paintLine(*currentMap,
                      lastPaintX,
                      lastPaintY,
                      position.x,
                      position.y,
                      -1);
            lastPaintX = position.x;
            lastPaintY = position.y;
        }

    if(!ImGui::IsMouseDown(ImGuiMouseButton_Left)){
        hasLast = false;
        return;
    }
}

void MapTools::fill_color(std::optional<Map> &currentMap,
                          const Tileset &tileset,
                          const EditorState &editorState) {
    if (!currentMap ||
        editorState.selectedTileID < 0 ||
        ImGui::GetIO().WantCaptureMouse)
    {
        return;
    }

    if (!ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        return;
    }

    mapXY position = calculateMapXY(tileset);

    if (!currentMap->isInside(position.x, position.y))
    {
        return;
    }

        if(!hasFillStart){
            startX = position.x;
            startY = position.y;
            hasFillStart = true;
        } else {
            const int endX = position.x;
            const int endY = position.y;

            const int minX = std::min(startX, endX);
            const int maxX = std::max(startX, endX);

            const int minY = std::min(startY, endY);
            const int maxY = std::max(startY, endY);

            for(int y = minY;y <= maxY; ++y){
                for(int x = minX;x <= maxX; ++x){
                    currentMap->setTile(x,y,editorState.selectedTileID);
                }
            }
            hasFillStart = false;
        }
}

mapXY MapTools::calculateMapXY(const Tileset& tileset)const {
    //supposed what the map start at screen position (0,0) Later need add zoom and camera
    ImVec2 MousePosition = ImGui::GetMousePos();

    int mapX = static_cast<int>(MousePosition.x) / tileset.getTileWidth();
    int mapY = static_cast<int>(MousePosition.y) / tileset.getTileHeight();

    return{mapX,mapY};
}
// Fills gaps between mouse positions so fast brush strokes remain continuous.
// Uses Bresenham's line algorithm.
void MapTools::paintLine(Map& map,
                         int startX,
                         int startY,
                         int endX,
                         int endY,
                         int tileID){

    const int dx = std::abs(startX - endX);
    const int dy = std::abs(startY - endY);

    int stepX = 0;
    int stepY = 0;

    if (startX < endX) {
        ++stepX;
    } else if (startX > endX) {
        --stepX;
    }

    if (startY < endY) {
        ++stepY;
    } else if (startY > endY) {
        --stepY;
    }

    int error = 0;

    map.setTile(startX, startY, tileID);

    if (dx >= dy) {
        while (startX != endX || startY != endY) {
            startX += stepX;
            error += dy;
            if (error >= dx) {
                startY += stepY;
                error -= dx;
            }
            map.setTile(startX, startY, tileID);
        }
    } else {
        while (startX != endX || startY != endY) {
            startY += stepY;
            error += dx;
            if (error >= dy) {
                startX += stepX;
                error -= dy;
            }
            map.setTile(startX, startY, tileID);
        }
    }
}