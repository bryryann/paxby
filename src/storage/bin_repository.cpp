#include <cstring>
#include <fstream>

#include "storage/bin_task_repository.h"
#include "io/binary.h";

namespace storage {

BinTaskRepository::BinTaskRepository(const std::filesystem::path& app_dir)
    : file_path_(app_dir / "tasks.bin") {}

// WARN: unused
void BinTaskRepository::add(const core::Task& task) {
    validate_storage();

    std::fstream file(file_path_, 
                      std::ios::in  |
                      std::ios::out |
                      std::ios::binary
    );
    if (!file) {
        throw std::runtime_error(
            "Failed to open storage file."
        );
    }

    file.seekg(4); // skip magic
    uint64_t task_count;
    file.read(reinterpret_cast<char*>(&task_count), sizeof(task_count));

    file.seekp(0, std::ios::end); // move to end to append

    // write 'id'
    uint32_t id = static_cast<uint32_t>(task.id);
    file.write(reinterpret_cast<const char*>(&id), sizeof(id));

    // write 'completed'
    uint8_t completed = task.completed ? 1 : 0;
    file.write(reinterpret_cast<const char*>(&completed), sizeof(completed));

    // write 'priority'
    uint32_t priority = static_cast<uint32_t>(task.priority);
    file.write(reinterpret_cast<const char*>(&priority), sizeof(priority));

    // write 'title'
    io::writestring(file, task.title);

    // write 'created_at'
    io::writestring(file, task.created_at);

    // write 'due_date'
    uint8_t has_due = task.due_date.has_value() ? 1 : 0;
    file.write(reinterpret_cast<const char*>(&has_due), sizeof(has_due));

    if (has_due) {
        io::writestring(file, *task.due_date);
    }

    // write 'tags'
    uint64_t tag_count = task.tags.size();
    file.write(reinterpret_cast<const char*>(&tag_count), sizeof(tag_count));

    for (const auto& tag : task.tags ) {
        io::writestring(file, tag);
    }

    task_count++;
    file.seekp(4); // back to right after magic
    file.write(reinterpret_cast<const char*>(&task_count), sizeof(task_count));
}

void BinTaskRepository::validate_storage() {
    if (!std::filesystem::exists(file_path_)) {
        throw std::runtime_error("Storage not initialized. Run `paxby ini` first.");
    }

    std::ifstream in(file_path_, std::ios::binary);

    char magic[4];
    in.read(magic, 4);

    if (std::strncmp(magic, "TSK1", 4) != 0) {
        throw std::runtime_error("Invalid or corrupted storage file.");
    }
}

}
