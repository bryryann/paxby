#include "cli/command.h"

#include <iostream>

namespace cli {

struct option options[] = {
    {"help",  no_argument,       nullptr, 'h'},
    // {"name",  required_argument, nullptr, 'n'},
    {nullptr, 0,                 nullptr,  0 }
};

void print_help() {
    std::cout << "usage: paxby [OPTION]... [ARG]...\n"
              << "options:\n"
              << " -h, --help    Display this help and exit.\n";
}

}
