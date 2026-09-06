//
// Created by user on 05.09.2026.
//

#include "EditorUI.h"

bool EditorUI::initialize(SDL_Window* window, SDL_Renderer *renderer) {
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
   mapEditor.drawUI(context.currentMap);
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