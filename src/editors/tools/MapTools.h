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
#include "../EditorContext.h"

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

void handleMapInput(EditorContext &context);

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
                   int tileID,
                   size_t layerIndex);

    [[nodiscard]]
    static mapXY calculateMapXY(const Tileset &tileset, const Camera2D &camera);

    MinMax calculateMinMax(mapXY& mapXY) const;

    void brush(EditorContext &context);

    void eraser(EditorContext &context);

    void  fill_color(EditorContext &context);

    static void fill_color_Preview(
                            int minX,
                            int endX,
                            int minY,
                            int endY,
                            const EditorContext &context);

};


#endif //RPGMAKER_MAPTOOLS_H
