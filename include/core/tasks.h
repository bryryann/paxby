// tasks.h
//
// Task related structs and properties

#pragma once

#include <iostream>
#include <vector>
#include <optional>

namespace core {

// Task priority
enum Priority {
    Low,
    Medium,
    High,
};

// Task object to be stored in tasks.json
struct Task {
    int id;
    std::string title;
    bool completed;
    std::vector<std::string> tags;
    Priority priority;
    std::string created_at;
    std::optional<std::string> due_date;

    Task(int id,
         std::string title,
         bool completed,
         std::vector<std::string> tags = {},
         Priority priority = Priority::Medium,
         std::string created_at = nullptr,
         std::optional<std::string> due_date = std::nullopt
    ) : id(id),
        title(std::move(title)),
        completed(completed),
        tags(std::move(tags)),
        priority(priority),
        created_at(std::move(created_at)),
        due_date(std::move(due_date))
    {}
};

}
