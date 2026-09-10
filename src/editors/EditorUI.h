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
#include "TileEditor.h"


class EditorUI {
public:
    static bool initialize(SDL_Window* window, SDL_Renderer* renderer);
    static void processEvent(SDL_Event& event);
    static void newFrame();
    void drawEditors(EditorContext& context);
    static void render(SDL_Renderer* renderer);
    static void shutdown();
private:
    MapEditor mapEditor;
    TileEditor tileEditor;
};


#endif //RPGMAKER_EDITORUI_H
