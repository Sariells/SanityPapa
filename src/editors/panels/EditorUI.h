//
// Created by user on 05.09.2026.
//

#ifndef RPGMAKER_EDITORUI_H
#define RPGMAKER_EDITORUI_H

#include "SDL3/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "fmt/core.h"

#include "MapCreatorDialog.h"
#include "TileEditor.h"
#include "ToolPanel.h"

#include "../EditorContext.h"
#include "../tools/MapTools.h"

class EditorUI {
public:
    bool initialize(SDL_Window* window,
                           SDL_Renderer* renderer,
                           const AssetManager& assetManager);
    static void processEvent(SDL_Event& event);
    static void newFrame();
    void drawEditors(EditorContext& context);
    static void render(SDL_Renderer* renderer);
    static void shutdown();
private:
    MapCreatorDialog mapCreatorDialog;
    TileEditor tileEditor;
    MapTools mapTools;
    ToolPanel toolPanel;
};


#endif //RPGMAKER_EDITORUI_H
