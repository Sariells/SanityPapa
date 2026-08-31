#pragma once

#include <filesystem>

class AssetManager
{
public:
    explicit AssetManager(
            const std::filesystem::path& projectRoot
    );

    [[nodiscard]]
    std::filesystem::path data(
            const std::filesystem::path& path
    ) const;

    [[nodiscard]]
    const std::filesystem::path& getProjectRoot() const;

private:
    std::filesystem::path projectRoot;
    std::filesystem::path dataRoot;
};