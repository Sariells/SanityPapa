//
// Created by user on 28.09.2026.
//

#include "mapIO.h"

bool mapIO::save(const Map &currentMap,const std::filesystem::path &path){
    auto result = json::object();
    result["width"] = currentMap.getWidth();
    result["height"] = currentMap.getHeight();
    result["layers"] = json::array();

    for(size_t layerIndex = 0; layerIndex < currentMap.getLayers();++layerIndex){

        json layer = json::object();
        layer["tiles"] = json::array();

        for(int y = 0; y < currentMap.getHeight(); ++y){
            json row = json::array();
            for(int x = 0; x < currentMap.getWidth(); ++x){

                row.push_back(currentMap.getTile(x,y,layerIndex));
            }
            layer["tiles"].push_back(row);
        }
        result["layers"].push_back(layer);
    }

    std::filesystem::create_directories(
            path.parent_path()
    );

    std::ofstream file(path);

    if(!file.is_open()){
        return false;
    }
    file << result.dump(4);
    return true;
}

std::optional<Map> mapIO::load(const std::filesystem::path& path){
    std::ifstream file(path);

    if (!file.is_open())
    {
        return std::nullopt;
    }

    json data;
    file >> data;

    int width = data["width"].get<int>();
    int height = data["height"].get<int>();

    std::size_t layerCount = data["layers"].size();

    Map map(
            width,
            height,
            layerCount
    );

    for (std::size_t layerIndex = 0;layerIndex < layerCount;++layerIndex){
        for (int y = 0; y < height; ++y){
            for (int x = 0; x < width; ++x){
                int tileID = data["layers"][layerIndex]["tiles"][y][x].get<int>();
                map.setTile(
                        x,
                        y,
                        layerIndex,
                        tileID
                );
            }
        }
    }
    return map;
}