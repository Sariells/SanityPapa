//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_MAPCREATORDIALOG_H
#define RPGMAKER_MAPCREATORDIALOG_H

#include "imgui.h"

#include <optional>

#include "../../map/Map.h"




class MapCreatorDialog {
public:
    void drawUI(std::optional<Map>& currentMap);



private:

    int newMapWidth = 10;
    int newMapHeight = 10;
    int newMapLayers = 1;



};


#endif //RPGMAKER_MAPCREATORDIALOG_H
