//
// Created by user on 06.09.2026.
//

#ifndef RPGMAKER_EDITORSTATE_H
#define RPGMAKER_EDITORSTATE_H
enum class EditorTools{
    None, //Only before pick any tool
    Brush,
    Eraser,
    Fill
};
struct EditorState{
    int selectedTileID = -1;
    EditorTools currentTool = EditorTools::None;
};


#endif //RPGMAKER_EDITORSTATE_H