// string.cpp
//
// Helper functions related to string operations

#include "utils/string.h"

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

}
