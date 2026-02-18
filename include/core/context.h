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
    List,
    Show,
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

    // 'list' properties
    std::filesystem::path list_dir = ".";
    bool paginated = true;
    std::size_t page_number = 0;
    std::size_t page_size   = 10;

    // 'show' properties
    std::size_t show_id;
};

}
