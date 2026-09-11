//
// Created by user on 05.09.2026.
//

#include "EditorUI.h"

bool EditorUI::initialize(SDL_Window *window, SDL_Renderer *renderer,const AssetManager& assetManager) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if(!ImGui_ImplSDL3_InitForSDLRenderer(window, renderer)){
        fmt::print("ImGui SDL3 init error\n");
        return false;
    }
    if(!ImGui_ImplSDLRenderer3_Init(renderer)){
        fmt::print("ImGui SDL3Render init error\n");
        return  false;
    }
    if (!toolPanel.initialize(renderer, assetManager))
    {
        fmt::print("ToolPanel init error\n");
        return false;
    }
    return true;
}

void EditorUI::processEvent(SDL_Event &event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void EditorUI::newFrame() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void EditorUI::drawEditors(EditorContext &context) {
   mapCreatorDialog.drawUI(context.currentMap);
   tileEditor.drawUI(context.tileset,context.editorState);
   toolPanel.drawUI(context.editorState);

   mapTools.handleMapInput(context.currentMap,context.tileset,context.editorState);
}

void EditorUI::render(SDL_Renderer *renderer) {
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(
            ImGui::GetDrawData(),
            renderer
    );
}

void EditorUI::shutdown() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}