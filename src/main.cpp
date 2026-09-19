#include <cstdlib>
#include <exception>
#include <filesystem>

#include <spdlog/spdlog.h>

#include "CityBuilder/Core/Application.hpp"

int main(const int argc, char* argv[])
{
    spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    try {
        const std::filesystem::path executablePath =
            argc > 0 ? std::filesystem::absolute(argv[0]) : std::filesystem::current_path();

        citybuilder::Application application{executablePath};
        return application.run();
    } catch (const std::exception& exception) {
        spdlog::critical("Fatal error: {}", exception.what());
        return EXIT_FAILURE;
    }
}
