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
};

}
