//
// Created by user on 10.09.2026.
//

#ifndef RPGMAKER_MAPTOOLS_H
#define RPGMAKER_MAPTOOLS_H

#include "imgui.h"

#include <optional>
#include <algorithm>

#include "../../map/Map.h"
#include "../EditorState.h"


struct mapXY{
    int x;
    int y;
};
struct MinMax{
    int minX;
    int minY;

    int maxX;
    int maxY;
};

class MapTools {
public:

void handleMapInput(std::optional<Map> &currentMap,
                    const Tileset &tileset,
                    const EditorState &editorState
                    );


private:
// Stores the previous mouse tile to keep a continuous stroke between frames.
    int lastPaintX = -1;
    int lastPaintY = -1;
    bool hasLast = false;
//
    int startX = -1;
    int startY = -1;
    bool hasFillStart = false;

    static void paintLine(Map& map,
                   int startX,
                   int startY,
                   int endX,
                   int endY,
                   int tileID);

    [[nodiscard]]
    static mapXY calculateMapXY(const Tileset& tileset);

    MinMax calculateMinMax(mapXY& mapXY) const;

    void brush(std::optional<Map> &currentMap,
               const Tileset &tileset,
               const EditorState &editorState);

    void eraser(std::optional<Map> &currentMap,
               const Tileset &tileset);

    void  fill_color(std::optional<Map> &currentMap,
                     const Tileset &tileset,
                     const EditorState &editorState);

    static void fill_color_Preview(int minX,
                            int endX,
                            int minY,
                            int endY,
                            const Tileset &tileset);

};


#endif //RPGMAKER_MAPTOOLS_H
