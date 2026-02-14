#pragma once

#include "core/tasks.h"

#include <string>
#include <vector>

namespace utils {

std::string current_timestamp();

int next_id(const std::vector<core::Task>& tasks);

}
