// json.h
//
// Json parsing and mapping.

#pragma once

#include <nlohmann/json.hpp>

#include <storage/tasks.h>

namespace storage::json {

std::string priority_to_string(Priority p);

Priority priority_from_string(const std::string& s);

void to_json(nlohmann::json& j, const Task& t);

void from_json(nlohmann::json& j, Task& t);

}
