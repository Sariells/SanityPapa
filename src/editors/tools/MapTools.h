//
// Created by user on 10.09.2026.
//

#ifndef RPGMAKER_MAPTOOLS_H
#define RPGMAKER_MAPTOOLS_H

#include "imgui.h"

#include <optional>

#include "../../map/Map.h"
#include "../EditorState.h"

struct mapXY{
    int x;
    int y;
};

class MapTools {
public:
    void brush();
    void erase();
    void fill();

    void handleMapInput(std::optional<Map> &currentMap,
                        const Tileset &tileset,
                        const EditorState &editorState);
private:
    int lastPaintX = -1;
    int lastPaintY = -1;
    bool hasLast = false;

    void paintLine(Map& map,
                   int startX,
                   int startY,
                   int endX,
                   int endY,
                   int tileID);

    mapXY calculateMapXY(
            const Tileset& tileset
    )const;
};


#endif //RPGMAKER_MAPTOOLS_H
