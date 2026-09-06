//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_TILEEDITOR_H
#define RPGMAKER_TILEEDITOR_H

#include <imgui.h>
#include <SDL3/SDL.h>


#include "../graphics/Tileset.h"
#include "EditorState.h"
struct TileUV
{
    ImVec2 start;
    ImVec2 end;
};

class TileEditor {
public:

    void drawUI(const   Tileset& tileset,
                        EditorState& editorState
                        );

    TileUV calculateTileUV(
            int tileID,
            const Tileset& tileset
    ) const;
};


#endif //RPGMAKER_TILEEDITOR_H
