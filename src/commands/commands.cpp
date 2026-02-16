// commands.cpp
//
// Implement the main commands and subcommands functions.

#include "commands/commands.h"
#include "core/tasks_json.h"
#include "storage/json_task_repository.h"
#include "utils/storage.h"
#include "utils/string.h"

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
            std::cout << "[verbose] " << msg << "\n";
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
    std::cout << "Fetching existing tasks...\n";
    auto tasks = repo.get_all();
    std::cout << "Loaded " << std::to_string(tasks.size()) << " existing tasks.\n";

    auto verbose = [&](const std::string& msg) {
        if (ctx.verbose) {
            std::cout << "[verbose] " << msg << "\n";
        }
    };

    auto new_id = utils::next_id(tasks);
    verbose("Generated new task id: " + std::to_string(new_id));

    auto priority = core::priority_from_string(ctx.priority);
    verbose("Parsed priority: " + ctx.priority);

    auto timestamp = utils::current_timestamp();
    verbose("Generated timestamp: " + timestamp);

    std::optional<std::string> due =
        ctx.due_date.empty()
            ? std::nullopt
            : std::optional<std::string>(ctx.due_date);

    if (due) {
        verbose("Due date set to: " + *due);
    } else {
        verbose("No due date specified.");
    }

    core::Task new_task(
        new_id,    // id
        ctx.title, // title
        false,     // completed
        ctx.tags,  // tags
        priority,  // priority
        timestamp, // created_at
        due        // due
    );

    verbose("Creating task: \"" + ctx.title + "\"");

    repo.add(new_task);
    verbose("Task persisted to repository.");

    std::cout << "Added task #" << new_task.id << " " << new_task.title << "\n";
}

// TODO: Implement run_list
void run_list(const core::Context &ctx, storage::JsonTaskRepository &repo) {
    std::cout << "Fetching existing tasks...\n";

    auto tasks = repo.get_all();
    int len = tasks.size();

    std::cout << "Loaded " << std::to_string(len) << " existing tasks.\n";

    if (len == 0) {
        std::cout << "No tasks found.\n";
        return;
    }

    for (core::Task t : tasks) {
        std::cout << utils::task_to_string(t);
    }
}

}
