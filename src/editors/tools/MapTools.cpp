//
// Created by user on 10.09.2026.
//

#include "MapTools.h"

void MapTools::handleMapInput(EditorContext &context) {

    switch (context.editorState.currentTool) {

        case EditorTools::None:
            break;

        case EditorTools::Brush:
            brush(context);
            break;

        case EditorTools::Eraser:
            eraser(context);
            break;
        case EditorTools::Fill_Color:
            fill_color(context);
            break;
        default:
            break;
    }
}

void MapTools::brush(EditorContext &context) {

    if( !context.currentMap ||
            context.editorState.selectedTileID < 0 ||
            ImGui::GetIO().WantCaptureMouse ||
            !ImGui::IsMouseDown(ImGuiMouseButton_Left)){
            hasLast = false;
            return;
        }

        mapXY position = calculateMapXY(context.tileset,context.camera);
        if(!hasLast){
            lastPaintX = position.x;
            lastPaintY = position.y;
            paintLine(*context.currentMap,
                      lastPaintX,
                      lastPaintY,
                      position.x,
                      position.y,
                      context.editorState.selectedTileID,
                      context.editorState.activeLayer);
            hasLast = true;
        } else {
            paintLine(*context.currentMap,
                      lastPaintX,
                      lastPaintY,
                      position.x,
                      position.y,
                      context.editorState.selectedTileID,
                      context.editorState.activeLayer);
            lastPaintX = position.x;
            lastPaintY = position.y;
        }
    }

void MapTools::eraser(EditorContext &context) {
    if( !context.currentMap ||
        ImGui::GetIO().WantCaptureMouse ||
        !ImGui::IsMouseDown(ImGuiMouseButton_Left)){
        hasLast = false;
        return;
    }
        mapXY position = calculateMapXY(context.tileset,context.camera);

        if(!context.currentMap->isInside(position.x,position.y)){
            hasLast = false;
            return;
        }
        if(!hasLast){
            lastPaintX = position.x;
            lastPaintY = position.y;
            paintLine(*context.currentMap,
                      lastPaintX,
                      lastPaintY,
                      position.x,
                      position.y,
                      -1,
                      context.editorState.activeLayer);
            hasLast = true;
        } else {
            paintLine(*context.currentMap,
                      lastPaintX,
                      lastPaintY,
                      position.x,
                      position.y,
                      -1,
                      context.editorState.activeLayer);
            lastPaintX = position.x;
            lastPaintY = position.y;
        }
}

void MapTools::fill_color(EditorContext &context) {
    if (!context.currentMap ||
        context.editorState.selectedTileID < 0 ||
        ImGui::GetIO().WantCaptureMouse)
    {
        return;
    }
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        mapXY position = calculateMapXY(context.tileset,context.camera);

        if (context.currentMap->isInside(position.x, position.y))
        {
            startX = position.x;
            startY = position.y;
            hasFillStart = true;
        }
    }
    if (hasFillStart &&
        ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        mapXY position = calculateMapXY(context.tileset,context.camera);
        MinMax m = calculateMinMax(position);

        fill_color_Preview(m.minX,m.maxX,m.minY,m.maxY,context);
        // текущая position — это временный конец прямоугольника
    }
    if (hasFillStart &&
        ImGui::IsMouseReleased(ImGuiMouseButton_Left))
    {
        mapXY position = calculateMapXY(context.tileset,context.camera);
        MinMax m = calculateMinMax(position);

        for(int y = m.minY;y <= m.maxY; ++y){
            for(int x = m.minX;x <= m.maxX; ++x){
                context.currentMap->setTile(x,y,context.editorState.activeLayer,
                                            context.editorState.selectedTileID);
            }
        }
        hasFillStart = false;
        // position теперь окончательный end
    }
}

void MapTools::fill_color_Preview(int minX, int endX,
                                  int minY, int endY,
                                  const EditorContext &context) {

    auto worldStartX = static_cast<float>(minX * context.tileset.getTileWidth());
    auto worldStartY = static_cast<float>(minY * context.tileset.getTileHeight());

    auto worldEndX = static_cast<float>((endX + 1) * context.tileset.getTileWidth());
    auto worldEndY = static_cast<float>((endY + 1) * context.tileset.getTileHeight());

    auto screenStartX = (worldStartX - context.camera.offsetX) * context.camera.zoom;
    auto screenStartY = (worldStartY - context.camera.offsetY) * context.camera.zoom;

    auto screenEndX = (worldEndX - context.camera.offsetX) * context.camera.zoom;
    auto screenEndY = (worldEndY - context.camera.offsetY) * context.camera.zoom;

    ImVec2 uv0(screenStartX,screenStartY);
    ImVec2 uv1(screenEndX,screenEndY);

    ImGui::GetForegroundDrawList()->AddRect(
            uv0,
            uv1,
            IM_COL32(255,255,255,255)
            );
}

mapXY MapTools::calculateMapXY(const Tileset& tileset, const Camera2D& camera) {
    //Screen Cords
    ImVec2 MousePosition = ImGui::GetMousePos();
    //world cords
    float worldX = MousePosition.x / camera.zoom + camera.offsetX;
    float worldY = MousePosition.y / camera.zoom + camera.offsetY;
    //TILE
    int mapX = static_cast<int>(worldX) / tileset.getTileWidth();
    int mapY = static_cast<int>(worldY) / tileset.getTileHeight();

    return{mapX,mapY};
}

MinMax MapTools::calculateMinMax(mapXY &position) const{
    const int X = position.x;
    const int Y = position.y;

    const int minX = std::min(startX, X);
    const int maxX = std::max(startX, X);

    const int minY = std::min(startY, Y);
    const int maxY = std::max(startY, Y);

    return {minX,minY,maxX,maxY};
}
// Fills gaps between mouse positions so fast brush strokes remain continuous.
// Uses Bresenham's line algorithm.
void MapTools::paintLine(Map &map,
                         int startX, int startY,
                         int endX, int endY,
                         int tileID,size_t layerIndex) {

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

    map.setTile(startX, startY, layerIndex, tileID);

    if (dx >= dy) {
        while (startX != endX || startY != endY) {
            startX += stepX;
            error += dy;
            if (error >= dx) {
                startY += stepY;
                error -= dx;
            }
            map.setTile(startX, startY, layerIndex,tileID);
        }
    } else {
        while (startX != endX || startY != endY) {
            startY += stepY;
            error += dx;
            if (error >= dy) {
                startX += stepX;
                error -= dy;
            }
            map.setTile(startX, startY, layerIndex,tileID);
        }
    }
}