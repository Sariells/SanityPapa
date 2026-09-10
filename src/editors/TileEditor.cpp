//
// Created by user on 06.09.2026.
//

#include "TileEditor.h"



MouseXY TileEditor::calculateMouseXY() {
    ImVec2 imagePosition = ImGui::GetItemRectMin();
    ImVec2 mousePosition = ImGui::GetMousePos();

    int localX = static_cast<int>(mousePosition.x - imagePosition.x);
    int localY = static_cast<int>(mousePosition.y - imagePosition.y);
    return {localX,localY};
}

ImVec2 TileEditor::calculateImageSize(const Tileset &tileset) {
    ImVec2 imageSize(
            static_cast<float>(tileset.getTextureWidth()),
            static_cast<float>(tileset.getTextureHeight())
    );
    return imageSize;
}

int TileEditor::calculateTileID(MouseXY cords, const Tileset& tileset) {
    int tileColumn = cords.localX / tileset.getTileWidth();
    int tileRow = cords.localY / tileset.getTileHeight();

    int tileID;

    if(tileColumn >= 0 && tileColumn < tileset.getColumns() && tileRow >= 0){
        tileID = tileRow * tileset.getColumns() + tileColumn;
    } else {
        return -1;
    }

    if(tileID >= 0 && tileID < tileset.getTileCount()){
        return tileID;
    }
    return -1;
}

TileStartEnd TileEditor::calculateTileStartEnd(Tileset &tileset) {
    ImVec2 imageposition = ImGui::GetItemRectMin();
    MouseXY cords = calculateMouseXY();

    int tileColumn = cords.localX / tileset.getTileWidth();
    int tileRow = cords.localY / tileset.getTileHeight();

    auto TileScreenX = imageposition.x + static_cast<float>(tileColumn * tileset.getTileWidth());
    auto TileScreenY = imageposition.y + static_cast<float>(tileRow * tileset.getTileHeight());

    auto TileEndX = TileScreenX + static_cast<float>(tileset.getTileWidth());
    auto TileEndY = TileScreenY + static_cast<float>(tileset.getTileHeight());

    ImVec2 tileStart{
            TileScreenX,
            TileScreenY
    };
    ImVec2 tileEnd{
            TileEndX,
            TileEndY
    };
    return {tileStart,tileEnd};
}

void TileEditor::drawHoverTile(Tileset &tileset) {
    TileStartEnd startEnd = calculateTileStartEnd(tileset);
    ImGui::GetWindowDrawList()->AddRect(
                startEnd.start,
                startEnd.end,
                IM_COL32(255,255,255,255)
            );
}

void TileEditor::drawUI(Tileset &tileset, EditorState &editorState) {
    SDL_Texture* texture = tileset.getTextureHandler();

    if(!texture){
        fmt::print("texture not load:{}\n", SDL_GetError());
        return;
    }

    ImVec2 uvStart(0.0f, 0.0f);
    ImVec2 uvEnd(1.0f, 1.0f);

    ImVec2 imageSize = calculateImageSize(tileset);

    ImGui::Begin("TileEditor");
    ImGui::Image(
                reinterpret_cast<ImTextureID>(texture),
                imageSize,
                uvStart,
                uvEnd
                );

    if(ImGui::IsItemHovered()){
        drawHoverTile(tileset);
    }
    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered()){

        MouseXY cords = calculateMouseXY();
        int tileID = calculateTileID(cords, tileset);
        if(tileID >= 0){
            editorState.selectedTileID = tileID;
        }
    }
    ImGui::Text(
            "Selected tile ID: %d",
            editorState.selectedTileID
    );
    ImGui::End();
}