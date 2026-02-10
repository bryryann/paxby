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
        throw std::runtime_error("Invalid tasks file format");
    }

    return j.at("tasks").get<std::vector<core::Task>>();
}

void JsonTaskRepository::save_all(const std::vector<core::Task>& tasks) {
    validate_storage();

    nlohmann::json j;
    j["tasks"] = tasks;

    std::ofstream out(file_path_);
    if (!out) {
        throw std::runtime_error("Failed to open tasks.json for writing");
    }

    out << j.dump(2);
}

void JsonTaskRepository::add(const core::Task& task) {
    validate_storage();

    auto tasks = get_all();
    tasks.push_back(task);
    save_all(tasks);

}

void JsonTaskRepository::validate_storage() {
    if (!std::filesystem::exists(file_path_)) {
        throw std::runtime_error("Storage not initialized. Run `paxby init` first.");
    }
}

} // namespace storage
