//
// Created by user on 06.09.2026.
//

#include "TileEditor.h"

TileUV TileEditor::calculateTileUV(int tileID, const Tileset &tileset) const {
    int tileColumn =tileID % tileset.getColumns();
    int tileRow = tileID / tileset.getColumns();

    float pixelStartX= static_cast<float>(tileColumn) * static_cast<float>(tileset.getTileWidth());
    float pixelStartY= static_cast<float>(tileRow) * static_cast<float>(tileset.getTileHeight());
    float pixelEndX = pixelStartX + static_cast<float>(tileset.getTileWidth());
    float pixelEndY = pixelStartY + static_cast<float>(tileset.getTileHeight());

    float uvStartX = pixelStartX / static_cast<float>(tileset.getTextureWidth());
    float uvStartY = pixelStartY / static_cast<float>(tileset.getTextureHeight());
    float uvEndX = pixelEndX / static_cast<float>(tileset.getTextureWidth());
    float uvEndY = pixelEndY / static_cast<float>(tileset.getTextureHeight());

    ImVec2 start (uvStartX,uvStartY);
    ImVec2 end(uvEndX,uvEndY);

    return {start,end};
}

void TileEditor::drawUI(const Tileset &tileset, EditorState &editorState) {
    SDL_Texture* texture = tileset.getTextureHandler();
    float width = 0.0f;
    float height = 0.0f;

    if(!texture){
        fmt::print("texture not load:{}\n", SDL_GetError());
        return;
    }

        if(!SDL_GetTextureSize(texture, &width, &height)){
        fmt::print("texture size error{}\n", SDL_GetError());
        return;
    }

    ImVec2 imageSize(
            static_cast<float>(tileset.getTextureWidth()),
            static_cast<float>(tileset.getTextureHeight())
            );
    ImVec2 uvStart(0.0f, 0.0f);
    ImVec2 uvEnd(1.0f, 1.0f);

    ImGui::Begin("TileEditor");
    ImGui::Image(
                reinterpret_cast<ImTextureID>(texture),
                imageSize,
                uvStart,
                uvEnd
                );
    ImGui::End();
}