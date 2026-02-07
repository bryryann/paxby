#include <storage/json_task_repository.h>

namespace storage {

JsonTaskRepository::JsonTaskRepository(const std::filesystem::path& app_dir)
    : file_path_(app_dir / "tasks.json") {}

void JsonTaskRepository::validate_storage() {
    if (!std::filesystem::exists(file_path_)) {
        throw std::runtime_error("Storage not initialized. Run `paxby init` first.");
    }
}

}
