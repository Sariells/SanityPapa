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
   TileEditor::drawUI(context.tileset,context.editorState);

   const size_t layerCount = context.currentMap ? context.currentMap->getLayers() : 0;

   toolPanel.drawUI(context.editorState, layerCount);

   mapTools.handleMapInput(context);
   handleKeyboardInput(context.camera);
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
//Cделать передвижение на стрелочки и колесико мышки и добавить зум
void EditorUI::handleKeyboardInput(Camera2D &camera) {
    float time = ImGui::GetIO().DeltaTime; //это для плавности штука кадры в секунду берет
    float cameraSpeed = 200.0f;
    if(ImGui::IsKeyDown(ImGuiKey_W) && !ImGui::GetIO().WantCaptureKeyboard){
        camera.offsetY -= cameraSpeed * time;
    }
    if(ImGui::IsKeyDown(ImGuiKey_S) && !ImGui::GetIO().WantCaptureKeyboard){
        camera.offsetY += cameraSpeed * time; //это какая-то умная формула чтобы камера плавно двигалась
    }
    if(ImGui::IsKeyDown(ImGuiKey_D) && !ImGui::GetIO().WantCaptureKeyboard){
        camera.offsetX += cameraSpeed * time;
    }
    if(ImGui::IsKeyDown(ImGuiKey_A) && !ImGui::GetIO().WantCaptureKeyboard){
        camera.offsetX -= cameraSpeed * time;
    }
}