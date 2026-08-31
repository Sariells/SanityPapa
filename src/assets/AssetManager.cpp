#include "AssetManager.h"

AssetManager::AssetManager(
        const std::filesystem::path& projectRoot
)
        : projectRoot(std::filesystem::absolute(projectRoot)),
          dataRoot(this->projectRoot / "data")
{
}

std::filesystem::path AssetManager::data(
        const std::filesystem::path& path
) const
{
    return dataRoot / path;
}

const std::filesystem::path& AssetManager::getProjectRoot() const
{
    return projectRoot;
}
