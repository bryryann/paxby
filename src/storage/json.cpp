// json.cpp
//
// Json parsing and mapping.

#include "storage/json.h"

namespace storage::json {

using json = nlohmann::json;

using namespace core;

inline std::string priority_to_string(Priority p) { 
    switch (p) {
        case Priority::Low:    return "low";
        case Priority::Medium: return "medium";
        case Priority::High:   return "high";
    }

    throw std::runtime_error("Invalid priority");
}

inline Priority priority_from_string(const std::string& s) {
    if (s == "low")    return Priority::Low;
    if (s == "medium") return Priority::Medium;
    if (s == "high")   return Priority::High;

    throw std::runtime_error("Unknown priority: " + s);
}

void to_json(json& j, const Task& t) {
    j = json{
        {"id", t.id},
        {"title", t.title},
        {"completed", t.completed},
        {"tags", t.tags},
        {"priority", priority_to_string(t.priority)},
        {"created_at", t.created_at},
    };

    if (t.due_date.has_value()) {
        j["due_date"] = t.due_date.value();
    } else {
        j["due_date"] = nullptr;
    };
}

void from_json(json& j, Task& t) {
    j.at("id").get_to(t.id);
    j.at("title").get_to(t.title);
    j.at("completed").get_to(t.completed);
    j.at("tags").get_to(t.tags);
    j.at("created_at").get_to(t.created_at);

    if (j.contains("priority")) {
        t.priority = priority_from_string(j.at("priority").get<std::string>());
    } else {
        t.priority = Priority::Low;
    }

    if (j.contains("due_date") && !j.at("due_date").is_null()) {
        t.due_date = j.at("due_date").get<std::string>();
    } else {
        t.due_date = std::nullopt;
    }
}

} // namespace storage::json
