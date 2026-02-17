#pragma once

#include "core/tasks.h"

#include <nlohmann/json.hpp>
#include <vector>

namespace storage {

class TaskRepository {
public:
    virtual ~TaskRepository() = default;

    virtual std::vector<core::Task> get_all() = 0;

    virtual std::vector<core::Task> get_paginated(
        std::size_t page_number,
        std::size_t page_size
    ) = 0;

    virtual void save_all(const std::vector<core::Task>& tasks) = 0;

    virtual void add(const core::Task& task) = 0;
};

}
