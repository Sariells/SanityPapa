#include "engine/Engine.h"

#include <fmt/core.h>

#include <filesystem>

int main()
{
    const std::filesystem::path projectRoot = RPGMAKER_PROJECT_ROOT;

    Engine engine(projectRoot, Map(10, 10));

    if (!engine.initialize())
    {
        fmt::print(
                "Engine initialization failed!\n"
        );

        return 1;
    }

    engine.run();

    return 0;
}
