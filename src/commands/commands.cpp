// commands.cpp
//
// Implement the main commands and subcommands functions.

#include "commands/commands.h"
#include "core/tasks_json.h"
#include "storage/json_task_repository.h"
#include "utils/storage.h"

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <iostream>

namespace commands {

// Initializes a new project directory and default configuration files.
//
// Idempotent: existing files are preserved.
void run_init(const core::Context &ctx) {
    namespace fs = std::filesystem;

    // Helper for verbose output
    auto verbose = [&](const std::string& msg) {
        if (ctx.verbose) {
            std::cout <<  msg << "\n";
        }
    };

    fs::path dir = ctx.init_dir / ".paxby";
    verbose("Initializing project in " + ctx.init_dir.string());

    // Create the root directory if it does not exist
    std::error_code ec;
    fs::create_directories(dir, ec);
    if (ec) {
        throw std::runtime_error(
            "Failed to create directory '" + dir.string() + "': " + ec.message()
        );
    }

    // Default files created during initialization.
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

void run_add(const core::Context &ctx, storage::JsonTaskRepository& repo) {
    auto tasks = repo.get_all();

    core::Task new_task(
        utils::next_id(tasks),                     // id
        ctx.title,                                 // title
        false,                                     // completed
        ctx.tags,                                  // tags
        core::priority_from_string(ctx.priority),  // priority
        utils::current_timestamp(),                // created_at
        ctx.due_date.empty()                       // due_date
            ? std::nullopt
            : std::optional<std::string>(ctx.due_date)
    );

    repo.add(new_task);

    std::cout << "Added task #" << new_task.id << " " << new_task.title << "\n";
}

}
