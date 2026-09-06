#include "Tileset.h"

#include <SDL3_image/SDL_image.h>
#include <tinyxml2.h>

#include <filesystem>

using namespace tinyxml2;

Tileset::~Tileset()
{
    unload();
}

bool Tileset::load(
        SDL_Renderer* renderer,
        const std::filesystem::path& path
)
{
    unload();

    if (!renderer)
    {
        fmt::print(
                "Failed to load TileSet: renderer is null\n"
        );

        return false;
    }

    fmt::print(
            "Loading TileSet: {}\n",
            path.string()
    );

    // Check TSX

    if (!std::filesystem::exists(path))
    {
        fmt::print(
                "TileSet file does not exist: {}\n",
                path.string()
        );

        return false;
    }

    // Load TSX

    XMLDocument document;

    if (document.LoadFile(path.string().c_str()) != XML_SUCCESS)
    {
        fmt::print(
                "Failed to load TileSet '{}': {}\n",
                path.string(),
                document.ErrorStr()
        );

        return false;
    }

    const XMLElement* tilesetElement =
            document.FirstChildElement("tileset");

    if (!tilesetElement)
    {
        fmt::print(
                "Invalid tileset: missing <tileset>\n"
        );

        return false;
    }


    // Read tileset properties


    if (tilesetElement->QueryIntAttribute(
            "tilewidth",
            &tileWidth
    ) != XML_SUCCESS)
    {
        fmt::print(
                "Invalid tileset: missing 'tilewidth'\n"
        );

        unload();
        return false;
    }

    if (tilesetElement->QueryIntAttribute(
            "tileheight",
            &tileHeight
    ) != XML_SUCCESS)
    {
        fmt::print(
                "Invalid tileset: missing 'tileheight'\n"
        );

        unload();
        return false;
    }

    if (tilesetElement->QueryIntAttribute(
            "tilecount",
            &tileCount
    ) != XML_SUCCESS)
    {
        fmt::print(
                "Invalid tileset: missing 'tilecount'\n"
        );

        unload();
        return false;
    }

    if (tilesetElement->QueryIntAttribute(
            "columns",
            &columns
    ) != XML_SUCCESS)
    {
        fmt::print(
                "Invalid tileset: missing 'columns'\n"
        );

        unload();
        return false;
    }

    if (tileWidth <= 0 ||
        tileHeight <= 0 ||
        tileCount <= 0 ||
        columns <= 0)
    {
        fmt::print(
                "Invalid tileset values: "
                "tileWidth={}, tileHeight={}, "
                "tileCount={}, columns={}\n",
                tileWidth,
                tileHeight,
                tileCount,
                columns
        );

        unload();
        return false;
    }


    // Find image


    const XMLElement* imageElement =
            tilesetElement->FirstChildElement("image");

    if (!imageElement)
    {
        fmt::print(
                "Invalid tileset: missing <image>\n"
        );

        unload();
        return false;
    }

    const char* imageSource =
            imageElement->Attribute("source");

    if (!imageSource || imageSource[0] == '\0')
    {
        fmt::print(
                "Invalid tileset: image has no source\n"
        );

        unload();
        return false;
    }


    // Resolve image path relative to TSX


    std::filesystem::path imagePath = path.parent_path() / imageSource;

    imagePath = std::filesystem::weakly_canonical(imagePath);

    fmt::print(
            "Loading tileset image: {}\n",
            imagePath.string()
    );

    if (!std::filesystem::exists(imagePath))
    {
        fmt::print(
                "Tileset image does not exist: {}\n",
                imagePath.string()
        );

        unload();
        return false;
    }


    // Load PNG


    SDL_Surface* surface =
            IMG_Load(imagePath.string().c_str());

    if (!surface)
    {
        fmt::print(
                "Failed to load tileset image '{}': {}\n",
                imagePath.string(),
                SDL_GetError()
        );

        unload();
        return false;
    }

    fmt::print(
            "Tileset image loaded: {}x{}\n",
            surface->w,
            surface->h
    );


    // Create texture
    textureWidth = surface->w;
    textureHeight = surface->h;

    texture = SDL_CreateTextureFromSurface(
                    renderer,
                    surface
            );

    SDL_DestroySurface(surface);

    if (!texture)
    {
        fmt::print(
                "Failed to create tileset texture: {}\n",
                SDL_GetError()
        );

        unload();
        return false;
    }


    // Success


    fmt::print(
            "Tileset loaded successfully:\n"
            "  Tile size: {}x{}\n"
            "  Tile count: {}\n"
            "  Columns: {}\n",
            tileWidth,
            tileHeight,
            tileCount,
            columns
    );

    return true;
}

void Tileset::unload()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    tileWidth = 0;
    tileHeight = 0;
    tileCount = 0;
    columns = 0;
    textureWidth = 0;
    textureHeight = 0;
}

void Tileset::draw(SDL_Renderer* renderer, float x, float y) const {
    if (!renderer || !texture)
        return;
    float width = 0.0f;
    float height = 0.0f;

    if (!SDL_GetTextureSize(texture, &width, &height))
    {
        fmt::print(
                "SDL_GetTextureSize failed: {}\n",
                SDL_GetError()
        );

        return;
    }

    SDL_FRect destination{
            x,
            y,
            width,
            height
    };

    SDL_RenderTexture(
            renderer,
            texture,
            nullptr,
            &destination
    );
}

void Tileset::drawTile(SDL_Renderer *renderer, int tileID, float x, float y) const {
    if (!renderer || !texture)
        return;

    if (columns <= 0)
        return;

    if (tileID < 0 || tileID >= tileCount)
        return;

    // Позиция тайла внутри tileset-текстуры.
    const int tileX = tileID % columns;
    const int tileY = tileID / columns;

    SDL_FRect source{
            static_cast<float>(tileX * tileWidth),
            static_cast<float>(tileY * tileHeight),
            static_cast<float>(tileWidth),
            static_cast<float>(tileHeight)
    };

    SDL_FRect destination{
            x,
            y,
            static_cast<float>(tileWidth),
            static_cast<float>(tileHeight)
    };

    SDL_RenderTexture(
            renderer,
            texture,
            &source,
            &destination
    );
}

int Tileset::getTileWidth() const
{
    return tileWidth;
}

int Tileset::getTileHeight() const
{
    return tileHeight;
}

int Tileset::getTileCount() const
{
    return tileCount;
}

int Tileset::getColumns() const
{
    return columns;
}

SDL_Texture *Tileset::getTextureHandler() const {
    return texture;
}

int Tileset::getTextureWidth()const {
    return textureWidth;
}

int Tileset::getTextureHeight()const {
    return textureHeight;
}