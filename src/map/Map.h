//
// Created by user on 01.09.2026.
//

#ifndef RPGMAKER_MAP_H
#define RPGMAKER_MAP_H

#include <vector>

class Map {
public:
    Map(int x, int y);

    void setTile(int x,int y,int tileID);

    [[nodiscard]]
    int getTile(int x,int y) const;

private;
    //Это наш размер карты будет
    int Width = 0;
    int Height = 0;
    //это массив он будет заполнен  кол-во элементов по формуле widht * height = elements
    std::vector<int> map;
    //а потом мы сделаем что-то вроде
};


#endif //RPGMAKER_MAP_H
