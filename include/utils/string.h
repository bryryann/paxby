// string.h
//
// Helper functions related to string operations

#pragma once

#include "core/tasks.h"

#include <string>
#include <vector>

namespace utils {

void add_comma_separated(std::vector<std::string>& vector, const std::string& input);

std::string task_compact(core::Task& task);

std::string task_detailed(core::Task& task);

}
