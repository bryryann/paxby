#pragma once

#include "core/tasks.h"
#include "storage/task_repository.h"

#include <filesystem>

namespace storage {

class BinTaskRepository : public TaskRepository {
public:
    explicit BinTaskRepository(const std::filesystem::path& app_dir);

    /*
    std::vector<core::Task> get_all() override;

    core::Task get_id(std::size_t id) override;

    std::vector<core::Task> get_paginated(
        std::size_t page_number,
        std::size_t page_size
    ) override;

    void save_all(const std::vector<core::Task>& tasks) override;

    void add(const core::Task& task) override;

    void remove(std::size_t id) override;

    void set_completed(std::size_t id) override;
    */

private:
    std::filesystem::path file_path_;

    void validate_storage();
};

}
