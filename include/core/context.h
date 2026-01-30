// context.h
//
// Define global settings and variables.

#pragma once

#include <filesystem>
#include <vector>

namespace core {

// Existing CLI commands.
enum class Command {
    None,
    Init,
    Add,
};

// Runtime configuration passed to all CLI commands.
struct Context {
    bool show_help = false;
    bool verbose = false;

    Command command = Command::None;

    // 'init' properties
    std::filesystem::path init_dir = ".";

    // 'add' properties
    std::string title;
    std::vector<std::string> tags;
    std::string priority;
    std::string due_date;
};

}
