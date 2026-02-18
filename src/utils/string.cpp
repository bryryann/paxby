// string.cpp
//
// Helper functions related to string operations

#include "utils/string.h"
#include "core/tasks_json.h"

#include <sstream>

namespace utils {

void add_comma_separated(std::vector<std::string> &vector, const std::string &input) {
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, ',')) {
        if (!item.empty()) {
            vector.push_back(item);
        }
    }
}

std::string task_compact(core::Task& task) {
    std::ostringstream oss;

    std::string status = task.completed ? "[x]" : "[ ]";

    oss << status 
        << " Task #" << task.id
        << " " << task.title
        << " (" << core::priority_to_string(task.priority) << ") ";

    if (!task.tags.empty()) {
        oss << "[";
        for (size_t i = 0; i < task.tags.size(); ++i) {
            oss << task.tags[i];
            if (i != task.tags.size() - 1) {
                oss << ",";
            }
        }
        oss << "] ";
    }

    if (task.due_date.has_value()) {
        oss << "due: " << task.due_date.value();
    }

    oss << "\n";

    return oss.str();
}

std::string task_detailed(core::Task& task) {
    std::ostringstream oss;

    std::string status = task.completed ? "[x]" : "[ ]";

    oss << "----------------------------------------\n";
    oss << status << " Task #" << task.id << ": " << task.title << "\n";
    oss << "Priority   : " << core::priority_to_string(task.priority) << "\n";
    oss << "Created at : " << task.created_at << "\n";

    if (task.due_date.has_value()) {
        oss << "Due date   : " << task.due_date.value() << "\n";
    }

    if (!task.tags.empty()) {
        oss << "Tags       : ";
        for (size_t i = 0; i < task.tags.size(); ++i) {
            oss << task.tags[i];
            if (i != task.tags.size() - 1) {
                oss << ", ";
            }
            oss << "\n";
        }
    }

    oss << "----------------------------------------\n";

    return oss.str();
}

}
