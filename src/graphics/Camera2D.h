//
// Created by user on 17.09.2026.
//

#ifndef RPGMAKER_CAMERA2D_H
#define RPGMAKER_CAMERA2D_H

struct Position2D{
    float x = 0;
    float y = 0;
};

struct Camera2D{
    //offset like camera X and camera Y
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float zoom = 1.0f;

    [[nodiscard]] Position2D screenToWorld(Position2D screen)const{
        float worldX = (screen.x / zoom) + offsetX;
        float worldY = (screen.y / zoom) + offsetY;
        return {worldX,worldY};
    };
    [[nodiscard]] Position2D worldToScreen(Position2D world)const{
        float screenX = (world.x - offsetX) * zoom;
        float screenY = (world.y - offsetY) * zoom;
        return{screenX,screenY};
    };
};
#endif //RPGMAKER_CAMERA2D_H
