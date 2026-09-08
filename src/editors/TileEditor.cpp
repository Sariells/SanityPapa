//
// Created by user on 06.09.2026.
//

#include "TileEditor.h"



MouseXY TileEditor::calculateMouseXY() const {
    ImVec2 imagePosition = ImGui::GetItemRectMin();
    ImVec2 mousePosition = ImGui::GetMousePos();

    int localX = static_cast<int>(mousePosition.x - imagePosition.x);
    int localY = static_cast<int>(mousePosition.y - imagePosition.y);
    return {localX,localY};
}

ImVec2 TileEditor::calculateImageSize(const Tileset &tileset)const {
    ImVec2 imageSize(
            static_cast<float>(tileset.getTextureWidth()),
            static_cast<float>(tileset.getTextureHeight())
    );
    return imageSize;
}

int TileEditor::calculateTileID(MouseXY cords, const Tileset& tileset) const {
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

void TileEditor::drawUI(const Tileset &tileset, EditorState &editorState) {
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