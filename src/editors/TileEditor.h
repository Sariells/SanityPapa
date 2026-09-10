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

struct TileStartEnd{
    ImVec2 start;
    ImVec2 end;
};

class TileEditor {
public:
    static void drawUI( Tileset& tileset,
                        EditorState& editorState
                        );
private:
    static int calculateTileID(
            MouseXY cords,
            const Tileset& tileset
    ) ;

    static MouseXY calculateMouseXY();

    static ImVec2  calculateImageSize(const Tileset& tileset);

    static TileStartEnd calculateTileStartEnd(Tileset &tileset,int tileColumn,int tileRow);

    static void drawHoverTile(Tileset &tileset);

    static void drawSelectedTile(int tileID,
                                 Tileset& tileset);
};


#endif //RPGMAKER_TILEEDITOR_H
