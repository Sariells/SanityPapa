//
// Created by user on 17.09.2026.
//

#ifndef RPGMAKER_CAMERA2D_H
#define RPGMAKER_CAMERA2D_H

struct Camera2D{
    //offset like camera X and camera Y
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float zoom = 2.0f;

    //calculateWorld;
    //calculateScreen;
};
// Поменять mapDraw и tileDraw в mapDraw делаем SDL_Frect а tileDraw передаем его уберая int x int y;
// Потом в MapTools изменить calculateMapXY
#endif //RPGMAKER_CAMERA2D_H
