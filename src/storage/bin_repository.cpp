#include <cstring>
#include <fstream>

#include "storage/bin_task_repository.h"

namespace storage {

BinTaskRepository::BinTaskRepository(const std::filesystem::path& app_dir)
    : file_path_(app_dir / "tasks.bin") {}

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
