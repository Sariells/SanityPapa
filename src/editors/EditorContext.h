//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_EDITORCONTEXT_H
#define RPGMAKER_EDITORCONTEXT_H

#include "../map/Map.h"
#include "../graphics/Tileset.h"
#include "../graphics/Camera2D.h"
#include "EditorState.h"

#include <optional>

struct EditorContext{
    std::optional<Map> &currentMap;
    Tileset &tileset;
    EditorState &editorState;
    Camera2D &camera;
};
#endif //RPGMAKER_EDITORCONTEXT_H