//
// Created by user on 01.09.2026.
//

#ifndef RPGMAKER_MAP_H
#define RPGMAKER_MAP_H

#include <SDL3/SDL.h>

#include <vector>


#include "../graphics/Tileset.h"
#include "../graphics/Camera2D.h"

struct MapLayers{
    std::vector<int> tiles;
};

class Map {
public:
    Map(int x, int y, size_t layerCount);

    void setTile(int x,int y,size_t layerIndex,int tileID);

    void draw(SDL_Renderer* renderer, const Tileset& tileset,const Camera2D &camera) const;

    [[nodiscard]]
    int getTile(int x,int y,size_t layerIndex) const;
    [[nodiscard]]
    bool isInside(int x, int y) const;
    [[nodiscard]]
    int getWidth()const;
    [[nodiscard]]
    int getHeight()const;
    [[nodiscard]]
    size_t getLayers()const;
private:
    //Это наш размер карты будет
    int Width = 0;
    int Height = 0;
    //это массив он будет заполнен  кол-во элементов по формуле widht * height = elements
    std::vector<MapLayers> layers;


};


#endif //RPGMAKER_MAP_H
