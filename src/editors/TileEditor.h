//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_TILEEDITOR_H
#define RPGMAKER_TILEEDITOR_H

#include <imgui.h>
#include <SDL3/SDL.h>


#include "../graphics/Tileset.h"
#include "EditorState.h"

struct MouseXY
{
    int localX;
    int localY;
};

class TileEditor {
public:
    void drawUI(const   Tileset& tileset,
                        EditorState& editorState
                        );
private:
    int calculateTileID(
            MouseXY cords,
            const Tileset& tileset
    ) const;

    MouseXY calculateMouseXY()const;

    ImVec2 calculateImageSize(const Tileset& tileset)const;
};


#endif //RPGMAKER_TILEEDITOR_H
