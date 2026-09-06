//
// Created by user on 01.09.2026.
//

#include "Map.h"


#include <fmt/core.h>

Map::Map(int x, int y)
:   Width(x),
    Height(y)
{
    mapTile.resize(x * y);
}

bool Map::isInside(int x, int y) const{
    return x >= 0 &&
           y >= 0 &&
           x < Width &&
           y < Height;
}
void Map::setTile(int x,int y,int tileID){
    if(!isInside(x,y)){
        fmt::print("undefined behavior");
        return;
    }
    int index = y * Width + x;
    mapTile[index] = tileID;
}

int Map::getTile(int x,int y) const{
    if(!isInside(x,y)){
        fmt::print("undefined behavior");
        return -1;
    }
    int index = y * Width + x;
    return mapTile[index];
}

void Map::draw(SDL_Renderer *renderer, const Tileset &tileset) const {
    for(int y = 0; y < Height; ++y){
        for(int x = 0; x < Width; ++x){
            int tileID = getTile(x,y);

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

int Map::getHeight() const {
    return Height;
}
int Map::getWidth() const {
    return Width;
}