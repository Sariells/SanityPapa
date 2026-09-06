//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_EDITORCONTEXT_H
#define RPGMAKER_EDITORCONTEXT_H

#endif //RPGMAKER_EDITORCONTEXT_H

#include <optional>

#include "../map/Map.h"
#include "../graphics/Tileset.h"

struct EditorContext{
    std::optional<Map>& currentMap;
    Tileset& tileset;
};