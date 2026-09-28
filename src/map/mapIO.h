//
// Created by user on 28.09.2026.
//

#ifndef RPGMAKER_MAPIO_H
#define RPGMAKER_MAPIO_H

#include "Map.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class mapIO {
public:
    static bool save(const Map &currentMap,const std::filesystem::path &path);
    static std::optional<Map> load(const std::filesystem::path &path);
};


#endif //RPGMAKER_MAPIO_H
