//
// Created by user on 28.09.2026.
//

#include "mapIO.h"

bool mapIO::save(const Map &currentMap,const std::filesystem::path &path){
    if(!path.parent_path().empty()){
        std::filesystem::create_directories(path.parent_path());
    }
    std::ofstream file(path);
    if(!file.is_open()){
        return false;
    }

    file << "{\n";
    file << "\"Width\":  " << currentMap.getWidth()  << ",\n";
    file << "\"Height\": " << currentMap.getHeight() << ",\n";
    file << "\"Layers\": \n[";

    for(size_t layerIndex = 0; layerIndex < currentMap.getLayers();++layerIndex){
        file << "[";
        for(int y = 0; y < currentMap.getHeight();++y){
            file << "\n[";
            for(int x = 0; x < currentMap.getWidth();++x){
                file << currentMap.getTile(x,y,layerIndex);
                if(x < currentMap.getWidth() - 1){
                    file << ",";
                }
            }
            file << "]";
            if(y < currentMap.getHeight() - 1){
                file << ",";
            }
        }
        file << "\n]";
        if(layerIndex < currentMap.getLayers() - 1){
            file << ",";
        }
    }
    file << "]";
    file << "\n}";
    return true;
};


std::optional<Map> mapIO::load(const std::filesystem::path& path){
    std::ifstream file(path);
    if(!file.is_open()){
        return std::nullopt;
    }

    json data;
    file >> data;
    //creating map
    int width = data["Width"].get<int>();
    int height = data["Height"].get<int>();
    size_t layerCount = data["Layers"].size();
    Map map{width,height,layerCount};

    for(size_t layerIndex = 0; layerIndex < map.getLayers();++layerIndex){
        for(int y = 0; y < map.getHeight();++y){
            for(int x = 0; x < map.getWidth();++x){
                int tileID = data["Layers"][layerIndex][y][x].get<int>();
                map.setTile(x,y,layerIndex,tileID);
            }
        }
    }

    return map;
};

