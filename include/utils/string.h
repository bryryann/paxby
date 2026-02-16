// string.h
//
// Helper functions related to string operations

#pragma once

#include "core/tasks.h"

#include <string>
#include <vector>

namespace utils {

void add_comma_separated(std::vector<std::string>& vector, const std::string& input);

std::string task_to_string(core::Task& task);

}
