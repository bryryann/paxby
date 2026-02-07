// tasks_json.h
//
// Json tasks parsing and mapping.
#pragma once

#include "core/tasks.h"

#include <nlohmann/json.hpp>

namespace core {

std::string priority_to_string(Priority p);

Priority priority_from_string(const std::string& s);

void to_json(nlohmann::json& j, const Task& t);

void from_json(const nlohmann::json& j, Task& t);

}
