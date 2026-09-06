//
// Created by user on 05.09.2026.
//

#ifndef RPGMAKER_EDITORUI_H
#define RPGMAKER_EDITORUI_H

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <fmt/core.h>

#include "MapEditor.h"
#include "EditorContext.h"

class EditorUI {
public:
    bool initialize(SDL_Window* window, SDL_Renderer* renderer);
    void processEvent(SDL_Event& event);
    void newFrame();
    void drawEditors(EditorContext& context);
    void render(SDL_Renderer* renderer);
    void shutdown();
private:
    MapEditor mapEditor;
};


#endif //RPGMAKER_EDITORUI_H
