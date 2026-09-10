//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_MAPCREATORDIALOG_H
#define RPGMAKER_MAPCREATORDIALOG_H

#include "imgui.h"

#include <optional>
#include <math.h>

#include "../../map/Map.h"
#include "../EditorState.h"

struct mapXY{
    int x;
    int y;
};

class MapCreatorDialog {
public:
    void drawUI(std::optional<Map>& currentMap);

    void handleMapInput(std::optional<Map>& currentMap,
                        const Tileset& tileset,
                        const EditorState& editorState);

private:

    int newMapWidth = 10;
    int newMapHeight = 10;

    int lastPaintX = -1;
    int lastPaintY = -1;
    bool hasLast = false;

    mapXY calculateMapXY(
            const Tileset& tileset
            )const;

    void paintLine(Map &map,
                   int endX,
                   int endY,
                   int startX,
                   int startY,
                   int tileID);
};


#endif //RPGMAKER_MAPCREATORDIALOG_H
