//
// Created by user on 10.09.2026.
//

#ifndef RPGMAKER_TOOLPANEL_H
#define RPGMAKER_TOOLPANEL_H

#include "imgui.h"
#include "SDL3/SDL.h"
#include "fmt/core.h"
#include <SDL3_image/SDL_image.h>

#include <filesystem>
#include <string>
#include <unordered_map>

#include "../EditorState.h"
#include "../../assets/AssetManager.h"

class ToolPanel {
public:
    bool initialize(SDL_Renderer *renderer,const AssetManager& assets);

    void drawUI(EditorState& editorState);
private:
    std::unordered_map<std::string,SDL_Texture*> icons;

};


#endif //RPGMAKER_TOOLPANEL_H
