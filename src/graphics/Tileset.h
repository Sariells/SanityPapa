#pragma once

#include <SDL3/SDL.h>
#include <fmt/core.h>

#include <filesystem>

class Tileset
{
public:
    Tileset() = default;

    ~Tileset();

    Tileset(const Tileset&) = delete;
    Tileset& operator=(const Tileset&) = delete;

    bool load(
            SDL_Renderer* renderer,
            const std::filesystem::path& path
    );

    void unload();

    void draw(SDL_Renderer* renderer, float x, float y) const;

    void drawTile(
            SDL_Renderer* renderer,
            int tileID,
            float x,
            float y
    ) const;

    [[nodiscard]]
    int getTileWidth() const;

    [[nodiscard]]
    int getTileHeight() const;

    [[nodiscard]]
    int getTileCount() const;

    [[nodiscard]]
    int getColumns() const;

    [[nodiscard]]
    SDL_Texture* getTextureHandler()const;

    [[nodiscard]]
    int getTextureWidth()const;

    [[nodiscard]]
    int getTextureHeight()const;

private:
    SDL_Texture* texture = nullptr;

    int tileWidth = 0;
    int tileHeight = 0;
    int tileCount = 0;
    int columns = 0;
    int textureWidth = 0;
    int textureHeight = 0;
};
