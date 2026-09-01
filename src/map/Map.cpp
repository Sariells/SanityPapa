//
// Created by user on 01.09.2026.
//

#include "Map.h"

Map::Map(int x, int y)
:   Width(x),
    Height(y)
{
    map.resize(x * y);
}

void Map::setTile(int x,int y,int tileID){
    int index = y * Width + x;
    map[index] = tileID;
}

int Map::getTile(int x,int y) const{
    int index = y * Width + x;
    return index;
}