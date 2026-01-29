// tasks.h
//
// Contains objects and enums related to the task storage structure.

#pragma once

#include <iostream>
#include <vector>
#include <optional>

namespace storage {

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
    Priority priority = Priority::Low;
    std::string created_at;
    std::optional<std::string> due_date;
};

}
