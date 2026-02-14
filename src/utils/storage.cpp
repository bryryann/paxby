#include "utils/storage.h"

#include <chrono>
#include <ctime>

namespace utils {

std::string current_timestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

int next_id(const std::vector<core::Task>& tasks) {
    int max_id = 0;
    for (const auto& t : tasks) {
        max_id = std::max(max_id, t.id);
    }

    return max_id + 1;
}

}
