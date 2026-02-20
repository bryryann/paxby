#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

#include "storage/json_task_repository.h"
#include "core/tasks.h"
#include "core/tasks_json.h"

namespace storage {

JsonTaskRepository::JsonTaskRepository(const std::filesystem::path& app_dir)
    : file_path_(app_dir / "tasks.json") {}

std::vector<core::Task> JsonTaskRepository::get_all() {
    validate_storage();

    std::ifstream in(file_path_);
    nlohmann::json j;

    try {
        in >> j;
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error(
            "Failed to parse tasks.json (file may be corrupted)."
        );
    }

    if (!j.contains("tasks") || !j["tasks"].is_array()) {
        throw std::runtime_error("Invalid tasks file format.");
    }

    return j.at("tasks").get<std::vector<core::Task>>();
}

core::Task JsonTaskRepository::get_id(std::size_t id) {
    validate_storage();

    std::ifstream in(file_path_);
    nlohmann::json j;

    try {
        in >> j;
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error(
            "Failed to parse tasks.json (file may be corrupted)."
        );
    }

    if (!j.contains("tasks") || !j["tasks"].is_array()) {
        throw std::runtime_error("Invalid tasks file format.");
    }

    for (const auto& task : j["tasks"]) {
        if (task.contains("id") && task["id"] == id) {
            return task.get<core::Task>();
        }
    }

    throw std::runtime_error("Task not found.");
}

std::vector<core::Task> JsonTaskRepository::get_paginated(
    std::size_t page_number,
    std::size_t page_size
) {
    validate_storage();

    std::ifstream in(file_path_);
    nlohmann::json j;

    try {
        in >> j;
    } catch (const nlohmann::json::parse_error&) {
        throw std::runtime_error(
            "Failed to parse tasks.json (file may be corrupted)."
        );
    }

    if (!j.contains("tasks") || !j["tasks"].is_array()) {
        throw std::runtime_error("Invalid tasks file format.");
    }

    // reference to tasks json array
    const auto& tasks_json = j["tasks"];

    std::size_t total = tasks_json.size();

    if (page_size == 0) {
        return {};
    }

    std::size_t start = page_number * page_size;

    if (start >= total) {
        throw std::runtime_error("Invalid page index - out of bounds.");
    }

    std::size_t end = std::min(start + page_size, total);

    std::vector<core::Task> result;
    result.reserve(end - start);

    for (std::size_t i = start; i < end; ++i) {
        result.push_back(tasks_json.at(i).get<core::Task>());
    }

    return result;
}

void JsonTaskRepository::save_all(const std::vector<core::Task>& tasks) {
    validate_storage();

    nlohmann::json j;
    j["tasks"] = tasks;

    std::ofstream out(file_path_);
    if (!out) {
        throw std::runtime_error("Failed to open tasks.json for writing.");
    }

    out << j.dump(2);
}

void JsonTaskRepository::add(const core::Task& task) {
    validate_storage();

    auto tasks = get_all();
    tasks.push_back(task);
    save_all(tasks);

}

void JsonTaskRepository::set_completed(std::size_t id) {
    validate_storage();

    std::ifstream in(file_path_);
    nlohmann::json j;

    try {
        in >> j;
    }
    catch (const nlohmann::json::parse_error&) {
        throw std::runtime_error(
            "Failed to parse tasks.json (file may be corrupted)."
        );
    }

    if (!j.contains("tasks") || !j["tasks"].is_array()) {
        throw std::runtime_error("Invalid tasks file format.");
    }

    bool found = false;
    for (auto& task : j["tasks"]) {
        if (task.contains("id") && task["id"] == id) {
            task["completed"] = true;
            found = true;
            break;
        }
    }

    if (!found) {
        throw std::runtime_error("Task not found.");
    }

    std::ofstream out(file_path_);
    if (!out) {
        throw std::runtime_error(
            "Failed to open tasks.json for writing."
        );
    }

    out << j.dump(2);
}

void JsonTaskRepository::validate_storage() {
    if (!std::filesystem::exists(file_path_)) {
        throw std::runtime_error("Storage not initialized. Run `paxby init` first.");
    }
}

} // namespace storage
