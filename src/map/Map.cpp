//
// Created by user on 01.09.2026.
//

#include "Map.h"


#include <fmt/core.h>

Map::Map(int x, int y,size_t layerCount)
        :   Width(x),
            Height(y)
{
    layers.resize(layerCount);
    for(auto &layer : layers){
        layer.tiles.resize(Width * Height,-1);
    }
}



bool Map::isInside(int x, int y) const{
    return x >= 0 &&
           y >= 0 &&
           x < Width &&
           y < Height;
}

void Map::setTile(int x,int y,size_t layerIndex,int tileID){
    if(!isInside(x,y)){
        return;
    }
    if(layerIndex > layers.size()){
        return;
    }
    int index = y * Width + x;
    layers[layerIndex].tiles[index] = tileID;
}

int Map::getTile(int x,int y,size_t layerIndex) const{
    if(!isInside(x,y)){
        fmt::print("Tile coordinates are out of border\n");
        return -1;
    }
    if(layerIndex > layers.size()){
        return -1;
    }
    int index = y * Width + x;
    return layers[layerIndex].tiles[index];
}

void Map::draw(SDL_Renderer *renderer, const Tileset &tileset) const {
    for(size_t layerIndex = 0; layerIndex < layers.size(); ++layerIndex){
        for(int y = 0; y < Height; ++y){
            for(int x = 0; x < Width; ++x){
                int tileID = getTile(x,y,layerIndex);
                if(tileID < 0) {
                    continue;
                }
                float drawX = static_cast<float>(x) * static_cast<float>(tileset.getTileWidth());
                float drawY = static_cast<float>(y) * static_cast<float>(tileset.getTileHeight());

                tileset.drawTile(
                        renderer,
                        tileID,
                        drawX,
                        drawY
                );
            }
        }
    }
}

int Map::getHeight() const {
    return Height;
}
int Map::getWidth() const {
    return Width;
}
size_t Map::getLayers() const {
    return layers.size();
}