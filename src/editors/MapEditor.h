//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_MAPEDITOR_H
#define RPGMAKER_MAPEDITOR_H

#include <imgui.h>

#include <optional>

#include "../map/Map.h"

class MapEditor {
public:
    void drawUI(std::optional<Map>& currentMap);


private:
    int newMapWidth = 10;
    int newMapHeight = 10;
};


#endif //RPGMAKER_MAPEDITOR_H
