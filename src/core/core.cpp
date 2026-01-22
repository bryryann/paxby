#include "core/core.h"

#include <iostream>

namespace core {

struct option long_options[] = {
    {"help",  no_argument,       nullptr, 'h'},
    {"name",  required_argument, nullptr, 'n'},
    {nullptr, 0,                 nullptr,  0 }
};

void run() {
    std::cout << "running..." << std::endl;
}

}
