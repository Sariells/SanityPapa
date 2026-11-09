//
// Created by user on 28.09.2026.
//

#ifndef RPGMAKER_MAPIO_H
#define RPGMAKER_MAPIO_H

#include "Map.h"



namespace mapIO {
    bool save(const Map &currentMap,const std::filesystem::path &path);
    std::optional<Map> load(const std::filesystem::path &path);
}


#endif //RPGMAKER_MAPIO_H
