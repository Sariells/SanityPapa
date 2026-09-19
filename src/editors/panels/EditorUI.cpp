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
   mapCreatorDialog.drawUI(context.currentMap);
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
//Cделать передвижение на стрелочки и колесико мышки и добавить зум
void EditorUI::handleKeyboardInput(Camera2D &camera, Map &currentMap,const Tileset &tileset, ViewPort &view) {
    float time = ImGui::GetIO().DeltaTime; //это для плавности штука кадры в секунду берет
    float cameraSpeed = 200.0f;

    if (ImGui::GetIO().WantCaptureKeyboard){
        return;
    }
    //map size * tilesize px - (viewport / zoom)
    float mapWorldWidth = static_cast<int>(currentMap.getWidth()) * tileset.getTileWidth();
    float mapWorldHeight = static_cast<int>(currentMap.getHeight()) * tileset.getTileHeight();

    float viewportWorldWidth = (view.width / camera.zoom);
    float viewportWorldHeight =  (view.height / camera.zoom);

    float paddingX = mapWorldWidth * 0.1f;
    float paddingY = mapWorldHeight * 0.1f;

    float MaxOffsetX = mapWorldWidth + paddingX - viewportWorldWidth;
    float MaxOffsetY =  mapWorldHeight + paddingY - viewportWorldHeight;

    float MinOffsetX = -paddingX;
    float MinOffsetY = -paddingY;

    float workspaceWidth = mapWorldWidth + paddingX * 2.0f;
    float workspaceHeight = mapWorldHeight + paddingY * 2.0f;

    bool canMoveX = workspaceWidth > viewportWorldWidth;
    bool canMoveY = workspaceHeight > viewportWorldHeight;

    if(!canMoveX){
        camera.offsetX = (mapWorldWidth - viewportWorldWidth) / 2;
    }
    if(!canMoveY){
        camera.offsetY = (mapWorldHeight - viewportWorldHeight) /2;
    }
    if(ImGui::IsKeyDown(ImGuiKey_W) && canMoveY && camera.offsetY > MinOffsetY){
        camera.offsetY -= cameraSpeed * time;
    }
    if(ImGui::IsKeyDown(ImGuiKey_S) && canMoveY && camera.offsetY < MaxOffsetY){
        camera.offsetY += cameraSpeed * time; //это какая-то умная формула чтобы камера плавно двигалась
    }
    if(ImGui::IsKeyDown(ImGuiKey_D) && canMoveX && camera.offsetX < MaxOffsetX){
        camera.offsetX += cameraSpeed * time;
    }
    if(ImGui::IsKeyDown(ImGuiKey_A) && canMoveX && camera.offsetX > MinOffsetX){
        camera.offsetX -= cameraSpeed * time;
    }
}