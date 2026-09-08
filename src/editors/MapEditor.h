//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_MAPEDITOR_H
#define RPGMAKER_MAPEDITOR_H

#include <imgui.h>

#include <optional>

#include "../map/Map.h"
#include "EditorState.h"

struct mapXY{
    int x;
    int y;
};

class MapEditor {
public:
    void drawUI(std::optional<Map>& currentMap);

    void handleMapInput(std::optional<Map>& currentMap,
                        const Tileset& tileset,
                        const EditorState& editorState);

private:

    int newMapWidth = 10;
    int newMapHeight = 10;

    mapXY calculateMapXY(
            const Tileset& tileset
            )const;
};


#endif //RPGMAKER_MAPEDITOR_H
