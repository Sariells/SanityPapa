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

void EditorUI::drawEditors(EditorContext &context,ViewPort &view) {
   mapCreatorDialog.drawUI(context.currentMap, context.editorState);
   TileEditor::drawUI(context.tileset,context.editorState);

   const size_t layerCount = context.currentMap ? context.currentMap->getLayers() : 0;

   toolPanel.drawUI(context.editorState, layerCount);

   mapTools.handleMapInput(context);
   if(context.currentMap){
       handleKeyboardInput(context.camera,*context.currentMap,context.tileset,view);
   }
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

void EditorUI::handleKeyboardInput(Camera2D &camera, Map &currentMap,const Tileset &tileset, ViewPort &view) {
    float time = ImGui::GetIO().DeltaTime;
    float cameraSpeed = 200.0f;

    if (ImGui::GetIO().WantCaptureKeyboard){
        return;
    }
    auto mapWorldWidth = static_cast<float>(currentMap.getWidth() * tileset.getTileWidth());
    auto mapWorldHeight = static_cast<float>(currentMap.getHeight() * tileset.getTileHeight());
    // float workspaceWidth = mapWorldWidth  * 2.0f;
    // float workspaceHeight = mapWorldHeight  * 2.0f;
    Center center{mapWorldWidth,mapWorldHeight};

    if(ImGui::IsKeyDown(ImGuiKey_W)){
        camera.offsetY -= cameraSpeed * time;
    }
    if(ImGui::IsKeyDown(ImGuiKey_S)){
        camera.offsetY += cameraSpeed * time;
    }
    if(ImGui::IsKeyDown(ImGuiKey_D)){
        camera.offsetX += cameraSpeed * time;
    }
    if(ImGui::IsKeyDown(ImGuiKey_A)){
        camera.offsetX -= cameraSpeed * time;
    }
    if(ImGui::IsKeyPressed(ImGuiKey_1)){
        camera.jumpToCenter(center,camera,view);
    }
}