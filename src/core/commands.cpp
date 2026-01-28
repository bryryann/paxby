#include "core/commands.h"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <iostream>

namespace core::commands {

void run_init(const Context &ctx) {
    namespace fs = std::filesystem;

    auto verbose = [&](const std::string& msg) {
        if (ctx.verbose) {
            std::cout <<  msg << "\n";
        }
    };

    fs::path dir = ctx.init_dir / ".paxby";
    verbose("Initializing project in " + ctx.init_dir.string());

    std::error_code ec;
    fs::create_directories(dir, ec);
    if (ec) {
        throw std::runtime_error(
            "Failed to create directory '" + dir.string() + "': " + ec.message()
        );
    }

    std::unordered_map<std::string, std::string> files = {
        {"tasks.json", "{ \"tasks\": [] }\n"},
        {"config.json", "{}\n"},
    };

    for (const auto& [name, content] : files) {
        fs::path file = dir / name;

        if (fs::exists(file)) {
            if (!fs::is_regular_file(file)) {
                throw std::runtime_error(
                    "'" + file.string() + "' exists and is not a regular file"
                );
            }

            verbose("Skipped existing file " + file.string());

            continue;
        }

        std::ofstream out(file);
        if (!out) {
            throw std::runtime_error("Failed to create file '" + file.string() + "'");
        }

        out << content;
        verbose("Created file " + file.string());
    }

    if (!ctx.verbose) {
        std::cout << "Initialize project in " << dir.parent_path().string() << "\n";
    }
}

}
