//
// Created by user on 05.09.2026.
//

#ifndef RPGMAKER_EDITORUI_H
#define RPGMAKER_EDITORUI_H

#include "MapCreatorDialog.h"
#include "TileEditor.h"
#include "ToolPanel.h"
#include "MapTools.h"
#include "EditorContext.h"
#include "SDL3/SDL.h"




class EditorUI {
public:
    bool initialize(SDL_Window* window,SDL_Renderer* renderer,const AssetManager& assetManager);
    static void processEvent(SDL_Event& event);
    static void newFrame();
    void drawEditors(EditorContext& context,ViewPort &view);
    static void render(SDL_Renderer* renderer);
    static void shutdown();
    static void handleKeyboardInput(Camera2D &camera,Map &currentMap,const Tileset &tileset, ViewPort &view);
private:
    MapCreatorDialog mapCreatorDialog;
    TileEditor tileEditor;
    MapTools mapTools;
    ToolPanel toolPanel;
};


#endif //RPGMAKER_EDITORUI_H
