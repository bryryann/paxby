// context.h
//
// Define global settings and variables.

#pragma once

#include <filesystem>

namespace core {

// Existing CLI commands.
enum class Command {
    None,
    Init,
};

// Runtime configuration passed to all CLI commands.
struct Context {
    bool show_help = false;
    bool verbose = false;

    Command command = Command::None;

    std::filesystem::path init_dir = ".";
};

}
