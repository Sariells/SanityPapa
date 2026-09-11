//
// Created by user on 10.09.2026.
//

#ifndef RPGMAKER_TOOLPANEL_H
#define RPGMAKER_TOOLPANEL_H

#include "imgui.h"
#include "SDL3/SDL.h"
#include "fmt/core.h"
#include <SDL3_image/SDL_image.h>


#include "../EditorState.h"
#include "../../assets/AssetManager.h"

class ToolPanel {
public:
    bool initialize(SDL_Renderer *renderer,const AssetManager& assets);

    void drawUI(EditorState& editorState);
private:
    SDL_Texture* brushIcon = nullptr;
    SDL_Texture* eraserIcon = nullptr;
    SDL_Texture* fillIcon = nullptr;
};


#endif //RPGMAKER_TOOLPANEL_H
