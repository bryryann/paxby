// json.h
//
// Json parsing and mapping.

#pragma once

#include "core/tasks.h"

#include <nlohmann/json.hpp>

namespace storage::json {

std::string priority_to_string(core::Priority p);

core::Priority priority_from_string(const std::string& s);

void to_json(nlohmann::json& j, const core::Task& t);

void from_json(nlohmann::json& j, core::Task& t);

}
